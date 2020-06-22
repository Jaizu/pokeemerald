#include "global.h"
#include "decompress.h"
#include "event_object_movement.h"
#include "field_camera.h"
#include "field_control_avatar.h"
#include "field_effect.h"
#include "field_effect_helpers.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "fldeff.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "main.h"
#include "mirage_tower.h"
#include "menu.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon_icon.h"
#include "pokemon.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "trainer_pokemon_sprites.h"
#include "trig.h"
#include "util.h"
#include "follow_me.h"
#include "constants/field_effects.h"
#include "constants/event_object_movement.h"
#include "constants/metatile_behaviors.h"
#include "constants/moves.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define subsprite_table(ptr) {.subsprites = ptr, .subspriteCount = (sizeof ptr) / (sizeof(struct Subsprite))}

EWRAM_DATA s32 gFieldEffectArguments[8] = {0};
EWRAM_DATA u16 gReflectionPaletteUnfadedBuffer[0x10] = {0};
EWRAM_DATA u16 gReflectionPaletteFadedBuffer[0x10] = {0};
// Static type declarations

static void Task_PokecenterHeal(u8 taskId);
static void PokecenterHealEffect_Init(struct Task *);
static void PokecenterHealEffect_WaitForBallPlacement(struct Task *);
static void PokecenterHealEffect_WaitForBallFlashing(struct Task *);
static void PokecenterHealEffect_WaitForSoundAndEnd(struct Task *);
static u8 CreatePokecenterMonitorSprite(s16, s16);
static void SpriteCB_PokecenterMonitor(struct Sprite *);

static void Task_HallOfFameRecord(u8 taskId);
static void HallOfFameRecordEffect_Init(struct Task *);
static void HallOfFameRecordEffect_WaitForBallPlacement(struct Task *);
static void HallOfFameRecordEffect_WaitForBallFlashing(struct Task *);
static void HallOfFameRecordEffect_WaitForSoundAndEnd(struct Task *);
static void CreateHofMonitorSprite(s16, s16, s16, bool8);
static void SpriteCB_HallOfFameMonitor(struct Sprite *);

static u8 CreateGlowingPokeballsEffect(s16, s16, s16, bool16);
static void SpriteCB_PokeballGlowEffect(struct Sprite *);
static void PokeballGlowEffect_PlaceBalls(struct Sprite *);
static void PokeballGlowEffect_TryPlaySe(struct Sprite *);
static void PokeballGlowEffect_Flash1(struct Sprite *);
static void PokeballGlowEffect_Flash2(struct Sprite *);
static void PokeballGlowEffect_WaitAfterFlash(struct Sprite *);
static void PokeballGlowEffect_Dummy(struct Sprite *);
static void PokeballGlowEffect_WaitForSound(struct Sprite *);
static void PokeballGlowEffect_Idle(struct Sprite *);
static void SpriteCB_PokeballGlow(struct Sprite *);

static void FieldCallback_UseFly(void);
static void Task_UseFly(u8);
static void FieldCallback_FlyIntoMap(void);
static void Task_FlyIntoMap(u8);

static void Task_FallWarpFieldEffect(u8);
static bool8 FallWarpEffect_Init(struct Task *);
static bool8 FallWarpEffect_WaitWeather(struct Task *);
static bool8 FallWarpEffect_StartFall(struct Task *);
static bool8 FallWarpEffect_Fall(struct Task *);
static bool8 FallWarpEffect_Land(struct Task *);
static bool8 FallWarpEffect_CameraShake(struct Task *);
static bool8 FallWarpEffect_End(struct Task *);

static void Task_EscalatorWarpOut(u8);
static bool8 EscalatorWarpOut_Init(struct Task *);
static bool8 EscalatorWarpOut_WaitForPlayer(struct Task *);
static bool8 EscalatorWarpOut_Up_Ride(struct Task *);
static bool8 EscalatorWarpOut_Up_End(struct Task *);
static bool8 EscalatorWarpOut_Down_Ride(struct Task *);
static bool8 EscalatorWarpOut_Down_End(struct Task *);
static void RideUpEscalatorOut(struct Task *);
static void RideDownEscalatorOut(struct Task *);
static void FadeOutAtEndOfEscalator(void);
static void WarpAtEndOfEscalator(void);

static void FieldCallback_EscalatorWarpIn(void);
static void Task_EscalatorWarpIn(u8);
static bool8 EscalatorWarpIn_Init(struct Task *);
static bool8 EscalatorWarpIn_Down_Init(struct Task *);
static bool8 EscalatorWarpIn_Down_Ride(struct Task *);
static bool8 EscalatorWarpIn_Up_Init(struct Task *);
static bool8 EscalatorWarpIn_Up_Ride(struct Task *);
static bool8 EscalatorWarpIn_WaitForMovement(struct Task *);
static bool8 EscalatorWarpIn_End(struct Task *);

static void Task_UseWaterfall(u8);
static bool8 WaterfallFieldEffect_Init(struct Task *, struct ObjectEvent *);
static bool8 WaterfallFieldEffect_ShowMon(struct Task *, struct ObjectEvent *);
static bool8 WaterfallFieldEffect_WaitForShowMon(struct Task *, struct ObjectEvent *);
static bool8 WaterfallFieldEffect_RideUp(struct Task *, struct ObjectEvent *);
static bool8 WaterfallFieldEffect_ContinueRideOrEnd(struct Task *, struct ObjectEvent *);

static void Task_UseDive(u8);
static bool8 DiveFieldEffect_Init(struct Task *);
static bool8 DiveFieldEffect_ShowMon(struct Task *);
static bool8 DiveFieldEffect_TryWarp(struct Task *);

static void Task_LavaridgeGymB1FWarp(u8);
static bool8 LavaridgeGymB1FWarpEffect_Init(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGymB1FWarpEffect_CameraShake(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGymB1FWarpEffect_Launch(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGymB1FWarpEffect_Rise(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGymB1FWarpEffect_FadeOut(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGymB1FWarpEffect_Warp(struct Task *, struct ObjectEvent *, struct Sprite *);

static void FieldCB_LavaridgeGymB1FWarpExit(void);
static void Task_LavaridgeGymB1FWarpExit(u8);
static bool8 LavaridgeGymB1FWarpExitEffect_Init(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGymB1FWarpExitEffect_StartPopOut(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGymB1FWarpExitEffect_PopOut(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGymB1FWarpExitEffect_End(struct Task *, struct ObjectEvent *, struct Sprite *);

static void Task_LavaridgeGym1FWarp(u8);
static bool8 LavaridgeGym1FWarpEffect_Init(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGym1FWarpEffect_AshPuff(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGym1FWarpEffect_Disappear(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGym1FWarpEffect_FadeOut(struct Task *, struct ObjectEvent *, struct Sprite *);
static bool8 LavaridgeGym1FWarpEffect_Warp(struct Task *, struct ObjectEvent *, struct Sprite *);

static void Task_EscapeRopeWarpOut(u8);
static void EscapeRopeWarpOutEffect_Init(struct Task *);
static void EscapeRopeWarpOutEffect_Spin(struct Task *);

static void FieldCallback_EscapeRopeWarpIn(void);
static void Task_EscapeRopeWarpIn(u8);
static void EscapeRopeWarpInEffect_Init(struct Task *);
static void EscapeRopeWarpInEffect_Spin(struct Task *);

static void Task_TeleportWarpOut(u8);
static void TeleportWarpOutFieldEffect_Init(struct Task*);
static void TeleportWarpOutFieldEffect_SpinGround(struct Task*);
static void TeleportWarpOutFieldEffect_SpinExit(struct Task*);
static void TeleportWarpOutFieldEffect_End(struct Task*);

static void FieldCallback_TeleportWarpIn(void);
static void Task_TeleportWarpIn(u8);
static void TeleportWarpInFieldEffect_Init(struct Task *);
static void TeleportWarpInFieldEffect_SpinEnter(struct Task *);
static void TeleportWarpInFieldEffect_SpinGround(struct Task *);

static void Task_FieldMoveShowMon(u8);
static void FieldMoveShowMonEffect_Init(struct Task *);
static void FieldMoveShowMonEffect_LoadGfx(struct Task *);
static void FieldMoveShowMonEffect_MoveWindowOnscreen(struct Task *);
static void FieldMoveShowMonEffect_WaitForMonCry(struct Task *);
static void FieldMoveShowMonEffect_MoveWindowOffscreen(struct Task *);
static void FieldMoveShowMonEffect_DestroyGfx(struct Task *);
static void FieldMoveShowMonEffect_End(struct Task *);
static void HBlankCB_FieldEffectPopupWindow(void);
static void SpriteCB_UpdateSpritePos(struct Sprite *sprite);

static void Task_SurfFieldEffect(u8);
static void SurfFieldEffect_Init(struct Task *);
static void SurfFieldEffect_FieldMovePose(struct Task *);
static void SurfFieldEffect_ShowMon(struct Task *);
static void SurfFieldEffect_JumpOnSurfBlob(struct Task *);
static void SurfFieldEffect_End(struct Task *);

static void SpriteCB_NPCFlyOut(struct Sprite *);

static void Task_FlyOut(u8);
static void FlyOutFieldEffect_FieldMovePose(struct Task *);
static void FlyOutFieldEffect_ShowMon(struct Task *);
static void FlyOutFieldEffect_BirdLeaveBall(struct Task *);
static void FlyOutFieldEffect_WaitBirdLeave(struct Task *);
static void FlyOutFieldEffect_BirdSwoopDown(struct Task *);
static void FlyOutFieldEffect_JumpOnBird(struct Task *);
static void FlyOutFieldEffect_FlyOffWithBird(struct Task *);
static void FlyOutFieldEffect_WaitFlyOff(struct Task *);
static void FlyOutFieldEffect_End(struct Task *);

static u8 CreateFlyBirdSprite(void);
static u8 GetFlyBirdAnimCompleted(u8);
static void StartFlyBirdSwoopDown(u8);
static void SetFlyBirdPlayerSpriteId(u8, u8);
static void SpriteCB_FlyBirdLeaveBall(struct Sprite *);
static void SpriteCB_FlyBirdSwoopDown(struct Sprite *);

static void Task_FlyIn(u8);
static void FlyInFieldEffect_BirdSwoopDown(struct Task *);
static void FlyInFieldEffect_FlyInWithBird(struct Task *);
static void FlyInFieldEffect_JumpOffBird(struct Task *);
static void FlyInFieldEffect_FieldMovePose(struct Task *);
static void FlyInFieldEffect_BirdReturnToBall(struct Task *);
static void FlyInFieldEffect_WaitBirdReturn(struct Task *);
static void FlyInFieldEffect_End(struct Task *);

static void Task_DestroyDeoxysRock(u8 taskId);
static void DestroyDeoxysRockEffect_CameraShake(s16*, u8);
static void DestroyDeoxysRockEffect_RockFragments(s16*, u8);
static void DestroyDeoxysRockEffect_WaitAndEnd(s16*, u8);
static void CreateDeoxysRockFragments(struct Sprite*);
static void SpriteCB_DeoxysRockFragment(struct Sprite* sprite);

static void Task_MoveDeoxysRock(u8 taskId);



// Static RAM declarations

static u8 sActiveList[32];

// External declarations
extern struct CompressedSpritePalette gMonPaletteTable[]; // GF made a mistake and did not extern it as const.
extern const struct CompressedSpritePalette gTrainerFrontPicPaletteTable[];
extern const struct CompressedSpriteSheet gTrainerFrontPicTable[];
extern u8 *gFieldEffectScriptPointers[];
extern const struct SpriteTemplate *const gFieldEffectObjectTemplatePointers[];

static const u32 sNewGameBirch_Gfx[] = INCBIN_U32("graphics/birch_speech/birch.4bpp");
static const u32 sUnusedBirchBeauty[] = INCBIN_U32("graphics/unused/intro_birch_beauty.4bpp");
static const u16 sNewGameBirch_Pal[16] = INCBIN_U16("graphics/birch_speech/birch.gbapal");
static const u32 sPokeballGlow_Gfx[] = INCBIN_U32("graphics/misc/pokeball_glow.4bpp");
static const u16 sPokeballGlow_Pal[16] = INCBIN_U16("graphics/field_effects/palettes/pokeball_glow.gbapal");
static const u32 sPokecenterMonitor0_Gfx[] = INCBIN_U32("graphics/misc/pokecenter_monitor/0.4bpp");
static const u32 sPokecenterMonitor1_Gfx[] = INCBIN_U32("graphics/misc/pokecenter_monitor/1.4bpp");
static const u32 sHofMonitorBig_Gfx[] = INCBIN_U32("graphics/misc/hof_monitor_big.4bpp");
static const u8 sHofMonitorSmall_Gfx[] = INCBIN_U8("graphics/misc/hof_monitor_small.4bpp");
static const u16 sHofMonitor_Pal[16] = INCBIN_U16("graphics/field_effects/palettes/hof_monitor.gbapal");

// Graphics for the lights streaking past your Pokemon when it uses a field move.
static const u32 sFieldMoveStreaksOutdoors_Gfx[] = INCBIN_U32("graphics/misc/field_move_streaks.4bpp");
static const u16 sFieldMoveStreaksOutdoors_Pal[16] = INCBIN_U16("graphics/misc/field_move_streaks.gbapal");
static const u16 sFieldMoveStreaksOutdoors_Tilemap[320] = INCBIN_U16("graphics/misc/field_move_streaks_map.bin");

// The following light streaks effect is used when the map is indoors
static const u32 sFieldMoveStreaksIndoors_Gfx[] = INCBIN_U32("graphics/misc/darkness_field_move_streaks.4bpp");
static const u16 sFieldMoveStreaksIndoors_Pal[16] = INCBIN_U16("graphics/misc/darkness_field_move_streaks.gbapal");
static const u16 sFieldMoveStreaksIndoors_Tilemap[320] = INCBIN_U16("graphics/misc/darkness_field_move_streaks_map.bin");

static const u16 sSpotlight_Pal[16] = INCBIN_U16("graphics/misc/spotlight.gbapal");
static const u8 sSpotlight_Gfx[] = INCBIN_U8("graphics/misc/spotlight.4bpp");
static const u8 sRockFragment_TopLeft[] = INCBIN_U8("graphics/misc/deoxys_rock_fragment_top_left.4bpp");
static const u8 sRockFragment_TopRight[] = INCBIN_U8("graphics/misc/deoxys_rock_fragment_top_right.4bpp");
static const u8 sRockFragment_BottomLeft[] = INCBIN_U8("graphics/misc/deoxys_rock_fragment_bottom_left.4bpp");
static const u8 sRockFragment_BottomRight[] = INCBIN_U8("graphics/misc/deoxys_rock_fragment_bottom_right.4bpp");

static const u16 sFieldEffectPopUp_Palette[16] = INCBIN_U16("graphics/interface/field_effect_popup_palette.gbapal");

bool8 (*const gFieldEffectScriptFuncs[])(u8 **, u32 *) =
{
    FieldEffectCmd_loadtiles,
    FieldEffectCmd_loadfadedpal,
    FieldEffectCmd_loadpal,
    FieldEffectCmd_callnative,
    FieldEffectCmd_end,
    FieldEffectCmd_loadgfx_callnative,
    FieldEffectCmd_loadtiles_callnative,
    FieldEffectCmd_loadfadedpal_callnative,
};

static const struct OamData sOam_64x64 =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
};

static const struct OamData sOam_8x8 =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
};

static const struct OamData sOam_16x16 =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
};

static const struct SpriteFrameImage sPicTable_NewGameBirch[] =
{
    obj_frame_tiles(sNewGameBirch_Gfx)
};

static const struct SpritePalette sSpritePalette_NewGameBirch =
{
    .data = sNewGameBirch_Pal,
    .tag = 0x1006
};

static const union AnimCmd sAnim_NewGameBirch[] =
{
    ANIMCMD_FRAME(.imageValue = 0, .duration = 1),
    ANIMCMD_END
};

static const union AnimCmd *const sAnimTable_NewGameBirch[] =
{
    sAnim_NewGameBirch
};

static const struct SpriteTemplate sSpriteTemplate_NewGameBirch =
{
    .tileTag = 0xFFFF,
    .paletteTag = 0x1006,
    .oam = &sOam_64x64,
    .anims = sAnimTable_NewGameBirch,
    .images = sPicTable_NewGameBirch,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

const struct SpritePalette gSpritePalette_PokeballGlow =
{
    .data = sPokeballGlow_Pal,
    .tag = FLDEFF_PAL_TAG_POKEBALL_GLOW
};

const struct SpritePalette gSpritePalette_HofMonitor =
{
    .data = sHofMonitor_Pal,
    .tag = FLDEFF_PAL_TAG_HOF_MONITOR
};

static const struct OamData sOam_32x16 =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x16),
    .x = 0,
    .size = SPRITE_SIZE(32x16),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
};

static const struct SpriteFrameImage sPicTable_PokeballGlow[] =
{
    obj_frame_tiles(sPokeballGlow_Gfx)
};

static const struct SpriteFrameImage sPicTable_PokecenterMonitor[] =
{
    obj_frame_tiles(sPokecenterMonitor0_Gfx),
    obj_frame_tiles(sPokecenterMonitor1_Gfx)
};

static const struct SpriteFrameImage sPicTable_HofMonitorBig[] =
{
    obj_frame_tiles(sHofMonitorBig_Gfx)
};

static const struct SpriteFrameImage sPicTable_HofMonitorSmall[] =
{
    {.data = sHofMonitorSmall_Gfx, .size = 0x200} // the macro breaks down here
};

static const struct Subsprite sSubsprites_PokecenterMonitor[] =
{
    {
        .x = -12, 
        .y =  -8, 
        .shape = SPRITE_SHAPE(16x8), 
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 0, 
        .priority = 2
    },
    {
        .x =  4, 
        .y = -8,
        .shape = SPRITE_SHAPE(8x8), 
        .size = SPRITE_SIZE(8x8), 
        .tileOffset = 2, 
        .priority = 2 
    },
    {
        .x = -12, 
        .y =   0, 
        .shape = SPRITE_SHAPE(16x8), 
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 3, 
        .priority = 2
    },
    {
        .x = 4, 
        .y = 0, 
        .shape = SPRITE_SHAPE(8x8), 
        .size = SPRITE_SIZE(8x8), 
        .tileOffset = 5, 
        .priority = 2
    }
};

static const struct SubspriteTable sSubspriteTable_PokecenterMonitor = subsprite_table(sSubsprites_PokecenterMonitor);

static const struct Subsprite sSubsprites_HofMonitorBig[] =
{
    {
        .x = -32, 
        .y = -8, 
        .shape = SPRITE_SHAPE(32x8), 
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0, 
        .priority = 2
    },
    {
        .x =  0, 
        .y = -8, 
        .shape = SPRITE_SHAPE(32x8), 
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4, 
        .priority = 2
    },
    {
        .x = -32, 
        .y =  0, 
        .shape = SPRITE_SHAPE(32x8), 
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 8, 
        .priority = 2
    },
    {
        .x =   0, 
        .y =  0, 
        .shape = SPRITE_SHAPE(32x8), 
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 12, 
        .priority = 2
    }
};

static const struct SubspriteTable sSubspriteTable_HofMonitorBig = subsprite_table(sSubsprites_HofMonitorBig);

const union AnimCmd sAnim_Static[] =
{
    ANIMCMD_FRAME(.imageValue = 0, .duration = 1),
    ANIMCMD_JUMP(0)
};

const union AnimCmd sAnim_Flicker[] =
{
    ANIMCMD_FRAME(.imageValue = 0, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 1, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 0, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 1, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 0, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 1, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 0, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 1, .duration = 16),
    ANIMCMD_END
};

// Flicker on and off, for the Pokéballs / monitors during the PokéCenter heal effect
const union AnimCmd *const sAnims_Flicker[] =
{
    sAnim_Static,
    sAnim_Flicker
};

static const union AnimCmd *const sAnims_HofMonitor[] =
{
    sAnim_Static
};

static const struct SpriteTemplate sSpriteTemplate_PokeballGlow =
{
    .tileTag = 0xFFFF,
    .paletteTag = FLDEFF_PAL_TAG_POKEBALL_GLOW,
    .oam = &sOam_8x8,
    .anims = sAnims_Flicker,
    .images = sPicTable_PokeballGlow,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_PokeballGlow
};

static const struct SpriteTemplate sSpriteTemplate_PokecenterMonitor =
{
    .tileTag = 0xFFFF,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &sOam_16x16,
    .anims = sAnims_Flicker,
    .images = sPicTable_PokecenterMonitor,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_PokecenterMonitor
};

static const struct SpriteTemplate sSpriteTemplate_HofMonitorBig =
{
    .tileTag = 0xFFFF,
    .paletteTag = FLDEFF_PAL_TAG_HOF_MONITOR,
    .oam = &sOam_16x16,
    .anims = sAnims_HofMonitor,
    .images = sPicTable_HofMonitorBig,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_HallOfFameMonitor
};

static const struct SpriteTemplate sSpriteTemplate_HofMonitorSmall =
{
    .tileTag = 0xFFFF,
    .paletteTag = FLDEFF_PAL_TAG_HOF_MONITOR,
    .oam = &sOam_32x16,
    .anims = sAnims_HofMonitor,
    .images = sPicTable_HofMonitorSmall,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_HallOfFameMonitor
};

void (*const sPokecenterHealEffectFuncs[])(struct Task *) =
{
    PokecenterHealEffect_Init,
    PokecenterHealEffect_WaitForBallPlacement,
    PokecenterHealEffect_WaitForBallFlashing,
    PokecenterHealEffect_WaitForSoundAndEnd
};

void (*const sHallOfFameRecordEffectFuncs[])(struct Task *) =
{
    HallOfFameRecordEffect_Init,
    HallOfFameRecordEffect_WaitForBallPlacement,
    HallOfFameRecordEffect_WaitForBallFlashing,
    HallOfFameRecordEffect_WaitForSoundAndEnd
};

void (*const sPokeballGlowEffectFuncs[])(struct Sprite *) =
{
    PokeballGlowEffect_PlaceBalls,
    PokeballGlowEffect_TryPlaySe,
    PokeballGlowEffect_Flash1,
    PokeballGlowEffect_Flash2,
    PokeballGlowEffect_WaitAfterFlash,
    PokeballGlowEffect_Dummy,
    PokeballGlowEffect_WaitForSound,
    PokeballGlowEffect_Idle
};

static const struct Coords16 sPokeballCoordOffsets[PARTY_SIZE] =
{
    {.x = 0, .y = 0},
    {.x = 6, .y = 0},
    {.x = 0, .y = 4},
    {.x = 6, .y = 4},
    {.x = 0, .y = 8},
    {.x = 6, .y = 8}
};

static const u8 sPokeballGlowReds[]   = {16, 12, 8, 0};
static const u8 sPokeballGlowGreens[] = {16, 12, 8, 0};
static const u8 sPokeballGlowBlues[]  = { 0,  0, 0, 0};

bool8 (*const sFallWarpFieldEffectFuncs[])(struct Task *) =
{
    FallWarpEffect_Init,
    FallWarpEffect_WaitWeather,
    FallWarpEffect_StartFall,
    FallWarpEffect_Fall,
    FallWarpEffect_Land,
    FallWarpEffect_CameraShake,
    FallWarpEffect_End,
};

bool8 (*const sEscalatorWarpOutFieldEffectFuncs[])(struct Task *) =
{
    EscalatorWarpOut_Init,
    EscalatorWarpOut_WaitForPlayer,
    EscalatorWarpOut_Up_Ride,
    EscalatorWarpOut_Up_End,
    EscalatorWarpOut_Down_Ride,
    EscalatorWarpOut_Down_End,
};

bool8 (*const sEscalatorWarpInFieldEffectFuncs[])(struct Task *) =
{
    EscalatorWarpIn_Init,
    EscalatorWarpIn_Down_Init,
    EscalatorWarpIn_Down_Ride,
    EscalatorWarpIn_Up_Init,
    EscalatorWarpIn_Up_Ride,
    EscalatorWarpIn_WaitForMovement,
    EscalatorWarpIn_End,
};

bool8 (*const sWaterfallFieldEffectFuncs[])(struct Task *, struct ObjectEvent *) =
{
    WaterfallFieldEffect_Init,
    WaterfallFieldEffect_ShowMon,
    WaterfallFieldEffect_WaitForShowMon,
    WaterfallFieldEffect_RideUp,
    WaterfallFieldEffect_ContinueRideOrEnd,
};

bool8 (*const sDiveFieldEffectFuncs[])(struct Task *) =
{
    DiveFieldEffect_Init,
    DiveFieldEffect_ShowMon,
    DiveFieldEffect_TryWarp,
};

bool8 (*const sLavaridgeGymB1FWarpEffectFuncs[])(struct Task *, struct ObjectEvent *, struct Sprite *) =
{
    LavaridgeGymB1FWarpEffect_Init,
    LavaridgeGymB1FWarpEffect_CameraShake,
    LavaridgeGymB1FWarpEffect_Launch,
    LavaridgeGymB1FWarpEffect_Rise,
    LavaridgeGymB1FWarpEffect_FadeOut,
    LavaridgeGymB1FWarpEffect_Warp,
};

bool8 (*const sLavaridgeGymB1FWarpExitEffectFuncs[])(struct Task *, struct ObjectEvent *, struct Sprite *) =
{
    LavaridgeGymB1FWarpExitEffect_Init,
    LavaridgeGymB1FWarpExitEffect_StartPopOut,
    LavaridgeGymB1FWarpExitEffect_PopOut,
    LavaridgeGymB1FWarpExitEffect_End,
};

bool8 (*const sLavaridgeGym1FWarpEffectFuncs[])(struct Task *, struct ObjectEvent *, struct Sprite *) =
{
    LavaridgeGym1FWarpEffect_Init,
    LavaridgeGym1FWarpEffect_AshPuff,
    LavaridgeGym1FWarpEffect_Disappear,
    LavaridgeGym1FWarpEffect_FadeOut,
    LavaridgeGym1FWarpEffect_Warp,
};

void (*const sEscapeRopeWarpOutEffectFuncs[])(struct Task *) =
{
    EscapeRopeWarpOutEffect_Init,
    EscapeRopeWarpOutEffect_Spin,
};

u32 FieldEffectStart(u8 id)
{
    u8 *script;
    u32 val;

    FieldEffectActiveListAdd(id);

    script = gFieldEffectScriptPointers[id];

    while (gFieldEffectScriptFuncs[*script](&script, &val))
        ;

    return val;
}

bool8 FieldEffectCmd_loadtiles(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadTiles(script);
    return TRUE;
}

bool8 FieldEffectCmd_loadfadedpal(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadFadedPalette(script);
    return TRUE;
}

bool8 FieldEffectCmd_loadpal(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadPalette(script);
    return TRUE;
}

bool8 FieldEffectCmd_callnative(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_CallNative(script, val);
    return TRUE;
}

bool8 FieldEffectCmd_end(u8 **script, u32 *val)
{
    return FALSE;
}

bool8 FieldEffectCmd_loadgfx_callnative(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadTiles(script);
    FieldEffectScript_LoadFadedPalette(script);
    FieldEffectScript_CallNative(script, val);
    return TRUE;
}

bool8 FieldEffectCmd_loadtiles_callnative(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadTiles(script);
    FieldEffectScript_CallNative(script, val);
    return TRUE;
}

bool8 FieldEffectCmd_loadfadedpal_callnative(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadFadedPalette(script);
    FieldEffectScript_CallNative(script, val);
    return TRUE;
}

u32 FieldEffectScript_ReadWord(u8 **script)
{
    return (*script)[0]
         + ((*script)[1] << 8)
         + ((*script)[2] << 16)
         + ((*script)[3] << 24);
}

void FieldEffectScript_LoadTiles(u8 **script)
{
    struct SpriteSheet *sheet = (struct SpriteSheet *)FieldEffectScript_ReadWord(script);
    if (GetSpriteTileStartByTag(sheet->tag) == 0xFFFF)
        LoadSpriteSheet(sheet);
    (*script) += 4;
}

void FieldEffectScript_LoadFadedPalette(u8 **script)
{
    struct SpritePalette *palette = (struct SpritePalette *)FieldEffectScript_ReadWord(script);
    LoadSpritePalette(palette);
    UpdatePaletteGammaType(IndexOfSpritePaletteTag(palette->tag), GAMMA_NORMAL);
    UpdateSpritePaletteWithWeather(IndexOfSpritePaletteTag(palette->tag));
    UpdateSpritePaletteWithTime(IndexOfSpritePaletteTag(palette->tag));
    (*script) += 4;
}

void FieldEffectScript_LoadPalette(u8 **script)
{
    struct SpritePalette *palette = (struct SpritePalette *)FieldEffectScript_ReadWord(script);
    LoadSpritePalette(palette);
    (*script) += 4;
}

void FieldEffectScript_CallNative(u8 **script, u32 *val)
{
    u32 (*func)(void) = (u32 (*)(void))FieldEffectScript_ReadWord(script);
    *val = func();
    (*script) += 4;
}

void FieldEffectFreeGraphicsResources(struct Sprite *sprite)
{
    u16 sheetTileStart = sprite->sheetTileStart;
    u32 paletteNum = sprite->oam.paletteNum;
    DestroySprite(sprite);
    FieldEffectFreeTilesIfUnused(sheetTileStart);
    FieldEffectFreePaletteIfUnused(paletteNum);
}

void FieldEffectStop(struct Sprite *sprite, u8 id)
{
    FieldEffectFreeGraphicsResources(sprite);
    FieldEffectActiveListRemove(id);
}

void FieldEffectFreeTilesIfUnused(u16 tileStart)
{
    u8 i;
    u16 tag = GetSpriteTileTagByTileStart(tileStart);

    if (tag != 0xFFFF)
    {
        for (i = 0; i < MAX_SPRITES; i++)
            if (gSprites[i].inUse && gSprites[i].usingSheet && tileStart == gSprites[i].sheetTileStart)
                return;
        FreeSpriteTilesByTag(tag);
    }
}

void FieldEffectFreePaletteIfUnused(u8 paletteNum)
{
    u8 i;
    u16 tag = GetSpritePaletteTagByPaletteNum(paletteNum);

    if (tag != 0xFFFF)
    {
        for (i = 0; i < MAX_SPRITES; i++)
            if (gSprites[i].inUse && gSprites[i].oam.paletteNum == paletteNum)
                return;
        FreeSpritePaletteByTag(tag);
    }
}

void FieldEffectActiveListClear(void)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sActiveList); i++)
        sActiveList[i] = 0xFF;
}

void FieldEffectActiveListAdd(u8 id)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sActiveList); i++)
    {
        if (sActiveList[i] == 0xFF)
        {
            sActiveList[i] = id;
            return;
        }
    }
}

void FieldEffectActiveListRemove(u8 id)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sActiveList); i++)
    {
        if (sActiveList[i] == id)
        {
            sActiveList[i] = 0xFF;
            return;
        }
    }
}

bool8 FieldEffectActiveListContains(u8 id)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sActiveList); i++)
        if (sActiveList[i] == id)
            return TRUE;
    return FALSE;
}

u8 CreateTrainerSprite(u8 trainerSpriteID, s16 x, s16 y, u8 subpriority, u8 *buffer)
{
    struct SpriteTemplate spriteTemplate;
    LoadCompressedSpritePaletteOverrideBuffer(&gTrainerFrontPicPaletteTable[trainerSpriteID], buffer);
    LoadCompressedSpriteSheetOverrideBuffer(&gTrainerFrontPicTable[trainerSpriteID], buffer);
    spriteTemplate.tileTag = gTrainerFrontPicTable[trainerSpriteID].tag;
    spriteTemplate.paletteTag = gTrainerFrontPicPaletteTable[trainerSpriteID].tag;
    spriteTemplate.oam = &sOam_64x64;
    spriteTemplate.anims = gDummySpriteAnimTable;
    spriteTemplate.images = NULL;
    spriteTemplate.affineAnims = gDummySpriteAffineAnimTable;
    spriteTemplate.callback = SpriteCallbackDummy;
    return CreateSprite(&spriteTemplate, x, y, subpriority);
}

void LoadTrainerGfx_TrainerCard(u8 gender, u16 palOffset, u8 *dest)
{
    LZDecompressVram(gTrainerFrontPicTable[gender].data, dest);
    LoadCompressedPalette(gTrainerFrontPicPaletteTable[gender].data, palOffset, 0x20);
}

u8 AddNewGameBirchObject(s16 x, s16 y, u8 subpriority)
{
    LoadSpritePalette(&sSpritePalette_NewGameBirch);
    return CreateSprite(&sSpriteTemplate_NewGameBirch, x, y, subpriority);
}

u8 CreateMonSprite_PicBox(u16 species, s16 x, s16 y, u8 subpriority)
{
    s32 spriteId = CreateMonPicSprite_HandleDeoxys(species, 0, 0x8000, 1, x, y, 0, gMonPaletteTable[species].tag);
    PreservePaletteInWeather(IndexOfSpritePaletteTag(gMonPaletteTable[species].tag) + 0x10);
    if (spriteId == 0xFFFF)
        return MAX_SPRITES;
    else
        return spriteId;
}

u8 CreateMonSprite_FieldMove(u16 species, u32 otId, u32 personality, s16 x, s16 y, u8 subpriority)
{
    const struct CompressedSpritePalette *spritePalette = GetMonSpritePalStructFromOtIdPersonality(species, otId, personality);
    u16 spriteId = CreateMonPicSprite_HandleDeoxys(species, otId, personality, 1, x, y, 0, spritePalette->tag);
    PreservePaletteInWeather(IndexOfSpritePaletteTag(spritePalette->tag) + 0x10);
    if (spriteId == 0xFFFF)
        return MAX_SPRITES;
    else
        return spriteId;
}

void FreeResourcesAndDestroySprite(struct Sprite *sprite, u8 spriteId)
{
    ResetPreservedPalettesInWeather();
    if (sprite->oam.affineMode != ST_OAM_AFFINE_OFF)
    {
        FreeOamMatrix(sprite->oam.matrixNum);
    }
    FreeAndDestroyMonPicSprite(spriteId);
}

// r, g, b are between 0 and 16
void MultiplyInvertedPaletteRGBComponents(u16 i, u8 r, u8 g, u8 b)
{
    int curRed, curGreen, curBlue;
    u16 color = gPlttBufferUnfaded[i];
    
    curRed   = (color & RGB_RED);
    curGreen = (color & RGB_GREEN) >>  5;
    curBlue  = (color & RGB_BLUE)  >> 10;
    
    curRed   += (((0x1F - curRed)   * r) >> 4);
    curGreen += (((0x1F - curGreen) * g) >> 4);
    curBlue  += (((0x1F - curBlue)  * b) >> 4);
    
    color  = curRed;
    color |= (curGreen <<  5);
    color |= (curBlue  << 10);
    
    gPlttBufferFaded[i] = color;
}

// r, g, b are between 0 and 16
void MultiplyPaletteRGBComponents(u16 i, u8 r, u8 g, u8 b)
{
    int curRed, curGreen, curBlue;
    u16 color = gPlttBufferUnfaded[i];
    
    curRed   = (color & RGB_RED);
    curGreen = (color & RGB_GREEN) >>  5;
    curBlue  = (color & RGB_BLUE)  >> 10;
    
    curRed   -= ((curRed   * r) >> 4);
    curGreen -= ((curGreen * g) >> 4);
    curBlue  -= ((curBlue  * b) >> 4);
    
    color  = curRed;
    color |= (curGreen <<  5);
    color |= (curBlue  << 10);
    
    gPlttBufferFaded[i] = color;
}

// Task data for Task_PokecenterHeal and Task_HallOfFameRecord
#define tState           data[0]
#define tNumMons         data[1]
#define tFirstBallX      data[2]
#define tFirstBallY      data[3]
#define tMonitorX        data[4]
#define tMonitorY        data[5]
#define tBallSpriteId    data[6]
#define tMonitorSpriteId data[7]
#define tStartHofFlash   data[15]

// Sprite data for SpriteCB_PokeballGlowEffect
#define sState      data[0]
#define sTimer      data[1]
#define sCounter    data[2]
#define sPlayHealSe data[5]
#define sNumMons    data[6]
#define sSpriteId   data[7]

// Sprite data for SpriteCB_PokeballGlow
#define sEffectSpriteId data[0]

bool8 FldEff_PokecenterHeal(void)
{
    u8 nPokemon;
    struct Task *task;

    nPokemon = CalculatePlayerPartyCount();
    task = &gTasks[CreateTask(Task_PokecenterHeal, 0xff)];
    task->tNumMons = nPokemon;
    task->tFirstBallX = 93;
    task->tFirstBallY = 36;
    task->tMonitorX = 124;
    task->tMonitorY = 24;
    return FALSE;
}

static void Task_PokecenterHeal(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    sPokecenterHealEffectFuncs[task->tState](task);
}

static void PokecenterHealEffect_Init(struct Task *task)
{
    task->tState++;
    task->tBallSpriteId = CreateGlowingPokeballsEffect(task->tNumMons, task->tFirstBallX, task->tFirstBallY, TRUE);
    task->tMonitorSpriteId = CreatePokecenterMonitorSprite(task->tMonitorX, task->tMonitorY);
}

static void PokecenterHealEffect_WaitForBallPlacement(struct Task *task)
{
    if (gSprites[task->tBallSpriteId].sState > 1)
    {
        gSprites[task->tMonitorSpriteId].sState++;
        task->tState++;
    }
}

static void PokecenterHealEffect_WaitForBallFlashing(struct Task *task)
{
    if (gSprites[task->tBallSpriteId].sState > 4)
    {
        task->tState++;
    }
}

static void PokecenterHealEffect_WaitForSoundAndEnd(struct Task *task)
{
    if (gSprites[task->tBallSpriteId].sState > 6)
    {
        DestroySprite(&gSprites[task->tBallSpriteId]);
        FieldEffectActiveListRemove(FLDEFF_POKECENTER_HEAL);
        DestroyTask(FindTaskIdByFunc(Task_PokecenterHeal));
    }
}

bool8 FldEff_HallOfFameRecord(void)
{
    u8 nPokemon;
    struct Task *task;

    nPokemon = CalculatePlayerPartyCount();
    task = &gTasks[CreateTask(Task_HallOfFameRecord, 0xff)];
    task->tNumMons = nPokemon;
    task->tFirstBallX = 117;
    task->tFirstBallY = 52;
    return FALSE;
}

static void Task_HallOfFameRecord(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    sHallOfFameRecordEffectFuncs[task->tState](task);
}

static void HallOfFameRecordEffect_Init(struct Task *task)
{
    u8 taskId;
    task->tState++;
    task->tBallSpriteId = CreateGlowingPokeballsEffect(task->tNumMons, task->tFirstBallX, task->tFirstBallY, FALSE);
    taskId = FindTaskIdByFunc(Task_HallOfFameRecord);
    CreateHofMonitorSprite(taskId, 120, 24, FALSE);
    CreateHofMonitorSprite(taskId, 40, 8, TRUE);
    CreateHofMonitorSprite(taskId, 72, 8, TRUE);
    CreateHofMonitorSprite(taskId, 168, 8, TRUE);
    CreateHofMonitorSprite(taskId, 200, 8, TRUE);
}

static void HallOfFameRecordEffect_WaitForBallPlacement(struct Task *task)
{
    if (gSprites[task->tBallSpriteId].sState > 1)
    {
        task->tStartHofFlash++;
        task->tState++;
    }
}

static void HallOfFameRecordEffect_WaitForBallFlashing(struct Task *task)
{
    if (gSprites[task->tBallSpriteId].sState > 4)
    {
        task->tState++;
    }
}

static void HallOfFameRecordEffect_WaitForSoundAndEnd(struct Task *task)
{
    if (gSprites[task->tBallSpriteId].sState > 6)
    {
        DestroySprite(&gSprites[task->tBallSpriteId]);
        FieldEffectActiveListRemove(FLDEFF_HALL_OF_FAME_RECORD);
        DestroyTask(FindTaskIdByFunc(Task_HallOfFameRecord));
    }
}

static u8 CreateGlowingPokeballsEffect(s16 numMons, s16 x, s16 y, bool16 playHealSe)
{
    u8 spriteId;
    struct Sprite *sprite;
    spriteId = CreateInvisibleSprite(SpriteCB_PokeballGlowEffect);
    sprite = &gSprites[spriteId];
    sprite->x2 = x;
    sprite->y2 = y;
    sprite->sPlayHealSe = playHealSe;
    sprite->sNumMons = numMons;
    sprite->sSpriteId = spriteId;
    return spriteId;
}

static void SpriteCB_PokeballGlowEffect(struct Sprite *sprite)
{
    sPokeballGlowEffectFuncs[sprite->sState](sprite);
}

static void PokeballGlowEffect_PlaceBalls(struct Sprite *sprite)
{
    u8 spriteId;
    if (sprite->sTimer == 0 || (--sprite->sTimer) == 0)
    {
        sprite->sTimer = 25;
        spriteId = CreateSpriteAtEnd(&sSpriteTemplate_PokeballGlow, sPokeballCoordOffsets[sprite->sCounter].x + sprite->x2, sPokeballCoordOffsets[sprite->sCounter].y + sprite->y2, 0);
        gSprites[spriteId].oam.priority = 2;
        gSprites[spriteId].sEffectSpriteId = sprite->sSpriteId;
        sprite->sCounter++;
        sprite->sNumMons--;
        PlaySE(SE_BALL);
    }
    if (sprite->sNumMons == 0)
    {
        sprite->sTimer = 32;
        sprite->sState++;
    }
}

static void PokeballGlowEffect_TryPlaySe(struct Sprite *sprite)
{
    if ((--sprite->sTimer) == 0)
    {
        sprite->sState++;
        sprite->sTimer = 8;
        sprite->sCounter = 0;
        sprite->data[3] = 0;
        if (sprite->sPlayHealSe)
        {
            PlayFanfare(MUS_HEAL);
        }
    }
}

static void PokeballGlowEffect_Flash1(struct Sprite *sprite)
{
    u8 phase;
    if ((--sprite->sTimer) == 0)
    {
        sprite->sTimer = 8;
        sprite->sCounter++;
        sprite->sCounter &= 3;

        if (sprite->sCounter == 0)
            sprite->data[3]++;
    }
    phase = (sprite->sCounter + 3) & 3;
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(FLDEFF_PAL_TAG_POKEBALL_GLOW) << 4) + 0x108, sPokeballGlowReds[phase], sPokeballGlowGreens[phase], sPokeballGlowBlues[phase]);
    phase = (sprite->sCounter + 2) & 3;
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(FLDEFF_PAL_TAG_POKEBALL_GLOW) << 4) + 0x106, sPokeballGlowReds[phase], sPokeballGlowGreens[phase], sPokeballGlowBlues[phase]);
    phase = (sprite->sCounter + 1) & 3;
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(FLDEFF_PAL_TAG_POKEBALL_GLOW) << 4) + 0x102, sPokeballGlowReds[phase], sPokeballGlowGreens[phase], sPokeballGlowBlues[phase]);
    phase = sprite->sCounter;
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(FLDEFF_PAL_TAG_POKEBALL_GLOW) << 4) + 0x105, sPokeballGlowReds[phase], sPokeballGlowGreens[phase], sPokeballGlowBlues[phase]);
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(FLDEFF_PAL_TAG_POKEBALL_GLOW) << 4) + 0x103, sPokeballGlowReds[phase], sPokeballGlowGreens[phase], sPokeballGlowBlues[phase]);
    if (sprite->data[3] > 2)
    {
        sprite->sState++;
        sprite->sTimer = 8;
        sprite->sCounter = 0;
    }
}

static void PokeballGlowEffect_Flash2(struct Sprite *sprite)
{
    u8 phase;
    if ((--sprite->sTimer) == 0)
    {
        sprite->sTimer = 8;
        sprite->sCounter++;
        sprite->sCounter &= 3;
        if (sprite->sCounter == 3)
        {
            sprite->sState++;
            sprite->sTimer = 30;
        }
    }
    phase = sprite->sCounter;
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(FLDEFF_PAL_TAG_POKEBALL_GLOW) << 4) + 0x108, sPokeballGlowReds[phase], sPokeballGlowGreens[phase], sPokeballGlowBlues[phase]);
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(FLDEFF_PAL_TAG_POKEBALL_GLOW) << 4) + 0x106, sPokeballGlowReds[phase], sPokeballGlowGreens[phase], sPokeballGlowBlues[phase]);
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(FLDEFF_PAL_TAG_POKEBALL_GLOW) << 4) + 0x102, sPokeballGlowReds[phase], sPokeballGlowGreens[phase], sPokeballGlowBlues[phase]);
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(FLDEFF_PAL_TAG_POKEBALL_GLOW) << 4) + 0x105, sPokeballGlowReds[phase], sPokeballGlowGreens[phase], sPokeballGlowBlues[phase]);
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(FLDEFF_PAL_TAG_POKEBALL_GLOW) << 4) + 0x103, sPokeballGlowReds[phase], sPokeballGlowGreens[phase], sPokeballGlowBlues[phase]);
}

static void PokeballGlowEffect_WaitAfterFlash(struct Sprite *sprite)
{
    if ((--sprite->sTimer) == 0)
    {
        sprite->sState++;
    }
}

static void PokeballGlowEffect_Dummy(struct Sprite *sprite)
{
    sprite->sState++;
}

static void PokeballGlowEffect_WaitForSound(struct Sprite *sprite)
{
    if (sprite->sPlayHealSe == FALSE || IsFanfareTaskInactive())
    {
        sprite->sState++;
    }
}

static void PokeballGlowEffect_Idle(struct Sprite *sprite)
{
    // Idle until destroyed
}

static void SpriteCB_PokeballGlow(struct Sprite *sprite)
{
    if (gSprites[sprite->sEffectSpriteId].sState > 4)
    {
        FieldEffectFreeGraphicsResources(sprite);
    }
}

static u8 CreatePokecenterMonitorSprite(s16 x, s16 y)
{
    u8 spriteId;
    struct Sprite *sprite;
    spriteId = CreateSpriteAtEnd(&sSpriteTemplate_PokecenterMonitor, x, y, 0);
    sprite = &gSprites[spriteId];
    sprite->oam.priority = 2;
    sprite->invisible = TRUE;
    SetSubspriteTables(sprite, &sSubspriteTable_PokecenterMonitor);
    return spriteId;
}

static void SpriteCB_PokecenterMonitor(struct Sprite *sprite)
{
    if (sprite->data[0] != 0)
    {
        sprite->data[0] = 0;
        sprite->invisible = FALSE;
        StartSpriteAnim(sprite, 1);
    }
    if (sprite->animEnded)
    {
        FieldEffectFreeGraphicsResources(sprite);
    }
}

static void CreateHofMonitorSprite(s16 taskId, s16 x, s16 y, bool8 isSmallMonitor)
{
    u8 spriteId;
    if (!isSmallMonitor)
    {
        spriteId = CreateSpriteAtEnd(&sSpriteTemplate_HofMonitorBig, x, y, 0);
        SetSubspriteTables(&gSprites[spriteId], &sSubspriteTable_HofMonitorBig);
    } else
    {
        spriteId = CreateSpriteAtEnd(&sSpriteTemplate_HofMonitorSmall, x, y, 0);
    }
    gSprites[spriteId].invisible = TRUE;
    gSprites[spriteId].data[0] = taskId;
}

static void SpriteCB_HallOfFameMonitor(struct Sprite *sprite)
{
    if (gTasks[sprite->data[0]].tStartHofFlash)
    {
        if (sprite->data[1] == 0 || (--sprite->data[1]) == 0)
        {
            sprite->data[1] = 16;
            sprite->invisible ^= 1;
        }
        sprite->data[2]++;
    }
    if (sprite->data[2] > 127)
    {
        FieldEffectFreeGraphicsResources(sprite);
    }
}

#undef tState
#undef tNumMons
#undef tFirstBallX
#undef tFirstBallY
#undef tMonitorX
#undef tMonitorY
#undef tBallSpriteId
#undef tMonitorSpriteId
#undef tStartHofFlash
#undef sState
#undef sTimer
#undef sCounter
#undef sPlayHealSe
#undef sNumMons
#undef sSpriteId
#undef sEffectSpriteId

void ReturnToFieldFromFlyMapSelect(void)
{
    SetMainCallback2(CB2_ReturnToField);
    gFieldCallback = FieldCallback_UseFly;
}

static void FieldCallback_UseFly(void)
{
    FadeInFromBlack();
    CreateTask(Task_UseFly, 0);
    ScriptContext2_Enable();
    FreezeObjectEvents();
    gFieldCallback = NULL;
}

static void Task_UseFly(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    if (!task->data[0])
    {
        if (!IsWeatherNotFadingIn())
            return;

        gFieldEffectArguments[0] = GetCursorSelectionMonId();
        if ((int)gFieldEffectArguments[0] > PARTY_SIZE - 1)
            gFieldEffectArguments[0] = 0;

        FieldEffectStart(FLDEFF_USE_FLY);
        task->data[0]++;
    }
    if (!FieldEffectActiveListContains(FLDEFF_USE_FLY))
    {
        Overworld_ResetStateAfterFly();
        WarpIntoMap();
        SetMainCallback2(CB2_LoadMap);
        gFieldCallback = FieldCallback_FlyIntoMap;
        DestroyTask(taskId);
    }
}

static void FieldCallback_FlyIntoMap(void)
{
    Overworld_PlaySpecialMapMusic();
    FadeInFromBlack();
    CreateTask(Task_FlyIntoMap, 0);
    gObjectEvents[gPlayerAvatar.objectEventId].invisible = TRUE;
    if (gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_SURFING)
    {
        ObjectEventTurn(&gObjectEvents[gPlayerAvatar.objectEventId], DIR_WEST);
    }
    ScriptContext2_Enable();
    FreezeObjectEvents();
    gFieldCallback = NULL;
}

static void Task_FlyIntoMap(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    if (task->data[0] == 0)
    {
        if (gPaletteFade.active)
        {
            return;
        }
        FieldEffectStart(FLDEFF_FLY_IN);
        task->data[0]++;
    }
    if (!FieldEffectActiveListContains(FLDEFF_FLY_IN))
    {
        ScriptContext2_Disable();
        UnfreezeObjectEvents();
        DestroyTask(taskId);
    }
}

#define tState      data[0]
#define tFallOffset data[1]
#define tTotalFall  data[2]
#define tSetTrigger data[3]
#define tSubsprMode data[4]

#define tVertShake  data[1] // re-used
#define tNumShakes  data[2]

void FieldCB_FallWarpExit(void)
{
    Overworld_PlaySpecialMapMusic();
    WarpFadeInScreen();
    ScriptContext2_Enable();
    FreezeObjectEvents();
    CreateTask(Task_FallWarpFieldEffect, 0);
    gFieldCallback = NULL;
}

static void Task_FallWarpFieldEffect(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    while (sFallWarpFieldEffectFuncs[task->tState](task));
}

static bool8 FallWarpEffect_Init(struct Task *task)
{
    struct ObjectEvent *playerObject;
    struct Sprite *playerSprite;
    playerObject = &gObjectEvents[gPlayerAvatar.objectEventId];
    playerSprite = &gSprites[gPlayerAvatar.spriteId];
    CameraObjectReset2();
    gObjectEvents[gPlayerAvatar.objectEventId].invisible = TRUE;
    gPlayerAvatar.preventStep = TRUE;
    ObjectEventSetHeldMovement(playerObject, GetFaceDirectionMovementAction(GetPlayerFacingDirection()));
    task->tSubsprMode = playerSprite->subspriteMode;
    playerObject->fixedPriority = 1;
    playerSprite->oam.priority = 1;
    playerSprite->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
    task->tState++;
    return TRUE;
}

static bool8 FallWarpEffect_WaitWeather(struct Task *task)
{
    if (IsWeatherNotFadingIn())
        task->tState++;

    return FALSE;
}

static bool8 FallWarpEffect_StartFall(struct Task *task)
{
    struct Sprite *sprite;
    s16 centerToCornerVecY;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    centerToCornerVecY = -(sprite->centerToCornerVecY << 1);
    sprite->y2 = -(sprite->y + sprite->centerToCornerVecY + gSpriteCoordOffsetY + centerToCornerVecY);
    task->tFallOffset = 1;
    task->tTotalFall = 0;
    gObjectEvents[gPlayerAvatar.objectEventId].invisible = FALSE;
    PlaySE(SE_FALL);
    task->tState++;
    return FALSE;
}

static bool8 FallWarpEffect_Fall(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    struct Sprite *sprite;

    objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->y2 += task->tFallOffset;
    if (task->tFallOffset < 8)
    {
        task->tTotalFall += task->tFallOffset;

        if (task->tTotalFall & 0xf)
            task->tFallOffset <<= 1;
    }
    if (task->tSetTrigger == FALSE && sprite->y2 >= -16)
    {
        task->tSetTrigger++;
        objectEvent->fixedPriority = 0;
        sprite->subspriteMode = task->tSubsprMode;
        objectEvent->triggerGroundEffectsOnMove = 1;
    }
    if (sprite->y2 >= 0)
    {
        PlaySE(SE_M_STRENGTH);
        objectEvent->triggerGroundEffectsOnStop = 1;
        objectEvent->landingJump = 1;
        sprite->y2 = 0;
        task->tState++;
    }
    return FALSE;
}

static bool8 FallWarpEffect_Land(struct Task *task)
{
    task->tState++;
    task->tVertShake = 4;
    task->tNumShakes = 0;
    SetCameraPanningCallback(NULL);
    return TRUE;
}

static bool8 FallWarpEffect_CameraShake(struct Task *task)
{
    SetCameraPanning(0, task->tVertShake);
    task->tVertShake = -task->tVertShake;
    task->tNumShakes++;

    if ((task->tNumShakes & 3) == 0)
        task->tVertShake >>= 1;

    if (task->tVertShake == 0)
        task->tState++;

    return FALSE;
}

static bool8 FallWarpEffect_End(struct Task *task)
{
    gPlayerAvatar.preventStep = FALSE;
    ScriptContext2_Disable();
    CameraObjectReset1();
    UnfreezeObjectEvents();
    InstallCameraPanAheadCallback();
    DestroyTask(FindTaskIdByFunc(Task_FallWarpFieldEffect));
    
    FollowMe_WarpSetEnd();
    
    return FALSE;
}

#undef tState
#undef tFallOffset
#undef tTotalFall
#undef tSetTrigger
#undef tSubsprMode
#undef tVertShake
#undef tNumShakes

#define tState   data[0]
#define tGoingUp data[1]

void StartEscalatorWarp(u8 metatileBehavior, u8 priority)
{
    u8 taskId;
    taskId = CreateTask(Task_EscalatorWarpOut, priority);
    gTasks[taskId].tGoingUp = FALSE;
    if (metatileBehavior == MB_UP_ESCALATOR)
    {
        gTasks[taskId].tGoingUp = TRUE;
    }
}

static void Task_EscalatorWarpOut(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    while (sEscalatorWarpOutFieldEffectFuncs[task->tState](task));
}

static bool8 EscalatorWarpOut_Init(struct Task *task)
{
    FreezeObjectEvents();
    CameraObjectReset2();
    StartEscalator(task->tGoingUp);
    task->tState++;
    return FALSE;
}

static bool8 EscalatorWarpOut_WaitForPlayer(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (!ObjectEventIsMovementOverridden(objectEvent) || ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        ObjectEventSetHeldMovement(objectEvent, GetFaceDirectionMovementAction(GetPlayerFacingDirection()));
        task->tState++;
        task->data[2] = 0;
        task->data[3] = 0;

        EscalatorMoveFollower(task->data[1]);
        if ((u8)task->tGoingUp == FALSE)
        {
            task->tState = 4; // jump to EscalatorWarpOut_Down_Ride
        }
        PlaySE(SE_ESCALATOR);
    }
    return FALSE;
}

static bool8 EscalatorWarpOut_Up_Ride(struct Task *task)
{
    RideUpEscalatorOut(task);
    if (task->data[2] > 3)
    {
        FadeOutAtEndOfEscalator();
        task->tState++;
    }
    return FALSE;
}

static bool8 EscalatorWarpOut_Up_End(struct Task *task)
{
    RideUpEscalatorOut(task);
    WarpAtEndOfEscalator();
    return FALSE;
}

static bool8 EscalatorWarpOut_Down_Ride(struct Task *task)
{
    RideDownEscalatorOut(task);
    if (task->data[2] > 3)
    {
        FadeOutAtEndOfEscalator();
        task->tState++;
    }
    return FALSE;
}

static bool8 EscalatorWarpOut_Down_End(struct Task *task)
{
    RideDownEscalatorOut(task);
    WarpAtEndOfEscalator();
    return FALSE;
}

static void RideUpEscalatorOut(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->x2 = Cos(0x84, task->data[2]);
    sprite->y2 = Sin(0x94, task->data[2]);
    task->data[3]++;
    if (task->data[3] & 1)
    {
        task->data[2]++;
    }
}

static void RideDownEscalatorOut(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->x2 = Cos(0x7c, task->data[2]);
    sprite->y2 = Sin(0x76, task->data[2]);
    task->data[3]++;
    if (task->data[3] & 1)
    {
        task->data[2]++;
    }
}

static void FadeOutAtEndOfEscalator(void)
{
    TryFadeOutOldMapMusic();
    WarpFadeOutScreen();
}

static void WarpAtEndOfEscalator(void)
{
    if (!gPaletteFade.active && BGMusicStopped() == TRUE)
    {
        StopEscalator();
        WarpIntoMap();
        gFieldCallback = FieldCallback_EscalatorWarpIn;
        SetMainCallback2(CB2_LoadMap);
        DestroyTask(FindTaskIdByFunc(Task_EscalatorWarpOut));
    }
}

#undef tState
#undef tGoingUp

static void FieldCallback_EscalatorWarpIn(void)
{
    Overworld_PlaySpecialMapMusic();
    WarpFadeInScreen();
    ScriptContext2_Enable();
    CreateTask(Task_EscalatorWarpIn, 0);
    gFieldCallback = NULL;
}

#define tState data[0]

static void Task_EscalatorWarpIn(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    while (sEscalatorWarpInFieldEffectFuncs[task->tState](task));
}

static bool8 EscalatorWarpIn_Init(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    s16 x;
    s16 y;
    u8 behavior;
    CameraObjectReset2();
    objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    ObjectEventSetHeldMovement(objectEvent, GetFaceDirectionMovementAction(DIR_EAST));
    PlayerGetDestCoords(&x, &y);
    behavior = MapGridGetMetatileBehaviorAt(x, y);
    task->tState++;
    task->data[1] = 16;

    if (behavior == MB_DOWN_ESCALATOR)
    {
        // If dest is down escalator tile, player is riding up
        behavior = TRUE;
        task->tState = 3; // jump to EscalatorWarpIn_Up_Init
    } 
    else // MB_UP_ESCALATOR
    {
        // If dest is up escalator tile, player is riding down
        behavior = FALSE;
    }
    StartEscalator(behavior);
    EscalatorMoveFollowerFinish();
    return TRUE;
}

static bool8 EscalatorWarpIn_Down_Init(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->x2 = Cos(0x84, task->data[1]);
    sprite->y2 = Sin(0x94, task->data[1]);
    task->tState++;
    return FALSE;
}

static bool8 EscalatorWarpIn_Down_Ride(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->x2 = Cos(0x84, task->data[1]);
    sprite->y2 = Sin(0x94, task->data[1]);
    task->data[2]++;
    if (task->data[2] & 1)
    {
        task->data[1]--;
    }
    if (task->data[1] == 0)
    {
        sprite->x2 = 0;
        sprite->y2 = 0;
        task->tState = 5;
    }
    return FALSE;
}

static bool8 EscalatorWarpIn_Up_Init(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->x2 = Cos(0x7c, task->data[1]);
    sprite->y2 = Sin(0x76, task->data[1]);
    task->tState++;
    return FALSE;
}

static bool8 EscalatorWarpIn_Up_Ride(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->x2 = Cos(0x7c, task->data[1]);
    sprite->y2 = Sin(0x76, task->data[1]);
    task->data[2]++;
    if (task->data[2] & 1)
    {
        task->data[1]--;
    }
    if (task->data[1] == 0)
    {
        sprite->x2 = 0;
        sprite->y2 = 0;
        task->tState++;
    }
    return FALSE;
}

static bool8 EscalatorWarpIn_WaitForMovement(struct Task *task)
{
    if (IsEscalatorMoving())
    {
        return FALSE;
    }
    StopEscalator();
    task->tState++;
    return TRUE;
}

static bool8 EscalatorWarpIn_End(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        CameraObjectReset1();
        ScriptContext2_Disable();
        ObjectEventSetHeldMovement(objectEvent, GetWalkNormalMovementAction(DIR_EAST));
        DestroyTask(FindTaskIdByFunc(Task_EscalatorWarpIn));
    }
    return FALSE;
}

#undef tState

#define tState data[0]
#define tMonId data[1]

bool8 FldEff_UseWaterfall(void)
{
    u8 taskId;
    taskId = CreateTask(Task_UseWaterfall, 0xff);
    gTasks[taskId].tMonId = gFieldEffectArguments[0];
    Task_UseWaterfall(taskId);
    return FALSE;
}

static void Task_UseWaterfall(u8 taskId)
{
    while (sWaterfallFieldEffectFuncs[gTasks[taskId].tState](&gTasks[taskId], &gObjectEvents[gPlayerAvatar.objectEventId]));
}

static bool8 WaterfallFieldEffect_Init(struct Task *task, struct ObjectEvent *objectEvent)
{
    ScriptContext2_Enable();
    gPlayerAvatar.preventStep = TRUE;
    task->tState++;
    return FALSE;
}

static bool8 WaterfallFieldEffect_ShowMon(struct Task *task, struct ObjectEvent *objectEvent)
{
    ScriptContext2_Enable();
    if (!ObjectEventIsMovementOverridden(objectEvent))
    {
        ObjectEventClearHeldMovementIfFinished(objectEvent);
        gFieldEffectArguments[0] = task->tMonId;
        FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
        task->tState++;
    }
    return FALSE;
}

static bool8 WaterfallFieldEffect_WaitForShowMon(struct Task *task, struct ObjectEvent *objectEvent)
{
    if (FieldEffectActiveListContains(FLDEFF_FIELD_MOVE_SHOW_MON))
    {
        return FALSE;
    }
    task->tState++;
    return TRUE;
}

static bool8 WaterfallFieldEffect_RideUp(struct Task *task, struct ObjectEvent *objectEvent)
{
    ObjectEventSetHeldMovement(objectEvent, GetWalkSlowMovementAction(DIR_NORTH));
    task->tState++;
    return FALSE;
}

static bool8 WaterfallFieldEffect_ContinueRideOrEnd(struct Task *task, struct ObjectEvent *objectEvent)
{
    if (!ObjectEventClearHeldMovementIfFinished(objectEvent))
        return FALSE;

    if (MetatileBehavior_IsWaterfall(objectEvent->currentMetatileBehavior))
    {
        // Still ascending waterfall, back to WaterfallFieldEffect_RideUp
        task->tState = 3;
        return TRUE;
    }

    ScriptContext2_Disable();
    gPlayerAvatar.preventStep = FALSE;
    DestroyTask(FindTaskIdByFunc(Task_UseWaterfall));
    FieldEffectActiveListRemove(FLDEFF_USE_WATERFALL);
    return FALSE;
}

#undef tState
#undef tMonId

bool8 FldEff_UseDive(void)
{
    u8 taskId;
    taskId = CreateTask(Task_UseDive, 0xff);
    gTasks[taskId].data[15] = gFieldEffectArguments[0];
    gTasks[taskId].data[14] = gFieldEffectArguments[1];
    Task_UseDive(taskId);
    return FALSE;
}

void Task_UseDive(u8 taskId)
{
    while (sDiveFieldEffectFuncs[gTasks[taskId].data[0]](&gTasks[taskId]));
}

static bool8 DiveFieldEffect_Init(struct Task *task)
{
    gPlayerAvatar.preventStep = TRUE;
    task->data[0]++;
    return FALSE;
}

static bool8 DiveFieldEffect_ShowMon(struct Task *task)
{
    ScriptContext2_Enable();
    gFieldEffectArguments[0] = task->data[15];
    FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
    task->data[0]++;
    return FALSE;
}

static bool8 DiveFieldEffect_TryWarp(struct Task *task)
{
    struct MapPosition mapPosition;
    PlayerGetDestCoords(&mapPosition.x, &mapPosition.y);

    // Wait for show mon first
    if (!FieldEffectActiveListContains(FLDEFF_FIELD_MOVE_SHOW_MON))
    {
        TryDoDiveWarp(&mapPosition, gObjectEvents[gPlayerAvatar.objectEventId].currentMetatileBehavior);
        DestroyTask(FindTaskIdByFunc(Task_UseDive));
        FieldEffectActiveListRemove(FLDEFF_USE_DIVE);
    }
    return FALSE;
}

void StartLavaridgeGymB1FWarp(u8 priority)
{
    CreateTask(Task_LavaridgeGymB1FWarp, priority);
}

static void Task_LavaridgeGymB1FWarp(u8 taskId)
{
    while (sLavaridgeGymB1FWarpEffectFuncs[gTasks[taskId].data[0]](&gTasks[taskId], &gObjectEvents[gPlayerAvatar.objectEventId], &gSprites[gPlayerAvatar.spriteId]));
}

static bool8 LavaridgeGymB1FWarpEffect_Init(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    FreezeObjectEvents();
    CameraObjectReset2();
    SetCameraPanningCallback(NULL);
    gPlayerAvatar.preventStep = TRUE;
    objectEvent->fixedPriority = 1;
    task->data[1] = 1;
    task->data[0]++;
    return TRUE;
}

static bool8 LavaridgeGymB1FWarpEffect_CameraShake(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    SetCameraPanning(0, task->data[1]);
    task->data[1] = -task->data[1];
    task->data[2]++;
    if (task->data[2] > 7)
    {
        task->data[2] = 0;
        task->data[0]++;
    }
    return FALSE;
}

static bool8 LavaridgeGymB1FWarpEffect_Launch(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    sprite->y2 = 0;
    task->data[3] = 1;
    gFieldEffectArguments[0] = objectEvent->currentCoords.x;
    gFieldEffectArguments[1] = objectEvent->currentCoords.y;
    gFieldEffectArguments[2] = sprite->subpriority - 1;
    gFieldEffectArguments[3] = sprite->oam.priority;
    FieldEffectStart(FLDEFF_ASH_LAUNCH);
    PlaySE(SE_M_EXPLOSION);
    task->data[0]++;
    return TRUE;
}

static bool8 LavaridgeGymB1FWarpEffect_Rise(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    s16 centerToCornerVecY;
    SetCameraPanning(0, task->data[1]);
    if (task->data[1] = -task->data[1], ++task->data[2] <= 17)
    {
        if (!(task->data[2] & 1) && (task->data[1] <= 3))
        {
            task->data[1] <<= 1;
        }
    } else if (!(task->data[2] & 4) && (task->data[1] > 0))
    {
        task->data[1] >>= 1;
    }
    if (task->data[2] > 6)
    {
        centerToCornerVecY = -(sprite->centerToCornerVecY << 1);
        if (sprite->y2 > -(sprite->y + sprite->centerToCornerVecY + gSpriteCoordOffsetY + centerToCornerVecY))
        {
            sprite->y2 -= task->data[3];
            if (task->data[3] <= 7)
            {
                task->data[3]++;
            }
        } else
        {
            task->data[4] = 1;
        }
    }
    if (task->data[5] == 0 && sprite->y2 < -0x10)
    {
        task->data[5]++;
        objectEvent->fixedPriority = 1;
        sprite->oam.priority = 1;
        sprite->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
    }
    if (task->data[1] == 0 && task->data[4] != 0)
    {
        task->data[0]++;
    }
    return FALSE;
}

static bool8 LavaridgeGymB1FWarpEffect_FadeOut(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    TryFadeOutOldMapMusic();
    WarpFadeOutScreen();
    task->data[0]++;
    return FALSE;
}

static bool8 LavaridgeGymB1FWarpEffect_Warp(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (!gPaletteFade.active && BGMusicStopped() == TRUE)
    {
        WarpIntoMap();
        gFieldCallback = FieldCB_LavaridgeGymB1FWarpExit;
        SetMainCallback2(CB2_LoadMap);
        DestroyTask(FindTaskIdByFunc(Task_LavaridgeGymB1FWarp));
    }
    return FALSE;
}

static void FieldCB_LavaridgeGymB1FWarpExit(void)
{
    Overworld_PlaySpecialMapMusic();
    WarpFadeInScreen();
    ScriptContext2_Enable();
    gFieldCallback = NULL;
    CreateTask(Task_LavaridgeGymB1FWarpExit, 0);
}

static void Task_LavaridgeGymB1FWarpExit(u8 taskId)
{
    while (sLavaridgeGymB1FWarpExitEffectFuncs[gTasks[taskId].data[0]](&gTasks[taskId], &gObjectEvents[gPlayerAvatar.objectEventId], &gSprites[gPlayerAvatar.spriteId]));
}

static bool8 LavaridgeGymB1FWarpExitEffect_Init(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    CameraObjectReset2();
    FreezeObjectEvents();
    gPlayerAvatar.preventStep = TRUE;
    objectEvent->invisible = TRUE;
    task->data[0]++;
    return FALSE;
}

static bool8 LavaridgeGymB1FWarpExitEffect_StartPopOut(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (IsWeatherNotFadingIn())
    {
        gFieldEffectArguments[0] = objectEvent->currentCoords.x;
        gFieldEffectArguments[1] = objectEvent->currentCoords.y;
        gFieldEffectArguments[2] = sprite->subpriority - 1;
        gFieldEffectArguments[3] = sprite->oam.priority;
        task->data[1] = FieldEffectStart(FLDEFF_ASH_PUFF);
        task->data[0]++;
    }
    return FALSE;
}

static bool8 LavaridgeGymB1FWarpExitEffect_PopOut(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    sprite = &gSprites[task->data[1]];
    if (sprite->animCmdIndex > 1)
    {
        task->data[0]++;
        objectEvent->invisible = FALSE;
        CameraObjectReset1();
        PlaySE(SE_M_DIG);
        ObjectEventSetHeldMovement(objectEvent, GetJumpMovementAction(DIR_EAST));
    }
    return FALSE;
}

static bool8 LavaridgeGymB1FWarpExitEffect_End(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        gPlayerAvatar.preventStep = FALSE;
        ScriptContext2_Disable();
        UnfreezeObjectEvents();
        DestroyTask(FindTaskIdByFunc(Task_LavaridgeGymB1FWarpExit));
    }
    return FALSE;
}

// For the ash effect when jumping off the Lavaridge Gym B1F warp tiles
u8 FldEff_AshLaunch(void)
{
    u8 spriteId;
    SetSpritePosToOffsetMapCoords((s16 *)&gFieldEffectArguments[0], (s16 *)&gFieldEffectArguments[1], 8, 8);
    spriteId = CreateSpriteAtEnd(gFieldEffectObjectTemplatePointers[FLDEFFOBJ_ASH_LAUNCH], gFieldEffectArguments[0], gFieldEffectArguments[1], gFieldEffectArguments[2]);
    gSprites[spriteId].oam.priority = gFieldEffectArguments[3];
    gSprites[spriteId].coordOffsetEnabled = TRUE;
    return spriteId;
}

void SpriteCB_AshLaunch(struct Sprite *sprite)
{
    if (sprite->animEnded)
        FieldEffectStop(sprite, FLDEFF_ASH_LAUNCH);
}

void StartLavaridgeGym1FWarp(u8 priority)
{
    CreateTask(Task_LavaridgeGym1FWarp, priority);
}

static void Task_LavaridgeGym1FWarp(u8 taskId)
{
    while(sLavaridgeGym1FWarpEffectFuncs[gTasks[taskId].data[0]](&gTasks[taskId], &gObjectEvents[gPlayerAvatar.objectEventId], &gSprites[gPlayerAvatar.spriteId]));
}

static bool8 LavaridgeGym1FWarpEffect_Init(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    FreezeObjectEvents();
    CameraObjectReset2();
    gPlayerAvatar.preventStep = TRUE;
    objectEvent->fixedPriority = 1;
    task->data[0]++;
    return FALSE;
}

static bool8 LavaridgeGym1FWarpEffect_AshPuff(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        if (task->data[1] > 3)
        {
            gFieldEffectArguments[0] = objectEvent->currentCoords.x;
            gFieldEffectArguments[1] = objectEvent->currentCoords.y;
            gFieldEffectArguments[2] = sprite->subpriority - 1;
            gFieldEffectArguments[3] = sprite->oam.priority;
            task->data[1] = FieldEffectStart(FLDEFF_ASH_PUFF);
            task->data[0]++;
        } else
        {
            task->data[1]++;
            ObjectEventSetHeldMovement(objectEvent, GetWalkInPlaceFastestMovementAction(objectEvent->facingDirection));
            PlaySE(SE_LAVARIDGE_FALL_WARP);
        }
    }
    return FALSE;
}

static bool8 LavaridgeGym1FWarpEffect_Disappear(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (gSprites[task->data[1]].animCmdIndex == 2)
    {
        objectEvent->invisible = TRUE;
        task->data[0]++;
    }
    return FALSE;
}

static bool8 LavaridgeGym1FWarpEffect_FadeOut(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (!FieldEffectActiveListContains(FLDEFF_ASH_PUFF))
    {
        TryFadeOutOldMapMusic();
        WarpFadeOutScreen();
        task->data[0]++;
    }
    return FALSE;
}

static bool8 LavaridgeGym1FWarpEffect_Warp(struct Task *task, struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (!gPaletteFade.active && BGMusicStopped() == TRUE)
    {
        WarpIntoMap();
        gFieldCallback = FieldCB_FallWarpExit;
        SetMainCallback2(CB2_LoadMap);
        DestroyTask(FindTaskIdByFunc(Task_LavaridgeGym1FWarp));
    }
    return FALSE;
}

// For the ash effect when a trainer pops out of ash, or when the player enters/exits a warp in Lavaridge Gym 1F
u8 FldEff_AshPuff(void)
{
    u8 spriteId;
    SetSpritePosToOffsetMapCoords((s16 *)&gFieldEffectArguments[0], (s16 *)&gFieldEffectArguments[1], 8, 8);
    spriteId = CreateSpriteAtEnd(gFieldEffectObjectTemplatePointers[FLDEFFOBJ_ASH_PUFF], gFieldEffectArguments[0], gFieldEffectArguments[1], gFieldEffectArguments[2]);
    gSprites[spriteId].oam.priority = gFieldEffectArguments[3];
    gSprites[spriteId].coordOffsetEnabled = TRUE;
    return spriteId;
}

void SpriteCB_AshPuff(struct Sprite *sprite)
{
    if (sprite->animEnded)
        FieldEffectStop(sprite, FLDEFF_ASH_PUFF);
}

#define tState     data[0]
#define tSpinDelay data[1]
#define tNumTurns  data[2]
#define tTimer     data[14]
#define tStartDir  data[15]

void StartEscapeRopeFieldEffect(void)
{
    ScriptContext2_Enable();
    FreezeObjectEvents();
    CreateTask(Task_EscapeRopeWarpOut, 80);
}

static void Task_EscapeRopeWarpOut(u8 taskId)
{
    sEscapeRopeWarpOutEffectFuncs[gTasks[taskId].tState](&gTasks[taskId]);
}

static void EscapeRopeWarpOutEffect_Init(struct Task *task)
{
    task->tState++;
    task->tTimer = 64;
    task->tStartDir = GetPlayerFacingDirection();
}

static void EscapeRopeWarpOutEffect_Spin(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    u8 spinDirections[5] =  {DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH};
    if (task->tTimer != 0 && (--task->tTimer) == 0)
    {
        TryFadeOutOldMapMusic();
        WarpFadeOutScreen();
    }
    objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (!ObjectEventIsMovementOverridden(objectEvent) || ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        if (task->tTimer == 0 && !gPaletteFade.active && BGMusicStopped() == TRUE)
        {
            SetObjectEventDirection(objectEvent, task->tStartDir);
            SetWarpDestinationToEscapeWarp();
            WarpIntoMap();
            gFieldCallback = FieldCallback_EscapeRopeWarpIn;
            SetMainCallback2(CB2_LoadMap);
            DestroyTask(FindTaskIdByFunc(Task_EscapeRopeWarpOut));
        } 
        else if (task->tSpinDelay == 0 || (--task->tSpinDelay) == 0)
        {
            ObjectEventSetHeldMovement(objectEvent, GetFaceDirectionMovementAction(spinDirections[objectEvent->facingDirection]));
            if (task->tNumTurns < 12)
                task->tNumTurns++;
            task->tSpinDelay = 8 >> (task->tNumTurns >> 2);
        }
    }
}

void (*const sEscapeRopeWarpInEffectFuncs[])(struct Task *) = {
    EscapeRopeWarpInEffect_Init,
    EscapeRopeWarpInEffect_Spin
};

static void FieldCallback_EscapeRopeWarpIn(void)
{
    Overworld_PlaySpecialMapMusic();
    WarpFadeInScreen();
    ScriptContext2_Enable();
    FreezeObjectEvents();
    gFieldCallback = NULL;
    gObjectEvents[gPlayerAvatar.objectEventId].invisible = TRUE;
    CreateTask(Task_EscapeRopeWarpIn, 0);
}

static void Task_EscapeRopeWarpIn(u8 taskId)
{
    sEscapeRopeWarpInEffectFuncs[gTasks[taskId].tState](&gTasks[taskId]);
}

static void EscapeRopeWarpInEffect_Init(struct Task *task)
{
    if (IsWeatherNotFadingIn())
    {
        task->tState++;
        task->tStartDir = GetPlayerFacingDirection();
    }
}

static void EscapeRopeWarpInEffect_Spin(struct Task *task)
{
    u8 spinDirections[5] = {DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH};
    struct ObjectEvent *objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (task->tSpinDelay == 0 || (--task->tSpinDelay) == 0)
    {
        if (ObjectEventIsMovementOverridden(objectEvent) && !ObjectEventClearHeldMovementIfFinished(objectEvent))
        {
            return;
        }
        if (task->tNumTurns >= 32 && task->tStartDir == GetPlayerFacingDirection())
        {
            objectEvent->invisible = FALSE;
            ScriptContext2_Disable();
            UnfreezeObjectEvents();
            DestroyTask(FindTaskIdByFunc(Task_EscapeRopeWarpIn));
            return;
        }
        ObjectEventSetHeldMovement(objectEvent, GetFaceDirectionMovementAction(spinDirections[objectEvent->facingDirection]));
        if (task->tNumTurns < 32)
            task->tNumTurns++;
        task->tSpinDelay = task->tNumTurns >> 2;
    }
    objectEvent->invisible ^= 1;
}

#undef tState
#undef tSpinDelay
#undef tNumTurns
#undef tTimer
#undef tStartDir

#define tState data[0]

void FldEff_TeleportWarpOut(void)
{
    CreateTask(Task_TeleportWarpOut, 0);
}

static void (*const sTeleportWarpOutFieldEffectFuncs[])(struct Task *) = {
    TeleportWarpOutFieldEffect_Init,
    TeleportWarpOutFieldEffect_SpinGround,
    TeleportWarpOutFieldEffect_SpinExit,
    TeleportWarpOutFieldEffect_End
};

static void Task_TeleportWarpOut(u8 taskId)
{
    sTeleportWarpOutFieldEffectFuncs[gTasks[taskId].tState](&gTasks[taskId]);
}

static void TeleportWarpOutFieldEffect_Init(struct Task *task)
{
    ScriptContext2_Enable();
    FreezeObjectEvents();
    CameraObjectReset2();
    task->data[15] = GetPlayerFacingDirection();
    task->tState++;
}

static void TeleportWarpOutFieldEffect_SpinGround(struct Task *task)
{
    u8 spinDirections[5] = {DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH};
    struct ObjectEvent *objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (task->data[1] == 0 || (--task->data[1]) == 0)
    {
        ObjectEventTurn(objectEvent, spinDirections[objectEvent->facingDirection]);
        task->data[1] = 8;
        task->data[2]++;
    }
    if (task->data[2] > 7 && task->data[15] == objectEvent->facingDirection)
    {
        task->tState++;
        task->data[1] = 4;
        task->data[2] = 8;
        task->data[3] = 1;
        PlaySE(SE_WARP_IN);
    }
}

static void TeleportWarpOutFieldEffect_SpinExit(struct Task *task)
{
    u8 spinDirections[5] = {DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH};
    struct ObjectEvent *objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    struct Sprite *sprite = &gSprites[gPlayerAvatar.spriteId];
    if ((--task->data[1]) <= 0)
    {
        task->data[1] = 4;
        ObjectEventTurn(objectEvent, spinDirections[objectEvent->facingDirection]);
    }
    sprite->y -= task->data[3];
    task->data[4] += task->data[3];
    if ((--task->data[2]) <= 0 && (task->data[2] = 4, task->data[3] < 8))
    {
        task->data[3] <<= 1;
    }
    if (task->data[4] > 8 && (sprite->oam.priority = 1, sprite->subspriteMode != SUBSPRITES_OFF))
    {
        sprite->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
    }
    if (task->data[4] >= 0xa8)
    {
        task->tState++;
        TryFadeOutOldMapMusic();
        WarpFadeOutScreen();
    }
}

static void TeleportWarpOutFieldEffect_End(struct Task *task)
{
    if (!gPaletteFade.active)
    {
        if (task->data[5] == FALSE)
        {
            ClearMirageTowerPulseBlendEffect();
            task->data[5] = TRUE;
        }

        if (BGMusicStopped() == TRUE)
        {
            SetWarpDestinationToLastHealLocation();
            WarpIntoMap();
            SetMainCallback2(CB2_LoadMap);
            gFieldCallback = FieldCallback_TeleportWarpIn;
            DestroyTask(FindTaskIdByFunc(Task_TeleportWarpOut));
        }
    }
}

static void FieldCallback_TeleportWarpIn(void)
{
    Overworld_PlaySpecialMapMusic();
    WarpFadeInScreen();
    ScriptContext2_Enable();
    FreezeObjectEvents();
    gFieldCallback = NULL;
    gObjectEvents[gPlayerAvatar.objectEventId].invisible = TRUE;
    CameraObjectReset2();
    CreateTask(Task_TeleportWarpIn, 0);
}

void (*const sTeleportWarpInFieldEffectFuncs[])(struct Task *) = {
    TeleportWarpInFieldEffect_Init,
    TeleportWarpInFieldEffect_SpinEnter,
    TeleportWarpInFieldEffect_SpinGround
};

static void Task_TeleportWarpIn(u8 taskId)
{
    sTeleportWarpInFieldEffectFuncs[gTasks[taskId].data[0]](&gTasks[taskId]);
}

static void TeleportWarpInFieldEffect_Init(struct Task *task)
{
    struct Sprite *sprite;
    s16 centerToCornerVecY;
    if (IsWeatherNotFadingIn())
    {
        sprite = &gSprites[gPlayerAvatar.spriteId];
        centerToCornerVecY = -(sprite->centerToCornerVecY << 1);
        sprite->y2 = -(sprite->y + sprite->centerToCornerVecY + gSpriteCoordOffsetY + centerToCornerVecY);
        gObjectEvents[gPlayerAvatar.objectEventId].invisible = FALSE;
        task->data[0]++;
        task->data[1] = 8;
        task->data[2] = 1;
        task->data[14] = sprite->subspriteMode;
        task->data[15] = GetPlayerFacingDirection();
        PlaySE(SE_WARP_IN);
    }
}

static void TeleportWarpInFieldEffect_SpinEnter(struct Task *task)
{
    u8 spinDirections[5] = {DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH};
    struct ObjectEvent *objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    struct Sprite *sprite = &gSprites[gPlayerAvatar.spriteId];
    if ((sprite->y2 += task->data[1]) >= -8)
    {
        if (task->data[13] == 0)
        {
            task->data[13]++;
            objectEvent->triggerGroundEffectsOnMove = 1;
            sprite->subspriteMode = task->data[14];
        }
    } else
    {
        sprite->oam.priority = 1;
        if (sprite->subspriteMode != SUBSPRITES_OFF)
        {
            sprite->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
        }
    }
    if (sprite->y2 >= -0x30 && task->data[1] > 1 && !(sprite->y2 & 1))
    {
        task->data[1]--;
    }
    if ((--task->data[2]) == 0)
    {
        task->data[2] = 4;
        ObjectEventTurn(objectEvent, spinDirections[objectEvent->facingDirection]);
    }
    if (sprite->y2 >= 0)
    {
        sprite->y2 = 0;
        task->data[0]++;
        task->data[1] = 1;
        task->data[2] = 0;
    }
}

static void TeleportWarpInFieldEffect_SpinGround(struct Task *task)
{
    u8 spinDirections[5] = {DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH};
    struct ObjectEvent *objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if ((--task->data[1]) == 0)
    {
        ObjectEventTurn(objectEvent, spinDirections[objectEvent->facingDirection]);
        task->data[1] = 8;
        if ((++task->data[2]) > 4 && task->data[14] == objectEvent->facingDirection)
        {
            ScriptContext2_Disable();
            CameraObjectReset1();
            UnfreezeObjectEvents();
            DestroyTask(FindTaskIdByFunc(Task_TeleportWarpIn));
        }
    }
}

// Task data for Task_FieldMoveShowMon
#define tState       data[0]
#define tWinOffset   data[1]
#define tTimer       data[2]
#define tMonSpriteId data[3]

bool8 FldEff_FieldMoveShowMon(void)
{
    u8 taskId = CreateTask(Task_FieldMoveShowMon, 0xff);
    return FALSE;
}

bool8 FldEff_FieldMoveShowMonInit(void)
{
    struct Pokemon *pokemon;
    u32 flag = gFieldEffectArguments[0] & 0x80000000;
    pokemon = &gPlayerParty[(u8)gFieldEffectArguments[0]];
    gFieldEffectArguments[0] = GetMonData(pokemon, MON_DATA_SPECIES);
    gFieldEffectArguments[1] = GetMonData(pokemon, MON_DATA_PERSONALITY);
    gFieldEffectArguments[0] |= flag;
    FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON);
    FieldEffectActiveListRemove(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
    return FALSE;
}

void (*const sFieldMoveShowMonEffectFuncs[])(struct Task *) = {
    FieldMoveShowMonEffect_Init,
    FieldMoveShowMonEffect_LoadGfx,
    FieldMoveShowMonEffect_MoveWindowOnscreen,
    FieldMoveShowMonEffect_WaitForMonCry,
    FieldMoveShowMonEffect_MoveWindowOffscreen,
    FieldMoveShowMonEffect_DestroyGfx,
    FieldMoveShowMonEffect_End,
};

static void Task_FieldMoveShowMon(u8 taskId)
{
    sFieldMoveShowMonEffectFuncs[gTasks[taskId].tState](&gTasks[taskId]);
}

static const u8 gText_MonUsedCut[]       = _("{STR_VAR_1} USED CUT!");
static const u8 gText_MonUsedFly[]       = _("{STR_VAR_1} USED FLY!");
static const u8 gText_MonUsedSurf[]      = _("{STR_VAR_1} USED SURF!");
static const u8 gText_MonUsedStrength[]  = _("{STR_VAR_1} USED STRENGTH!");
static const u8 gText_MonUsedFlash[]     = _("{STR_VAR_1} USED FLASH!");
static const u8 gText_MonUsedRockSmash[] = _("{STR_VAR_1} USED ROCK SMASH!");
static const u8 gText_MonUsedWaterfall[] = _("{STR_VAR_1} USED WATERFALL!");
static const u8 gText_MonUsedDive[]      = _("{STR_VAR_1} USED DIVE!");
static const u8 gText_MonUsedAMove[]     = _("{STR_VAR_1} USED A MOVE!");

static void FieldMoveShowMonEffect_Init(struct Task *task)
{
    u8 popupWindowId = GetFieldEffectPopUpWindowId();
    u8 x;

    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuRegBits(REG_OFFSET_WININ, WININ_WIN0_CLR);
    LoadPalette(sFieldEffectPopUp_Palette, 0xE0, sizeof(sFieldEffectPopUp_Palette));
    AddFieldEffectPopUpWindow();
    PutWindowTilemap(popupWindowId);
    FillWindowPixelBuffer(popupWindowId, PIXEL_FILL(1));

    switch (gFieldEffectArguments[2])
    {
    case MOVE_CUT:
        StringExpandPlaceholders(gStringVar4, gText_MonUsedCut);
        break;
    case MOVE_FLY:
        StringExpandPlaceholders(gStringVar4, gText_MonUsedFly);
        break;
    case MOVE_SURF:
        StringExpandPlaceholders(gStringVar4, gText_MonUsedSurf);
        break;
    case MOVE_STRENGTH:
        StringExpandPlaceholders(gStringVar4, gText_MonUsedStrength);
        break;
    case MOVE_FLASH:
        StringExpandPlaceholders(gStringVar4, gText_MonUsedFlash);
        break;
    case MOVE_ROCK_SMASH:
        StringExpandPlaceholders(gStringVar4, gText_MonUsedRockSmash);
        break;
    case MOVE_WATERFALL:
        StringExpandPlaceholders(gStringVar4, gText_MonUsedWaterfall);
        break;
    case MOVE_DIVE:
        StringExpandPlaceholders(gStringVar4, gText_MonUsedDive);
        break;
    default:
        StringExpandPlaceholders(gStringVar4, gText_MonUsedAMove);
        break;
    }
    x = GetStringCenterAlignXOffset(1, gStringVar4, 240);
    AddTextPrinterParameterized(popupWindowId, 1, gStringVar4, x + 16, 18, 0xFF, NULL);
    CopyWindowToVram(popupWindowId, 3);
    EnableInterrupts(INTR_FLAG_HBLANK);
    SetHBlankCallback(HBlankCB_FieldEffectPopupWindow);
    if (task->tTimer == 1)
    {
        task->tState++;
        task->tTimer = 0;
    }
    task->tTimer++;
}

static void FieldMoveShowMonEffect_LoadGfx(struct Task *task)
{
    u8 x = GetStringCenterAlignXOffset(1, gStringVar4, 240);

    LoadMonIconPalette(gFieldEffectArguments[0]);
    task->tMonSpriteId = CreateMonIcon(gFieldEffectArguments[0], SpriteCB_UpdateSpritePos, x - 4, 180, 0, gFieldEffectArguments[1], FALSE);
    gSprites[task->tMonSpriteId].oam.priority = 0;
    task->tState++;
}

static void FieldMoveShowMonEffect_MoveWindowOnscreen(struct Task *task)
{
    task->tWinOffset += 10;
    if (task->tWinOffset > 47)
    {
        task->tWinOffset = 48;
        task->tTimer = 0;
        task->tState++;
    }
    SetGpuReg(REG_OFFSET_BG0VOFS, task->tWinOffset);
}

static void FieldMoveShowMonEffect_WaitForMonCry(struct Task *task)
{
    if (task->tTimer == 0)
    {
        PlayCry1(gFieldEffectArguments[0], 0);
        task->tTimer++;
    }
    else if (IsCryFinished())
        task->tState++;
}

static void FieldMoveShowMonEffect_MoveWindowOffscreen(struct Task *task)
{
    task->tWinOffset -= 10;
    if (task->tWinOffset <= 0)
    {
        task->tWinOffset = 0;
        task->tTimer = 0;
        task->tState++;
    }
    SetGpuReg(REG_OFFSET_BG0VOFS, task->tWinOffset);
}

static void FieldMoveShowMonEffect_DestroyGfx(struct Task *task)
{
    ClearStdWindowAndFrame(GetFieldEffectPopUpWindowId(), TRUE);
    RemoveFieldEffectPopUpWindow();
    FreeAndDestroyMonIconSprite(&gSprites[task->tMonSpriteId]);
    SetGpuReg_ForcedBlank(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ);
    DisableInterrupts(INTR_FLAG_HBLANK);
    SetHBlankCallback(NULL);
    task->tState++;
}

static void FieldMoveShowMonEffect_End(struct Task *task)
{
    IntrCallback callback;
    LoadWordFromTwoHalfwords((u16 *)&task->data[13], (u32 *)&callback);
    InitTextBoxGfxAndPrinters();
    FieldEffectActiveListRemove(FLDEFF_FIELD_MOVE_SHOW_MON);
    DestroyTask(FindTaskIdByFunc(Task_FieldMoveShowMon));
}

static void SpriteCB_UpdateSpritePos(struct Sprite *sprite)
{
    struct Task *task = &gTasks[FindTaskIdByFunc(Task_FieldMoveShowMon)];

    sprite->y2 = -(task->tWinOffset);
}

static void HBlankCB_FieldEffectPopupWindow(void)
{
    struct Task *task = &gTasks[FindTaskIdByFunc(Task_FieldMoveShowMon)];
    s16 currentOffset = 158 - task->tWinOffset;

    if (REG_VCOUNT > currentOffset)
    {
        REG_BLDCNT = BLDCNT_TGT1_BG0 | BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND;
        REG_BLDALPHA = BLDALPHA_BLEND(15, 5);
    }
    else
    {
        gWeatherPtr->currBlendEVA = 8;
        gWeatherPtr->currBlendEVB = 10;
        gWeatherPtr->targetBlendEVA = 8;
        gWeatherPtr->targetBlendEVB = 10;
        REG_BLDALPHA = BLDALPHA_BLEND(8, 10);
    }
}

#undef tState
#undef tWinOffset
#undef tTimer
#undef tMonSpriteId

#define tState data[0]
#define tDestX data[1]
#define tDestY data[2]
#define tMonId data[15]

u8 FldEff_UseSurf(void)
{
    u8 taskId = CreateTask(Task_SurfFieldEffect, 0xff);
    gTasks[taskId].tMonId = gFieldEffectArguments[0];
    Overworld_ClearSavedMusic();
    Overworld_ChangeMusicTo(MUS_SURF);
    return FALSE;
}

void (*const sSurfFieldEffectFuncs[])(struct Task *) = {
    SurfFieldEffect_Init,
    SurfFieldEffect_FieldMovePose,
    SurfFieldEffect_ShowMon,
    SurfFieldEffect_JumpOnSurfBlob,
    SurfFieldEffect_End,
};

static void Task_SurfFieldEffect(u8 taskId)
{
    sSurfFieldEffectFuncs[gTasks[taskId].tState](&gTasks[taskId]);
}

static void SurfFieldEffect_Init(struct Task *task)
{
    ScriptContext2_Enable();
    FreezeObjectEvents();
    gPlayerAvatar.preventStep = TRUE;
    SetPlayerAvatarStateMask(PLAYER_AVATAR_FLAG_SURFING);
    PlayerGetDestCoords(&task->tDestX, &task->tDestY);
    MoveCoords(gObjectEvents[gPlayerAvatar.objectEventId].movementDirection, &task->tDestX, &task->tDestY);
    task->tState++;
}

static void SurfFieldEffect_FieldMovePose(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (!ObjectEventIsMovementOverridden(objectEvent) || ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        SetPlayerAvatarFieldMove();
        ObjectEventSetHeldMovement(objectEvent, MOVEMENT_ACTION_START_ANIM_IN_DIRECTION);
        task->tState++;
    }
}

static void SurfFieldEffect_ShowMon(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (ObjectEventCheckHeldMovementStatus(objectEvent))
    {
        gFieldEffectArguments[0] = task->tMonId | 0x80000000;
        FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
        task->tState++;
    }
}

static void SurfFieldEffect_JumpOnSurfBlob(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    if (!FieldEffectActiveListContains(FLDEFF_FIELD_MOVE_SHOW_MON))
    {
        objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
        ObjectEventSetGraphicsId(objectEvent, GetPlayerAvatarGraphicsIdByStateId(PLAYER_AVATAR_STATE_SURFING));
        ObjectEventClearHeldMovementIfFinished(objectEvent);
        ObjectEventSetHeldMovement(objectEvent, GetJumpSpecialMovementAction(objectEvent->movementDirection));
        FollowMe_FollowerToWater();
        gFieldEffectArguments[0] = task->tDestX;
        gFieldEffectArguments[1] = task->tDestY;
        gFieldEffectArguments[2] = gPlayerAvatar.objectEventId;
        objectEvent->fieldEffectSpriteId = FieldEffectStart(FLDEFF_SURF_BLOB);
        task->tState++;
    }
}

static void SurfFieldEffect_End(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        gPlayerAvatar.preventStep = FALSE;
        gPlayerAvatar.flags &= ~PLAYER_AVATAR_FLAG_5;
        ObjectEventSetHeldMovement(objectEvent, GetFaceDirectionMovementAction(objectEvent->movementDirection));
        SetSurfBlob_BobState(objectEvent->fieldEffectSpriteId, BOB_PLAYER_AND_MON);
        UnfreezeObjectEvents();
        ScriptContext2_Disable();
        FieldEffectActiveListRemove(FLDEFF_USE_SURF);
        DestroyTask(FindTaskIdByFunc(Task_SurfFieldEffect));
    }
}

#undef tState
#undef tDestX
#undef tDestY
#undef tMonId

u8 FldEff_RayquazaSpotlight(void)
{
    u8 i, j, k;
    u8 spriteId = CreateSprite(gFieldEffectObjectTemplatePointers[FLDEFFOBJ_RAYQUAZA], 120, -24, 1);
    struct Sprite *sprite = &gSprites[spriteId];

    sprite->oam.priority = 1;
    sprite->oam.paletteNum = 4;
    sprite->data[0] = 0;
    sprite->data[1] = 0;
    sprite->data[2] = 0;
    sprite->data[3] = -1;
    sprite->data[4] = sprite->y;
    sprite->data[5] = 0;
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ | BLDCNT_TGT2_BD);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(14, 14));
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
    LoadPalette(sSpotlight_Pal, 0xC0, sizeof(sSpotlight_Pal));
    SetGpuReg(REG_OFFSET_BG0VOFS, 120);
    for (i = 3; i < 15; i++)
    {
        for (j = 12; j < 18; j++)
        {
            ((u16*)(BG_SCREEN_ADDR(31)))[i * 32 + j] = 0xBFF4 + i * 6 + j + 1;
        }
    }
    for (k = 0; k < 90; k++)
    {
        for (i = 0; i < 8; i++)
        {
            *(u16*)(BG_CHAR_ADDR(2) + (k + 1) * 32 + i * 4) = (sSpotlight_Gfx[k * 32 + i * 4 + 1] << 8) + sSpotlight_Gfx[k * 32 + i * 4];
            *(u16*)(BG_CHAR_ADDR(2) + (k + 1) * 32 + i * 4 + 2) = (sSpotlight_Gfx[k * 32 + i * 4 + 3] << 8) + sSpotlight_Gfx[k * 32 + i * 4 + 2];
        }
    }
    return spriteId;
}

u8 FldEff_NPCFlyOut(void)
{
    u8 spriteId;
    struct Sprite *sprite;

    LoadFieldEffectPalette(FLDEFFOBJ_BIRD);
    spriteId = CreateSprite(gFieldEffectObjectTemplatePointers[FLDEFFOBJ_BIRD], 0x78, 0, 1);
    sprite = &gSprites[spriteId];
    sprite->oam.priority = 1;
    sprite->callback = SpriteCB_NPCFlyOut;
    sprite->data[1] = gFieldEffectArguments[0];
    PlaySE(SE_M_FLY);
    return spriteId;
}

static void SpriteCB_NPCFlyOut(struct Sprite *sprite)
{
    struct Sprite *npcSprite;

    sprite->x2 = Cos(sprite->data[2], 0x8c);
    sprite->y2 = Sin(sprite->data[2], 0x48);
    sprite->data[2] = (sprite->data[2] + 4) & 0xff;
    if (sprite->data[0])
    {
        npcSprite = &gSprites[sprite->data[1]];
        npcSprite->coordOffsetEnabled = FALSE;
        npcSprite->x = sprite->x + sprite->x2;
        npcSprite->y = sprite->y + sprite->y2 - 8;
        npcSprite->x2 = 0;
        npcSprite->y2 = 0;
    }

    if (sprite->data[2] >= 0x80)
        FieldEffectStop(sprite, FLDEFF_NPCFLY_OUT);
}

// Task data for Task_FlyOut/FlyIn
#define tState          data[0]
#define tMonId          data[1]
#define tBirdSpriteId   data[1] //re-used
#define tTimer          data[2]
#define tAvatarFlags    data[15]

// Sprite data for the fly bird
#define sPlayerSpriteId data[6]
#define sAnimCompleted  data[7]

u8 FldEff_UseFly(void)
{
    u8 taskId = CreateTask(Task_FlyOut, 254);
    gTasks[taskId].tMonId = gFieldEffectArguments[0];
    return 0;
}

void (*const sFlyOutFieldEffectFuncs[])(struct Task *) = {
    FlyOutFieldEffect_FieldMovePose,
    FlyOutFieldEffect_ShowMon,
    FlyOutFieldEffect_BirdLeaveBall,
    FlyOutFieldEffect_WaitBirdLeave,
    FlyOutFieldEffect_BirdSwoopDown,
    FlyOutFieldEffect_JumpOnBird,
    FlyOutFieldEffect_FlyOffWithBird,
    FlyOutFieldEffect_WaitFlyOff,
    FlyOutFieldEffect_End,
};

static void Task_FlyOut(u8 taskId)
{
    sFlyOutFieldEffectFuncs[gTasks[taskId].tState](&gTasks[taskId]);
}

static void FlyOutFieldEffect_FieldMovePose(struct Task *task)
{
    struct ObjectEvent *objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (!ObjectEventIsMovementOverridden(objectEvent) || ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        task->tAvatarFlags = gPlayerAvatar.flags;
        gPlayerAvatar.preventStep = TRUE;
        SetPlayerAvatarStateMask(PLAYER_AVATAR_FLAG_ON_FOOT);
        SetPlayerAvatarFieldMove();
        ObjectEventSetHeldMovement(objectEvent, MOVEMENT_ACTION_START_ANIM_IN_DIRECTION);
        task->tState++;
    }
}

static void FlyOutFieldEffect_ShowMon(struct Task *task)
{
    struct ObjectEvent *objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        task->tState++;
        gFieldEffectArguments[0] = task->tMonId;
        gFieldEffectArguments[2] = MOVE_FLY;
        FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
    }
}

static void FlyOutFieldEffect_BirdLeaveBall(struct Task *task)
{
    if (!FieldEffectActiveListContains(FLDEFF_FIELD_MOVE_SHOW_MON))
    {
        struct ObjectEvent *objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
        if (task->tAvatarFlags & PLAYER_AVATAR_FLAG_SURFING)
        {
            SetSurfBlob_BobState(objectEvent->fieldEffectSpriteId, BOB_JUST_MON);
            SetSurfBlob_DontSyncAnim(objectEvent->fieldEffectSpriteId, FALSE);
        }
        task->tBirdSpriteId = CreateFlyBirdSprite(); // Does "leave ball" animation by default
        task->tState++;
    }
}

static void FlyOutFieldEffect_WaitBirdLeave(struct Task *task)
{
    if (GetFlyBirdAnimCompleted(task->tBirdSpriteId))
    {
        task->tState++;
        task->tTimer = 16;
        SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_ON_FOOT);
        ObjectEventSetHeldMovement(&gObjectEvents[gPlayerAvatar.objectEventId], MOVEMENT_ACTION_FACE_LEFT);
    }
}

static void FlyOutFieldEffect_BirdSwoopDown(struct Task *task)
{
    struct ObjectEvent *objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if ((task->tTimer == 0 || (--task->tTimer) == 0) && ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        task->tState++;
        PlaySE(SE_M_FLY);
        StartFlyBirdSwoopDown(task->tBirdSpriteId);
    }
}

static void FlyOutFieldEffect_JumpOnBird(struct Task *task)
{
    if ((++task->tTimer) >= 8)
    {
        struct ObjectEvent *objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
        ObjectEventSetGraphicsId(objectEvent, GetPlayerAvatarGraphicsIdByStateId(PLAYER_AVATAR_STATE_SURFING));
        StartSpriteAnim(&gSprites[objectEvent->spriteId], 0x16);
        objectEvent->inanimate = TRUE;
        ObjectEventSetHeldMovement(objectEvent, MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT);
        if (task->tAvatarFlags & PLAYER_AVATAR_FLAG_SURFING)
        {
            DestroySprite(&gSprites[objectEvent->fieldEffectSpriteId]);
        }
        task->tState++;
        task->tTimer = 0;
    }
}

static void FlyOutFieldEffect_FlyOffWithBird(struct Task *task)
{
    if ((++task->tTimer) >= 10)
    {
        struct ObjectEvent *objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
        ObjectEventClearHeldMovementIfActive(objectEvent);
        objectEvent->inanimate = FALSE;
        objectEvent->hasShadow = FALSE;
        SetFlyBirdPlayerSpriteId(task->tBirdSpriteId, objectEvent->spriteId);
        CameraObjectReset2();
        task->tState++;
    }
}

static void FlyOutFieldEffect_WaitFlyOff(struct Task *task)
{
    if (GetFlyBirdAnimCompleted(task->tBirdSpriteId))
    {
        WarpFadeOutScreen();
        task->tState++;
    }
}

static void FlyOutFieldEffect_End(struct Task *task)
{
    if (!gPaletteFade.active)
    {
        FieldEffectActiveListRemove(FLDEFF_USE_FLY);
        DestroyTask(FindTaskIdByFunc(Task_FlyOut));
    }
}

static u8 CreateFlyBirdSprite(void)
{
    u8 spriteId;
    struct Sprite *sprite;

    LoadFieldEffectPalette(FLDEFFOBJ_BIRD);
    spriteId = CreateSprite(gFieldEffectObjectTemplatePointers[FLDEFFOBJ_BIRD], 0xff, 0xb4, 0x1);
    sprite = &gSprites[spriteId];
    sprite->oam.priority = 1;
    sprite->callback = SpriteCB_FlyBirdLeaveBall;
    return spriteId;
}

static u8 GetFlyBirdAnimCompleted(u8 spriteId)
{
    return gSprites[spriteId].sAnimCompleted;
}

static void StartFlyBirdSwoopDown(u8 spriteId)
{
    struct Sprite *sprite;
    sprite = &gSprites[spriteId];
    sprite->callback = SpriteCB_FlyBirdSwoopDown;
    sprite->x = DISPLAY_WIDTH / 2;
    sprite->y = 0;
    sprite->x2 = 0;
    sprite->y2 = 0;
    memset(&sprite->data[0], 0, 8 * sizeof(u16) /* zero all data cells */);
    sprite->sPlayerSpriteId = MAX_SPRITES;
}

static void SetFlyBirdPlayerSpriteId(u8 birdSpriteId, u8 playerSpriteId)
{
    gSprites[birdSpriteId].sPlayerSpriteId = playerSpriteId;
}

static const union AffineAnimCmd sAffineAnim_FlyBirdLeaveBall[] = {
    AFFINEANIMCMD_FRAME(8, 8, -30, 0),
    AFFINEANIMCMD_FRAME(28, 28, 0, 30),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sAffineAnim_FlyBirdReturnToBall[] = {
    AFFINEANIMCMD_FRAME(256, 256, 64, 0),
    AFFINEANIMCMD_FRAME(-10, -10, 0, 22),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const sAffineAnims_FlyBird[] = {
    sAffineAnim_FlyBirdLeaveBall,
    sAffineAnim_FlyBirdReturnToBall
};

static void SpriteCB_FlyBirdLeaveBall(struct Sprite *sprite)
{
    if (sprite->sAnimCompleted == FALSE)
    {
        if (sprite->data[0] == 0)
        {
            sprite->oam.affineMode = ST_OAM_AFFINE_DOUBLE;
            sprite->affineAnims = sAffineAnims_FlyBird;
            InitSpriteAffineAnim(sprite);
            StartSpriteAffineAnim(sprite, 0);
            sprite->x = 0x76;
            sprite->y = -0x30;
            sprite->data[0]++;
            sprite->data[1] = 0x40;
            sprite->data[2] = 0x100;
        }
        sprite->data[1] += (sprite->data[2] >> 8);
        sprite->x2 = Cos(sprite->data[1], 0x78);
        sprite->y2 = Sin(sprite->data[1], 0x78);
        if (sprite->data[2] < 0x800)
        {
            sprite->data[2] += 0x60;
        }
        if (sprite->data[1] > 0x81)
        {
            sprite->sAnimCompleted++;
            sprite->oam.affineMode = ST_OAM_AFFINE_OFF;
            FreeOamMatrix(sprite->oam.matrixNum);
            CalcCenterToCornerVec(sprite, sprite->oam.shape, sprite->oam.size, ST_OAM_AFFINE_OFF);
        }
    }
}

static void SpriteCB_FlyBirdSwoopDown(struct Sprite *sprite)
{
    sprite->x2 = Cos(sprite->data[2], 0x8c);
    sprite->y2 = Sin(sprite->data[2], 0x48);
    sprite->data[2] = (sprite->data[2] + 4) & 0xff;
    if (sprite->sPlayerSpriteId != MAX_SPRITES)
    {
        struct Sprite *sprite1 = &gSprites[sprite->sPlayerSpriteId];
        sprite1->coordOffsetEnabled = FALSE;
        sprite1->x = sprite->x + sprite->x2;
        sprite1->y = sprite->y + sprite->y2 - 8;
        sprite1->x2 = 0;
        sprite1->y2 = 0;
    }
    if (sprite->data[2] >= 0x80)
    {
        sprite->sAnimCompleted = TRUE;
    }
}

static void SpriteCB_FlyBirdReturnToBall(struct Sprite *sprite)
{
    if (sprite->sAnimCompleted == FALSE)
    {
        if (sprite->data[0] == 0)
        {
            sprite->oam.affineMode = ST_OAM_AFFINE_DOUBLE;
            sprite->affineAnims = sAffineAnims_FlyBird;
            InitSpriteAffineAnim(sprite);
            StartSpriteAffineAnim(sprite, 1);
            sprite->x = 0x5e;
            sprite->y = -0x20;
            sprite->data[0]++;
            sprite->data[1] = 0xf0;
            sprite->data[2] = 0x800;
            sprite->data[4] = 0x80;
        }
        sprite->data[1] += sprite->data[2] >> 8;
        sprite->data[3] += sprite->data[2] >> 8;
        sprite->data[1] &= 0xff;
        sprite->x2 = Cos(sprite->data[1], 0x20);
        sprite->y2 = Sin(sprite->data[1], 0x78);
        if (sprite->data[2] > 0x100)
        {
            sprite->data[2] -= sprite->data[4];
        }
        if (sprite->data[4] < 0x100)
        {
            sprite->data[4] += 24;
        }
        if (sprite->data[2] < 0x100)
        {
            sprite->data[2] = 0x100;
        }
        if (sprite->data[3] >= 60)
        {
            sprite->sAnimCompleted++;
            sprite->oam.affineMode = ST_OAM_AFFINE_OFF;
            FreeOamMatrix(sprite->oam.matrixNum);
            sprite->invisible = TRUE;
        }
    }
}

static void StartFlyBirdReturnToBall(u8 spriteId)
{
    StartFlyBirdSwoopDown(spriteId); // Set up is the same, but overrwrites the callback below
    gSprites[spriteId].callback = SpriteCB_FlyBirdReturnToBall;
}

u8 FldEff_FlyIn(void)
{
    CreateTask(Task_FlyIn, 254);
    return 0;
}

void (*const sFlyInFieldEffectFuncs[])(struct Task *) = {
    FlyInFieldEffect_BirdSwoopDown,
    FlyInFieldEffect_FlyInWithBird,
    FlyInFieldEffect_JumpOffBird,
    FlyInFieldEffect_FieldMovePose,
    FlyInFieldEffect_BirdReturnToBall,
    FlyInFieldEffect_WaitBirdReturn,
    FlyInFieldEffect_End,
};

static void Task_FlyIn(u8 taskId)
{
    sFlyInFieldEffectFuncs[gTasks[taskId].tState](&gTasks[taskId]);
}

static void FlyInFieldEffect_BirdSwoopDown(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (!ObjectEventIsMovementOverridden(objectEvent) || ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        task->tState++;
        task->tTimer = 17;
        task->tAvatarFlags = gPlayerAvatar.flags;
        gPlayerAvatar.preventStep = TRUE;
        SetPlayerAvatarStateMask(PLAYER_AVATAR_FLAG_ON_FOOT);
        if (task->tAvatarFlags & PLAYER_AVATAR_FLAG_SURFING)
        {
            SetSurfBlob_BobState(objectEvent->fieldEffectSpriteId, BOB_NONE);
        }
        ObjectEventSetGraphicsId(objectEvent, GetPlayerAvatarGraphicsIdByStateId(PLAYER_AVATAR_STATE_SURFING));
        CameraObjectReset2();
        ObjectEventTurn(objectEvent, DIR_WEST);
        StartSpriteAnim(&gSprites[objectEvent->spriteId], 0x16);
        objectEvent->invisible = FALSE;
        task->tBirdSpriteId = CreateFlyBirdSprite();
        StartFlyBirdSwoopDown(task->tBirdSpriteId);
        SetFlyBirdPlayerSpriteId(task->tBirdSpriteId, objectEvent->spriteId);
    }
}

static void FlyInFieldEffect_FlyInWithBird(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    struct Sprite *sprite;
    if (task->tTimer == 0 || (--task->tTimer) == 0)
    {
        objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
        sprite = &gSprites[objectEvent->spriteId];
        SetFlyBirdPlayerSpriteId(task->tBirdSpriteId, MAX_SPRITES);
        sprite->x += sprite->x2;
        sprite->y += sprite->y2;
        sprite->x2 = 0;
        sprite->y2 = 0;
        task->tState++;
        task->tTimer = 0;
    }
}

static void FlyInFieldEffect_JumpOffBird(struct Task *task)
{
    s16 sYPositions[18] = {
        -2,
        -4,
        -5,
        -6,
        -7,
        -8,
        -8,
        -8,
        -7,
        -7,
        -6,
        -5,
        -3,
        -2,
        0,
        2,
        4,
        8
    };
    struct Sprite *sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->y2 = sYPositions[task->tTimer];

    if ((++task->tTimer) >= (int)ARRAY_COUNT(sYPositions))
        task->tState++;
}

static void FlyInFieldEffect_FieldMovePose(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    struct Sprite *sprite;
    if (GetFlyBirdAnimCompleted(task->tBirdSpriteId))
    {
        objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
        sprite = &gSprites[objectEvent->spriteId];
        objectEvent->inanimate = FALSE;
        MoveObjectEventToMapCoords(objectEvent, objectEvent->currentCoords.x, objectEvent->currentCoords.y);
        sprite->x2 = 0;
        sprite->y2 = 0;
        sprite->coordOffsetEnabled = TRUE;
        SetPlayerAvatarFieldMove();
        ObjectEventSetHeldMovement(objectEvent, MOVEMENT_ACTION_START_ANIM_IN_DIRECTION);
        task->tState++;
    }
}

static void FlyInFieldEffect_BirdReturnToBall(struct Task *task)
{
    if (ObjectEventClearHeldMovementIfFinished(&gObjectEvents[gPlayerAvatar.objectEventId]))
    {
        task->tState++;
        StartFlyBirdReturnToBall(task->tBirdSpriteId);
    }
}

static void FlyInFieldEffect_WaitBirdReturn(struct Task *task)
{
    if (GetFlyBirdAnimCompleted(task->tBirdSpriteId))
    {
        DestroySprite(&gSprites[task->tBirdSpriteId]);
        task->tState++;
        task->data[1] = 16;
    }
}

static void FlyInFieldEffect_End(struct Task *task)
{
    u8 state;
    struct ObjectEvent *objectEvent;
    if ((--task->data[1]) == 0)
    {
        objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
        state = PLAYER_AVATAR_STATE_NORMAL;
        if (task->tAvatarFlags & PLAYER_AVATAR_FLAG_SURFING)
        {
            state = PLAYER_AVATAR_STATE_SURFING;
            SetSurfBlob_BobState(objectEvent->fieldEffectSpriteId, BOB_PLAYER_AND_MON);
        }
        ObjectEventSetGraphicsId(objectEvent, GetPlayerAvatarGraphicsIdByStateId(state));
        ObjectEventTurn(objectEvent, DIR_SOUTH);
        gPlayerAvatar.flags = task->tAvatarFlags;
        gPlayerAvatar.preventStep = FALSE;
        FieldEffectActiveListRemove(FLDEFF_FLY_IN);
        DestroyTask(FindTaskIdByFunc(Task_FlyIn));
    }
}

#undef tState
#undef tMonId
#undef tBirdSpriteId
#undef tTimer
#undef tAvatarFlags
#undef sPlayerSpriteId
#undef sAnimCompleted

#define tState         data[1]
#define tObjectEventId data[2]
#define tTimer         data[3]
#define tCameraTaskId  data[5]
#define tLocalId       data[6]
#define tMapNum        data[7]
#define tMapGroup      data[8]

bool8 FldEff_DestroyDeoxysRock(void)
{
    u8 taskId;
    u8 objectEventId;
    if (!TryGetObjectEventIdByLocalIdAndMap(gFieldEffectArguments[0], gFieldEffectArguments[1], gFieldEffectArguments[2], &objectEventId))
    {
        taskId = CreateTask(Task_DestroyDeoxysRock, 80);
        gTasks[taskId].tObjectEventId = objectEventId;
        gTasks[taskId].tLocalId = gFieldEffectArguments[0];
        gTasks[taskId].tMapNum = gFieldEffectArguments[1];
        gTasks[taskId].tMapGroup = gFieldEffectArguments[2];
    }
    else
    {
        FieldEffectActiveListRemove(FLDEFF_DESTROY_DEOXYS_ROCK);
    }
    return FALSE;
}

#define tShakeDelay data[0]
#define tShakeUp    data[1]
#define tShake      data[5]
#define tEndDelay   data[6]
#define tEnding     data[7]

static void Task_DeoxysRockCameraShake(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (tEnding)
    {
        if (++tEndDelay > 20)
        {
            tEndDelay = 0;
            if (tShake != 0)
                tShake--;
        }
    }
    else
    {
        tShake = 4;
    }

    if (++tShakeDelay > 1)
    {
        tShakeDelay = 0;

        if (++tShakeUp & 1)
            SetCameraPanning(0, -tShake);
        else
            SetCameraPanning(0, tShake);
    }
    UpdateCameraPanning();
    if (tShake == 0)
        DestroyTask(taskId);
}

static void StartEndingDeoxysRockCameraShake(u8 taskId)
{
    gTasks[taskId].tEnding = TRUE;
}

#undef tShakeDelay
#undef tShakeUp
#undef tShake
#undef tEndDelay
#undef tEnding

void (*const sDestroyDeoxysRockEffectFuncs[])(s16*, u8) = {
    DestroyDeoxysRockEffect_CameraShake,
    DestroyDeoxysRockEffect_RockFragments,
    DestroyDeoxysRockEffect_WaitAndEnd,
};

static void Task_DestroyDeoxysRock(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    InstallCameraPanAheadCallback();
    SetCameraPanningCallback(0);
    sDestroyDeoxysRockEffectFuncs[tState](data, taskId);
}

static void DestroyDeoxysRockEffect_CameraShake(s16* data, u8 taskId)
{
    u8 newTaskId = CreateTask(Task_DeoxysRockCameraShake, 90);
    PlaySE(SE_THUNDER2);
    tCameraTaskId = newTaskId;
    tState++;
}

static void DestroyDeoxysRockEffect_RockFragments(s16* data, u8 taskId)
{
    if (++tTimer > 120)
    {
        struct Sprite *sprite = &gSprites[gObjectEvents[tObjectEventId].spriteId];
        gObjectEvents[tObjectEventId].invisible = TRUE;
        BlendPalettes(PALETTES_BG, 0x10, RGB_WHITE);
        BeginNormalPaletteFade(PALETTES_BG, 0, 0x10, 0, RGB_WHITE);
        CreateDeoxysRockFragments(sprite);
        PlaySE(SE_THUNDER);
        StartEndingDeoxysRockCameraShake(tCameraTaskId);
        tTimer = 0;
        tState++;
    }
}

static void DestroyDeoxysRockEffect_WaitAndEnd(s16* data, u8 taskId)
{
    if (!gPaletteFade.active && !FuncIsActiveTask(Task_DeoxysRockCameraShake))
    {
        InstallCameraPanAheadCallback();
        RemoveObjectEventByLocalIdAndMap(tLocalId, tMapNum, tMapGroup);
        FieldEffectActiveListRemove(FLDEFF_DESTROY_DEOXYS_ROCK);
        DestroyTask(taskId);
    }
}

#undef tState
#undef tObjectEventId
#undef tTimer
#undef tCameraTaskId
#undef tLocalId
#undef tMapNum
#undef tMapGroup

static const struct SpriteFrameImage sImages_DeoxysRockFragment[] = {
    obj_frame_tiles(sRockFragment_TopLeft),
    obj_frame_tiles(sRockFragment_TopRight),
    obj_frame_tiles(sRockFragment_BottomLeft),
    obj_frame_tiles(sRockFragment_BottomRight),
};

static const union AnimCmd sAnim_RockFragment_TopLeft[] = {
    ANIMCMD_FRAME(.imageValue = 0),
    ANIMCMD_END
};

static const union AnimCmd sAnim_RockFragment_TopRight[] = {
    ANIMCMD_FRAME(.imageValue = 1),
    ANIMCMD_END
};

static const union AnimCmd sAnim_RockFragment_BottomLeft[] = {
    ANIMCMD_FRAME(.imageValue = 2),
    ANIMCMD_END
};

static const union AnimCmd sAnim_RockFragment_BottomRight[] = {
    ANIMCMD_FRAME(.imageValue = 3),
    ANIMCMD_END
};

static const union AnimCmd *const sAnims_DeoxysRockFragment[] = {
    sAnim_RockFragment_TopLeft,
    sAnim_RockFragment_TopRight,
    sAnim_RockFragment_BottomLeft,
    sAnim_RockFragment_BottomRight,
};

static const struct SpriteTemplate sSpriteTemplate_DeoxysRockFragment = {
    .tileTag = 0xFFFF,
    .paletteTag = 4378,
    .oam = &sOam_8x8,
    .anims = sAnims_DeoxysRockFragment,
    .images = sImages_DeoxysRockFragment,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_DeoxysRockFragment
};

static void CreateDeoxysRockFragments(struct Sprite* sprite)
{
    int i;
    int xPos = (s16)gTotalCameraPixelOffsetX + sprite->x + sprite->x2;
    int yPos = (s16)gTotalCameraPixelOffsetY + sprite->y + sprite->y2 - 4;

    for (i = 0; i < 4; i++)
    {
        u8 spriteId = CreateSprite(&sSpriteTemplate_DeoxysRockFragment, xPos, yPos, 0);
        if (spriteId != MAX_SPRITES)
        {
            StartSpriteAnim(&gSprites[spriteId], i);
            gSprites[spriteId].data[0] = i;
            gSprites[spriteId].oam.paletteNum = sprite->oam.paletteNum;
        }
    }
}

static void SpriteCB_DeoxysRockFragment(struct Sprite* sprite)
{
    // 1 case for each fragment, fly off in 4 different directions
    switch (sprite->data[0])
    {
    case 0:
        sprite->x -= 16;
        sprite->y -= 12;
        break;
    case 1:
        sprite->x += 16;
        sprite->y -= 12;
        break;
    case 2:
        sprite->x -= 16;
        sprite->y += 12;
        break;
    case 3:
        sprite->x += 16;
        sprite->y += 12;
        break;
    }
    if ((u16)(sprite->x + 4) > DISPLAY_WIDTH + 8 || sprite->y < -4 || sprite->y > DISPLAY_HEIGHT + 4)
        DestroySprite(sprite);
}

bool8 FldEff_MoveDeoxysRock(struct Sprite* sprite)
{
    u8 objectEventIdBuffer;
    if (!TryGetObjectEventIdByLocalIdAndMap(gFieldEffectArguments[0], gFieldEffectArguments[1], gFieldEffectArguments[2], &objectEventIdBuffer))
    {
        struct ObjectEvent *object;
        int xPos, yPos;
        u8 taskId;
        object = &gObjectEvents[objectEventIdBuffer];
        xPos = object->currentCoords.x - 7;
        yPos = object->currentCoords.y - 7;
        xPos = (gFieldEffectArguments[3] - xPos) * 16;
        yPos = (gFieldEffectArguments[4] - yPos) * 16;
        ShiftObjectEventCoords(object, gFieldEffectArguments[3] + 7, gFieldEffectArguments[4] + 7);
        taskId = CreateTask(Task_MoveDeoxysRock, 80);
        gTasks[taskId].data[1] = object->spriteId;
        gTasks[taskId].data[2] = gSprites[object->spriteId].x + xPos;
        gTasks[taskId].data[3] = gSprites[object->spriteId].y + yPos;
        gTasks[taskId].data[8] = gFieldEffectArguments[5];
        gTasks[taskId].data[9] = objectEventIdBuffer;
    }
    return FALSE;
}

static void Task_MoveDeoxysRock(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    struct Sprite *sprite = &gSprites[data[1]];
    switch (data[0])
    {
        case 0:
            data[4] = sprite->x << 4;
            data[5] = sprite->y << 4;
            data[6] = SAFE_DIV(data[2] * 16 - data[4], data[8]);
            data[7] = SAFE_DIV(data[3] * 16 - data[5], data[8]);
            data[0]++;
        case 1:
            if (data[8] != 0)
            {
                data[8]--;
                data[4] += data[6];
                data[5] += data[7];
                sprite->x = data[4] >> 4;
                sprite->y = data[5] >> 4;
            }
            else
            {
                struct ObjectEvent *object = &gObjectEvents[data[9]];
                sprite->x = data[2];
                sprite->y = data[3];
                ShiftStillObjectEventCoords(object);
                object->triggerGroundEffectsOnStop = TRUE;
                FieldEffectActiveListRemove(FLDEFF_MOVE_DEOXYS_ROCK);
                DestroyTask(taskId);
            }
            break;
    }
}

