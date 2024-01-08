#include "global.h"
#include "battle.h"
#include "title_screen.h"
#include "sprite.h"
#include "gba/m4a_internal.h"
#include "bg.h"
#include "clear_save_data_menu.h"
#include "decompress.h"
#include "event_data.h"
#include "global.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "intro.h"
#include "librfu.h"
#include "link.h"
#include "m4a.h"
#include "main.h"
#include "main_menu.h"
#include "malloc.h"
#include "menu.h"
#include "mystery_event_menu.h"
#include "mystery_gift_menu.h"
#include "option_menu.h"
#include "overworld.h"
#include "palette.h"
#include "random.h"
#include "reset_rtc_screen.h"
#include "berry_fix_program.h"
#include "rtc.h"
#include "save.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text_window.h"
#include "trig.h"
#include "util.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"

enum {
    TAG_VERSION = 1000,
    TAG_PRESS_START_COPYRIGHT,
    TAG_LOGO_SHINE,
};

#define VERSION_BANNER_RIGHT_TILEOFFSET 64
#define VERSION_BANNER_LEFT_X 98
#define VERSION_BANNER_RIGHT_X 162
#define VERSION_BANNER_Y 2
#define VERSION_BANNER_Y_GOAL 66
#define START_BANNER_X 202
#define BLINK_TIMER 30
#define DEOXYS_TIMER_MIN 300
#define DEOXYS_TIMER_MAX 600
#define BACKGROUND_DELTA_MIN 16
#define BACKGROUND_DELTA_MAX 64
#define BACKGROUND_TIMER_MIN 240
#define BACKGROUND_TIMER_MAX 420

#define HIDE_MENU_BUTTON_COMBO (L_BUTTON | R_BUTTON)
#define CLEAR_SAVE_BUTTON_COMBO (B_BUTTON | SELECT_BUTTON | DPAD_UP)
#define RESET_RTC_BUTTON_COMBO (B_BUTTON | SELECT_BUTTON | DPAD_LEFT)
#define BERRY_UPDATE_BUTTON_COMBO (B_BUTTON | SELECT_BUTTON)
#define A_B_START_SELECT (A_BUTTON | B_BUTTON | START_BUTTON | SELECT_BUTTON)

EWRAM_DATA static bool8 sCurrActionOptionCheck = FALSE;
EWRAM_DATA static bool8 sIsDeoxysSpawned = FALSE;
EWRAM_DATA static u8 sDeoxysSpriteId;
EWRAM_DATA static u8 sScrollTaskId;
EWRAM_DATA static s16 sBg0HorizontalOffset = 0;

static void MainCB2(void);
static void Task_TitleScreenPhase1(u8);
static void Task_TitleScreenPhase2(u8);
static void Task_ContinuePressA(u8);
static void Task_TitleScreenCheckSave(u8);
static void Task_WaitForTitleScreenSaveErrorMessage(u8);
static void Task_TitleScreenCheckBattery(u8);
static void Task_WaitForTitleScreenBatteryErrorMessage(u8);
static void Task_WaitForBackgroundFade(u8);
static void Task_BuildTitleScreenMenu(u8);
static void Task_TitleScreenPhase3(u8);
static void Task_TitleScreenHandleAPress(u8);
static void CB2_GoToMainMenu(void);
static void CB2_GoToContinueSavedGame(void);
static void CB2_GoToClearSaveDataScreen(void);
static void CB2_GoToNewGame(void);
static void CB2_GoToContinueSavedGame(void);
static void CB2_GoToResetRtcScreen(void);
static void CB2_GoToBerryFixScreen(void);
static void CB2_GoToCopyrightScreen(void);
static void CreateTitleScreenErrorWindow(const u8 *string, u8 left);
static void UpdateActionSelectionCursor(s16 *currItem, u8 delta);

static void SpriteCB_VersionBannerLeft(struct Sprite *sprite);
static void SpriteCB_VersionBannerRight(struct Sprite *sprite);
static void SpriteCB_PokemonLogoShine(struct Sprite *sprite);
static void SpriteCB_TitleScreenDeoxys(struct Sprite *sprite);


// const rom data
static const u32 sTitleScreenDeoxysNormalGfx[] = INCBIN_U32("graphics/title_screen/deoxys_normal.4bpp.lz");
static const u32 sTitleScreenDeoxysAttackGfx[] = INCBIN_U32("graphics/title_screen/deoxys_attack.4bpp.lz");
static const u32 sTitleScreenDeoxysDefenseGfx[] = INCBIN_U32("graphics/title_screen/deoxys_defense.4bpp.lz");
static const u32 sTitleScreenDeoxysSpeedGfx[] = INCBIN_U32("graphics/title_screen/deoxys_speed.4bpp.lz");
static const u32 sTitleScreenDeoxysPal[] = INCBIN_U32("graphics/title_screen/deoxys_normal.gbapal.lz");
static const u32 sTitleScreenRayquazaGfx[] = INCBIN_U32("graphics/title_screen/rayquaza.4bpp.lz");
static const u32 sTitleScreenRayquazaTilemap[] = INCBIN_U32("graphics/title_screen/rayquaza.bin.lz");
static const u32 sTitleScreenLogoShineGfx[] = INCBIN_U32("graphics/title_screen/logo_shine.4bpp.lz");
static const u8 sTitleScreenCursorGfx[] = INCBIN_U8("graphics/title_screen/cursor.4bpp");
static const u8 sTitleScreenTextColor[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY};
static const u8 sTitleScreenPressA[] = _("PRESS {A_BUTTON} TO CONTINUE");
static const u8 sVanadiumGameVersion[] = _("v0.0.1");
static const u8 sVanadiumDebugSuffix[] = _("-D");

enum
{
    WIN_MAIN,
};

static const struct BgTemplate sBgTemplates_TitleScreen[] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 29,
        .screenSize = 2,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0,
    },
    {
        .bg = 1,
        .charBaseIndex = 3,
        .mapBaseIndex = 27,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0,
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 9,
        .screenSize = 1,
        .paletteMode = 1,
        .priority = 1,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sWindowTemplates_TitleScreen[] =
{
    [WIN_MAIN] = {
        .bg = 1,
        .tilemapLeft = 5,
        .tilemapTop = 16,
        .width = 21,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x01,
    },
    DUMMY_WIN_TEMPLATE
};

static const struct ScanlineEffectParams sScanlineParams_Titlescreen_Clouds =
{
    .dmaDest = &REG_BG0HOFS,
    .dmaControl = SCANLINE_EFFECT_DMACNT_16BIT,
    .initState = 1
};

static const u16 sCloudScrollSpeeds[][7] =
{
    {Q_8_8(0.375), Q_8_8(0.5), Q_8_8(0.75), Q_8_8(1.0), Q_8_8(1.25), Q_8_8(1.5), Q_8_8(1.75)},
    {Q_8_8(0.375), Q_8_8(0.5), Q_8_8(0.75), Q_8_8(1.0), Q_8_8(1.25), Q_8_8(1.5), Q_8_8(1.75)},
    {Q_8_8(0.125), Q_8_8(0.25), Q_8_8(0.375), Q_8_8(0.5), Q_8_8(0.625), Q_8_8(0.75), Q_8_8(0.875)},
    {Q_8_8(0.75), Q_8_8(1.0), Q_8_8(1.5), Q_8_8(2.0), Q_8_8(2.5), Q_8_8(3.0), Q_8_8(3.5)},
};

static const u16 sCloudPanSpeeds[] =
{
    Q_8_8(0.5), Q_8_8(0.5), Q_8_8(0.5), Q_8_8(0.75)
};

static const u8 sDeoxysSineAmplitudes[] =
{
    2, 2, 2, 3,
};

static const u8 sDeoxysSineIncrements[] =
{
    6, 6, 4, 8,
};

// Used to blend "Emerald Version" as it passes over over the Pokémon banner.
// Also used by the intro to blend the Game Freak name/logo in and out as they appear and disappear
const u16 gTitleScreenAlphaBlend[64] =
{
    BLDALPHA_BLEND(16, 0),
    BLDALPHA_BLEND(16, 1),
    BLDALPHA_BLEND(16, 2),
    BLDALPHA_BLEND(16, 3),
    BLDALPHA_BLEND(16, 4),
    BLDALPHA_BLEND(16, 5),
    BLDALPHA_BLEND(16, 6),
    BLDALPHA_BLEND(16, 7),
    BLDALPHA_BLEND(16, 8),
    BLDALPHA_BLEND(16, 9),
    BLDALPHA_BLEND(16, 10),
    BLDALPHA_BLEND(16, 11),
    BLDALPHA_BLEND(16, 12),
    BLDALPHA_BLEND(16, 13),
    BLDALPHA_BLEND(16, 14),
    BLDALPHA_BLEND(16, 15),
    BLDALPHA_BLEND(15, 16),
    BLDALPHA_BLEND(14, 16),
    BLDALPHA_BLEND(13, 16),
    BLDALPHA_BLEND(12, 16),
    BLDALPHA_BLEND(11, 16),
    BLDALPHA_BLEND(10, 16),
    BLDALPHA_BLEND(9, 16),
    BLDALPHA_BLEND(8, 16),
    BLDALPHA_BLEND(7, 16),
    BLDALPHA_BLEND(6, 16),
    BLDALPHA_BLEND(5, 16),
    BLDALPHA_BLEND(4, 16),
    BLDALPHA_BLEND(3, 16),
    BLDALPHA_BLEND(2, 16),
    BLDALPHA_BLEND(1, 16),
    BLDALPHA_BLEND(0, 16),
    [32 ... 63] = BLDALPHA_BLEND(0, 16)
};

static const struct OamData sVersionBannerLeftOamData =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_8BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct OamData sVersionBannerRightOamData =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_8BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sVersionBannerLeftAnimSequence[] =
{
    ANIMCMD_FRAME(0, 30),
    ANIMCMD_END,
};

static const union AnimCmd sVersionBannerRightAnimSequence[] =
{
    ANIMCMD_FRAME(VERSION_BANNER_RIGHT_TILEOFFSET, 30),
    ANIMCMD_END,
};

static const union AnimCmd *const sVersionBannerLeftAnimTable[] =
{
    sVersionBannerLeftAnimSequence,
};

static const union AnimCmd *const sVersionBannerRightAnimTable[] =
{
    sVersionBannerRightAnimSequence,
};

static const struct SpriteTemplate sVersionBannerLeftSpriteTemplate =
{
    .tileTag = TAG_VERSION,
    .paletteTag = TAG_VERSION,
    .oam = &sVersionBannerLeftOamData,
    .anims = sVersionBannerLeftAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_VersionBannerLeft,
};

static const struct SpriteTemplate sVersionBannerRightSpriteTemplate =
{
    .tileTag = TAG_VERSION,
    .paletteTag = TAG_VERSION,
    .oam = &sVersionBannerRightOamData,
    .anims = sVersionBannerRightAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_VersionBannerRight,
};

static const struct CompressedSpriteSheet sSpriteSheet_EmeraldVersion[] =
{
    {
        .data = gTitleScreenEmeraldVersionGfx,
        .size = 0x1000,
        .tag = TAG_VERSION
    },
    {},
};

static const struct OamData sPokemonLogoShineOamData =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sPokemonLogoShineAnimSequence[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const sPokemonLogoShineAnimTable[] =
{
    sPokemonLogoShineAnimSequence,
};

static const struct SpriteTemplate sPokemonLogoShineSpriteTemplate =
{
    .tileTag = TAG_LOGO_SHINE,
    .paletteTag = TAG_PRESS_START_COPYRIGHT,
    .oam = &sPokemonLogoShineOamData,
    .anims = sPokemonLogoShineAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_PokemonLogoShine,
};

static const struct CompressedSpriteSheet sPokemonLogoShineSpriteSheet[] =
{
    {
        .data = sTitleScreenLogoShineGfx,
        .size = 0x800,
        .tag = TAG_LOGO_SHINE
    },
    {},
};

static const struct CompressedSpriteSheet sTitleScreenDeoxysFormsSpriteSheet[] =
{
    {
        .data = sTitleScreenDeoxysNormalGfx,
        .size = 0x2000,
        .tag = 1003,
    },
    {
        .data = sTitleScreenDeoxysAttackGfx,
        .size = 0x2000,
        .tag = 1003,
    },
    {
        .data = sTitleScreenDeoxysDefenseGfx,
        .size = 0x2000,
        .tag = 1003,
    },
    {
        .data = sTitleScreenDeoxysSpeedGfx,
        .size = 0x2000,
        .tag = 1003,
    },
};

static const struct CompressedSpritePalette sTitleScreenDeoxysSpritePalette =
{

    .data = sTitleScreenDeoxysPal,
    .tag = 1003,
};

static const struct OamData sTitleScreenDeoxysOamData =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = TRUE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sTitleScreenDeoxysAnim_Normal[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(32, 6),
    ANIMCMD_FRAME(64, 6),
    ANIMCMD_FRAME(96, 6),
    ANIMCMD_FRAME(128, 6),
    ANIMCMD_FRAME(160, 6),
    ANIMCMD_FRAME(192, 6),
    ANIMCMD_FRAME(224, 6),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sTitleScreenDeoxysAnim_Attack[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(32, 6),
    ANIMCMD_FRAME(64, 6),
    ANIMCMD_FRAME(96, 6),
    ANIMCMD_FRAME(128, 6),
    ANIMCMD_FRAME(160, 6),
    ANIMCMD_FRAME(192, 6),
    ANIMCMD_FRAME(224, 6),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sTitleScreenDeoxysAnim_Defense[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(32, 8),
    ANIMCMD_FRAME(64, 8),
    ANIMCMD_FRAME(96, 8),
    ANIMCMD_FRAME(128, 8),
    ANIMCMD_FRAME(160, 8),
    ANIMCMD_FRAME(192, 8),
    ANIMCMD_FRAME(224, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sTitleScreenDeoxysAnim_Speed[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(32, 4),
    ANIMCMD_FRAME(64, 4),
    ANIMCMD_FRAME(96, 4),
    ANIMCMD_FRAME(128, 4),
    ANIMCMD_FRAME(160, 4),
    ANIMCMD_FRAME(192, 4),
    ANIMCMD_FRAME(224, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sTitleScreenDeoxysAnimTable[] =
{
    sTitleScreenDeoxysAnim_Normal,
    sTitleScreenDeoxysAnim_Attack,
    sTitleScreenDeoxysAnim_Defense,
    sTitleScreenDeoxysAnim_Speed,
};

static const struct SpriteTemplate sTitleScreenDeoxysSpriteTemplate =
{
    .tileTag = 1003,
    .paletteTag = 1003,
    .oam = &sTitleScreenDeoxysOamData,
    .anims = sTitleScreenDeoxysAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_TitleScreenDeoxys,
};

enum
{
    HAS_NO_SAVED_GAME,  //NEW GAME, OPTION
    HAS_SAVED_GAME,     //CONTINUE, NEW GAME, OPTION
    HAS_MYSTERY_EVENTS, //CONTINUE, NEW GAME, MYSTERY GIFT, MYSTERY EVENTS, OPTION
};

enum
{
    ACTION_NEW_GAME,
    ACTION_CONTINUE,
    ACTION_OPTION,
    ACTION_MYSTERY_GIFT,
    ACTION_MYSTERY_EVENTS,
    ACTION_EREADER,
    ACTION_INVALID
};

// Task data for the main title screen tasks (Task_TitleScreenPhase#)
#define tCounter        data[0]
#define tSkipToNext     data[1]
#define tDeoxysState    data[3]
#define tBg2Y           data[3]
#define tDeoxysOldForm  data[4]
#define tDeoxysSinIndex data[5]
#define tDeoxysTimer    data[6]
#define tDeoxysMosaic   data[7]
#define tDeoxysForm     data[8]
#define tRedraw         data[9]
#define tVisible        data[10]
#define tTimer          data[11]
#define tCurrItem       data[12]
#define tItemCount      data[13]
#define tMenuType       data[14]
#define tAction         data[15]

// Sprite data for sVersionBannerLeftSpriteTemplate / sVersionBannerRightSpriteTemplate
#define sAlphaBlendIdx data[0]
#define sParentTaskId  data[1]

static void SpriteCB_VersionBannerLeft(struct Sprite *sprite)
{
    if (gTasks[sprite->sParentTaskId].tSkipToNext)
    {
        sprite->oam.objMode = ST_OAM_OBJ_NORMAL;
        sprite->y = VERSION_BANNER_Y_GOAL;
    }
    else
    {
        if (sprite->y != VERSION_BANNER_Y_GOAL)
            sprite->y++;
        if (sprite->sAlphaBlendIdx != 0)
            sprite->sAlphaBlendIdx--;
        SetGpuReg(REG_OFFSET_BLDALPHA, gTitleScreenAlphaBlend[sprite->sAlphaBlendIdx]);
    }
}

static void SpriteCB_VersionBannerRight(struct Sprite *sprite)
{
    if (gTasks[sprite->sParentTaskId].tSkipToNext)
    {
        sprite->oam.objMode = ST_OAM_OBJ_NORMAL;
        sprite->y = VERSION_BANNER_Y_GOAL;
    }
    else
    {
        if (sprite->y != VERSION_BANNER_Y_GOAL)
            sprite->y++;
    }
}

// Defines for SpriteCB_PokemonLogoShine
enum {
    SHINE_MODE_SINGLE_NO_BG_COLOR,
    SHINE_MODE_DOUBLE,
    SHINE_MODE_SINGLE,
};

#define SHINE_SPEED  4

#define sMode     data[0]
#define sBgColor  data[1]

static void SpriteCB_PokemonLogoShine(struct Sprite *sprite)
{
    if (sprite->x < DISPLAY_WIDTH + 32)
    {
        // In any mode except SHINE_MODE_SINGLE_NO_BG_COLOR the background
        // color will change, in addition to the shine sprite moving.
        if (sprite->sMode != SHINE_MODE_SINGLE_NO_BG_COLOR)
        {
            u16 backgroundColor;

            if (sprite->x < DISPLAY_WIDTH / 2)
            {
                // Brighten background color
                if (sprite->sBgColor < 31)
                    sprite->sBgColor++;
                if (sprite->sBgColor < 31)
                    sprite->sBgColor++;
            }
            else
            {
                // Darken background color
                if (sprite->sBgColor != 0)
                    sprite->sBgColor--;
                if (sprite->sBgColor != 0)
                    sprite->sBgColor--;
            }

            backgroundColor = _RGB(sprite->sBgColor, sprite->sBgColor, sprite->sBgColor);

            // Flash the background green for 4 frames of movement.
            // Otherwise use the updating color.
            if (sprite->x == DISPLAY_WIDTH / 2 + (3 * SHINE_SPEED)
                || sprite->x == DISPLAY_WIDTH / 2 + (4 * SHINE_SPEED)
                || sprite->x == DISPLAY_WIDTH / 2 + (5 * SHINE_SPEED)
                || sprite->x == DISPLAY_WIDTH / 2 + (6 * SHINE_SPEED))
                gPlttBufferFaded[0] = RGB(31, 31, 26);
            else
                gPlttBufferFaded[0] = backgroundColor;
        }

        sprite->x += SHINE_SPEED;
    }
    else
    {
        // Sprite has moved fully offscreen
        gPlttBufferFaded[0] = RGB_BLACK;
        DestroySprite(sprite);
    }
}

static void SpriteCB_PokemonLogoShine_Fast(struct Sprite *sprite)
{
    if (sprite->x < DISPLAY_WIDTH + 32)
        sprite->x += SHINE_SPEED * 2;
    else
        DestroySprite(sprite);
}

static void StartPokemonLogoShine(u8 mode)
{
    u8 spriteId;

    switch (mode)
    {
    case SHINE_MODE_SINGLE_NO_BG_COLOR:
    case SHINE_MODE_SINGLE:
        // Create one regular shine sprite.
        // If mode is SHINE_MODE_SINGLE it will also change the background color.
        spriteId = CreateSprite(&sPokemonLogoShineSpriteTemplate, 0, 68, 0);
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
        gSprites[spriteId].sMode = mode;
        break;
    case SHINE_MODE_DOUBLE:
        // Create an invisible sprite with mode set to update the background color
        spriteId = CreateSprite(&sPokemonLogoShineSpriteTemplate, 0, 68, 0);
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
        gSprites[spriteId].sMode = mode;
        gSprites[spriteId].invisible = TRUE;

        // Create two faster shine sprites
        spriteId = CreateSprite(&sPokemonLogoShineSpriteTemplate, 0, 68, 0);
        gSprites[spriteId].callback = SpriteCB_PokemonLogoShine_Fast;
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;

        spriteId = CreateSprite(&sPokemonLogoShineSpriteTemplate, -80, 68, 0);
        gSprites[spriteId].callback = SpriteCB_PokemonLogoShine_Fast;
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
        break;
    }
}

#undef sMode
#undef sBgColor

static void SpriteCB_TitleScreenDeoxys(struct Sprite *sprite)
{
    struct Task *task = &gTasks[sprite->data[0]];
    u16 backgroundState = gTasks[sScrollTaskId].data[9];
    u8 mosaicHorizontal;
    u8 mosaicVertical;
    u16 newForm;

    switch (task->tDeoxysState)
    {
        case 0:
            if (sprite->x2 < (DISPLAY_WIDTH / 2) + 32)
                sprite->x2 += 2;
            else
                task->tDeoxysState++;
            break;
        case 1:
            task->tDeoxysTimer = (Random() % (DEOXYS_TIMER_MAX - DEOXYS_TIMER_MIN + 1)) + DEOXYS_TIMER_MIN;
            task->tDeoxysState++;
            break;
        case 2:
            if (backgroundState != 3)
            {
                if (task->tDeoxysTimer != 0)
                {
                    task->tDeoxysTimer--;
                }
                else
                {
                    task->tDeoxysState++;
                    task->tDeoxysTimer = 0;
                    PlaySE(SE_M_TELEPORT);
                }
            }
            break;
        case 3:
            if (task->tDeoxysTimer ^= 1)
            {
                if (task->tDeoxysMosaic < 8)
                    task->tDeoxysMosaic++;
                else
                    task->tDeoxysState++;
            }
            break;
        case 4:
            do
            {
                newForm = Random() % 4;
            }
            while (newForm == task->tDeoxysForm);

            DmaClear16(3, (void *)(OBJ_VRAM0 + (sprite->sheetTileStart * TILE_SIZE_4BPP)), 8192);
            LZ77UnCompVram(sTitleScreenDeoxysFormsSpriteSheet[newForm].data, (void *)(OBJ_VRAM0 + (sprite->sheetTileStart * TILE_SIZE_4BPP)));
            StartSpriteAnim(sprite, newForm);
            task->tDeoxysOldForm = task->tDeoxysForm;
            task->tDeoxysForm = newForm;
            task->tDeoxysTimer = 0;
            task->tDeoxysState++;
            break;
        case 5:
            if (task->tDeoxysTimer ^= 1)
            {
                if (task->tDeoxysMosaic > 0)
                    task->tDeoxysMosaic--;
                else
                    task->tDeoxysState = 1;
            }
            break;
        case 6:
            break;
    }

    SetGpuReg(REG_OFFSET_MOSAIC, (task->tDeoxysMosaic << 4 | task->tDeoxysMosaic) << 8);

    sprite->y2 = Sin(task->tDeoxysSinIndex, sDeoxysSineAmplitudes[task->tDeoxysForm]);
    task->tDeoxysSinIndex += sDeoxysSineIncrements[task->tDeoxysForm];
    task->tDeoxysSinIndex &= 0xFF;
}

static void VBlankCB(void)
{
    ScanlineEffect_InitHBlankDmaTransfer();
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_Titlescreen_AnimateSky(u8 taskId)
{
    struct Task *task = &gTasks[gSprites[sDeoxysSpriteId].data[0]];
    s16 *data = gTasks[taskId].data;
    u16 offset;
    u16 newTarget;

    data[0] += sCloudScrollSpeeds[task->tDeoxysForm][0];
    data[1] += sCloudScrollSpeeds[task->tDeoxysForm][1];
    data[2] += sCloudScrollSpeeds[task->tDeoxysForm][2];
    data[3] += sCloudScrollSpeeds[task->tDeoxysForm][3];
    data[4] += sCloudScrollSpeeds[task->tDeoxysForm][4];
    data[5] += sCloudScrollSpeeds[task->tDeoxysForm][5];
    data[6] += sCloudScrollSpeeds[task->tDeoxysForm][6];

    data[7] += 3;
    data[7] &= 0x7F;
    data[8] = gSineTable[data[7]] >> 5;

    BlendPalette(234, 1, data[8], RGB(6, 4, 7));
    BlendPalette(235, 1, data[8], RGB(6, 6, 10));
    BlendPalette(238, 1, data[8], RGB(3, 2, 4));
    BlendPalette(239, 1, data[8], RGB(1, 1, 1));

    switch (data[9])
    {
        case 0:
            if (task->tDeoxysState != 0 && sIsDeoxysSpawned == TRUE)
            {
                data[10] = (Random() % (BACKGROUND_TIMER_MAX - BACKGROUND_TIMER_MIN + 1)) + BACKGROUND_TIMER_MIN;
                data[9]++;
            }
            break;
        case 1:
            if (data[10] != 0)
            {
                data[10]--;
            }
            else
            {
                data[9]++;
                data[10] = 0;
            }
            break;
        case 2:
            do
            {
                newTarget = Q_8_8(Random() % BACKGROUND_DELTA_MAX + 1);
            }
            while (abs(newTarget - data[11]) <= Q_8_8(BACKGROUND_DELTA_MIN));

            data[11] = newTarget;
            data[9]++;
            break;
        case 3:
            if (sBg0HorizontalOffset != data[11])
            {
                if (sBg0HorizontalOffset < data[11])
                    sBg0HorizontalOffset += Q_8_8(0.5);
                else
                    sBg0HorizontalOffset -= Q_8_8(0.5);

                SetGpuReg(REG_OFFSET_BG0VOFS, 512 - Q_8_8_TO_INT(sBg0HorizontalOffset));
            }
            else
            {
                data[9] = 0;
            }
            break;
    }

    offset = Q_8_8_TO_INT(sBg0HorizontalOffset);

    for (u32 i = 0; i < DISPLAY_HEIGHT; i++)
    {
        if (i <= 82 + offset)
        {
            gScanlineEffectRegBuffers[0][i] = 0;
            gScanlineEffectRegBuffers[1][i] = 0;
        }
        else if (i <= 87 + offset)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[0]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[0]);
        }
        else if (i <= 92 + offset)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[1]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[1]);
        }
        else if (i <= 99 + offset)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[2]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[2]);
        }
        else if (i <= 111 + offset)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[3]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[3]);
        }
        else if (i <= 128 + offset)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[4]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[4]);
        }
        else if (i <= 138 + offset)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[5]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[5]);
        }
        else if (i <= DISPLAY_HEIGHT + offset)
        {
            gScanlineEffectRegBuffers[0][i] = Q_8_8_TO_INT(data[6]);
            gScanlineEffectRegBuffers[1][i] = Q_8_8_TO_INT(data[6]);
        }
    }
}

void CB2_InitTitleScreen(void)
{
    u8 taskId;

    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        StartTimer1();
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        *((u16 *)PLTT) = RGB_WHITE;
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_BG2CNT, 0);
        SetGpuReg(REG_OFFSET_BG1CNT, 0);
        SetGpuReg(REG_OFFSET_BG0CNT, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        SetGpuReg(REG_OFFSET_MOSAIC, 0);
        DmaFill16(3, 0, (void *)VRAM, VRAM_SIZE);
        DmaFill32(3, 0, (void *)OAM, OAM_SIZE);
        DmaFill16(3, 0, (void *)(PLTT + 2), PLTT_SIZE - 2);
        ResetTasks();
        ResetSpriteData();
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ScanlineEffect_Clear();
        FreeAllSpritePalettes();
        DeactivateAllTextPrinters();
        gReservedSpritePaletteCount = 9;
        InitBgsFromTemplates(DISPCNT_MODE_1, sBgTemplates_TitleScreen, ARRAY_COUNT(sBgTemplates_TitleScreen));
        HideBg(0);
        HideBg(1);
        HideBg(2);
        InitWindows(sWindowTemplates_TitleScreen);
        gMain.state = 1;
        break;
    case 1:
        // bg2
        LZ77UnCompVram(gTitleScreenPokemonLogoGfx, (void *)(BG_CHAR_ADDR(0)));
        LZ77UnCompVram(gTitleScreenPokemonLogoTilemap, (void *)(BG_SCREEN_ADDR(9)));
        LoadPalette(gTitleScreenBgPalettes, BG_PLTT_ID(0), 15 * PLTT_SIZE_4BPP);
        // bg1
        LoadPalette(GetOverworldTextboxPalettePtr(), 0xF0, 0x20);
        // bg0
        LZ77UnCompVram(sTitleScreenRayquazaGfx, (void *)(BG_CHAR_ADDR(2)));
        LZ77UnCompVram(sTitleScreenRayquazaTilemap, (void *)(BG_SCREEN_ADDR(29)));
        LoadCompressedSpriteSheet(&sSpriteSheet_EmeraldVersion[0]);
        LoadCompressedSpriteSheet(&sPokemonLogoShineSpriteSheet[0]);
        LoadCompressedSpriteSheet(&sTitleScreenDeoxysFormsSpriteSheet[0]);
        LoadCompressedSpritePalette(&sTitleScreenDeoxysSpritePalette);
        LoadPalette(gTitleScreenEmeraldVersionPal, OBJ_PLTT_ID(0), PLTT_SIZE_4BPP);
        gMain.state = 2;
        break;
    case 2:
        CpuFastFill16(0, gScanlineEffectRegBuffers, sizeof(gScanlineEffectRegBuffers));
        ScanlineEffect_SetParams(sScanlineParams_Titlescreen_Clouds);
        sScrollTaskId = CreateTask(Task_Titlescreen_AnimateSky, 1);
        taskId = CreateTask(Task_TitleScreenPhase1, 0);
        gTasks[taskId].tCounter = 256;
        gTasks[taskId].tSkipToNext = FALSE;
        gTasks[taskId].tBg2Y = -32;
        gMain.state = 3;
        break;
    case 3:
        BeginNormalPaletteFade(PALETTES_ALL, 1, 16, 0, RGB_WHITEALPHA);
        SetVBlankCallback(VBlankCB);
        gMain.state = 4;
        break;
    case 4:
        SetGpuReg(REG_OFFSET_BG2X_L, -29 * 256);
        SetGpuReg(REG_OFFSET_BG2X_H, -1);
        SetGpuReg(REG_OFFSET_BG2Y_L, -32 * 256);
        SetGpuReg(REG_OFFSET_BG2Y_H, -1);
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WINOBJ_ALL);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_LIGHTEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 12);
        SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(3) | BGCNT_CHARBASE(2) | BGCNT_SCREENBASE(26) | BGCNT_16COLOR | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(2) | BGCNT_CHARBASE(3) | BGCNT_SCREENBASE(27) | BGCNT_16COLOR | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG2CNT, BGCNT_PRIORITY(1) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(9) | BGCNT_256COLOR | BGCNT_AFF256x256);
        EnableInterrupts(INTR_FLAG_VBLANK);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_1 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG2_ON | DISPCNT_OBJ_ON | DISPCNT_OBJWIN_ON);
        ShowBg(2);
        m4aSongNumStart(MUS_TITLE);
        gMain.state = 5;
        break;
    case 5:
        if (!UpdatePaletteFade())
        {
            StartPokemonLogoShine(SHINE_MODE_SINGLE_NO_BG_COLOR);
            SetMainCallback2(MainCB2);
        }
        break;
    }
}

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    RunTextPrinters();
    UpdatePaletteFade();
}

// Shine the Pokémon logo two more times, and fade in the version banner
static void Task_TitleScreenPhase1(u8 taskId)
{
    // Skip to next phase when A, B, Start, or Select is pressed
    if (JOY_NEW(A_B_START_SELECT) || gTasks[taskId].tSkipToNext)
    {
        gTasks[taskId].tSkipToNext = TRUE;
        gTasks[taskId].tCounter = 0;
    }

    if (gTasks[taskId].tCounter != 0)
    {
        u16 frameNum = gTasks[taskId].tCounter;
        if (frameNum == 176)
            StartPokemonLogoShine(SHINE_MODE_DOUBLE);
        else if (frameNum == 64)
            StartPokemonLogoShine(SHINE_MODE_SINGLE);

        gTasks[taskId].tCounter--;
    }
    else
    {
        u8 spriteId;

        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_1 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG2_ON | DISPCNT_OBJ_ON);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_OBJ | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL);
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));
        SetGpuReg(REG_OFFSET_BLDY, 0);
        ShowBg(2);

        // Create left side of version banner
        spriteId = CreateSprite(&sVersionBannerLeftSpriteTemplate, VERSION_BANNER_LEFT_X, VERSION_BANNER_Y, 0);
        gSprites[spriteId].sAlphaBlendIdx = ARRAY_COUNT(gTitleScreenAlphaBlend);
        gSprites[spriteId].sParentTaskId = taskId;

        // Create right side of version banner
        spriteId = CreateSprite(&sVersionBannerRightSpriteTemplate, VERSION_BANNER_RIGHT_X, VERSION_BANNER_Y, 0);
        gSprites[spriteId].sParentTaskId = taskId;

        gTasks[taskId].tCounter = 144;
        gTasks[taskId].func = Task_TitleScreenPhase2;
    }
}

#undef sParentTaskId
#undef sAlphaBlendIdx

// Create "Press Start" and copyright banners, and slide Pokémon logo up
static void Task_TitleScreenPhase2(u8 taskId)
{
    u32 yPos;

    // Skip to next phase when A, B, Start, or Select is pressed
    if (JOY_NEW(A_B_START_SELECT) || gTasks[taskId].tSkipToNext)
    {
        gTasks[taskId].tSkipToNext = TRUE;
        gTasks[taskId].tCounter = 0;
    }

    if (gTasks[taskId].tCounter != 0)
    {
        gTasks[taskId].tCounter--;
    }
    else
    {
        gTasks[taskId].tSkipToNext = TRUE;
        gTasks[taskId].tRedraw = TRUE;
        gTasks[taskId].tTimer = BLINK_TIMER;
        gTasks[taskId].tVisible = TRUE;
        PutWindowTilemap(WIN_MAIN);
        CopyWindowToVram(WIN_MAIN, COPYWIN_FULL);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_1 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_OBJ_ON);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);

        sDeoxysSpriteId = CreateSprite(&sTitleScreenDeoxysSpriteTemplate, -32, 108, 1);
        gTasks[taskId].tDeoxysState = 0;
        gTasks[taskId].tDeoxysMosaic = 0;
        gTasks[taskId].tDeoxysOldForm = 0;
        gTasks[taskId].tDeoxysForm = 0;
        gSprites[sDeoxysSpriteId].data[0] = taskId;
        sIsDeoxysSpawned = TRUE;
        gTasks[taskId].func = Task_ContinuePressA;
    }

    if (!(gTasks[taskId].tCounter & 1) && gTasks[taskId].tBg2Y != 0)
        gTasks[taskId].tBg2Y++;

    // Slide Pokemon logo up
    if (gTasks[taskId].tSkipToNext)
    {
        SetGpuReg(REG_OFFSET_BG2Y_L, 0);
        SetGpuReg(REG_OFFSET_BG2Y_H, 0);
    }
    else
    {
        yPos = gTasks[taskId].data[3] * 256;
        SetGpuReg(REG_OFFSET_BG2Y_L, yPos);
        SetGpuReg(REG_OFFSET_BG2Y_H, yPos / 0x10000);
    }

    gTasks[taskId].data[5] = 15;
}

static void Task_ContinuePressA(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    u8 left;

    if (--task->tTimer == 0)
    {
        task->tRedraw = TRUE;
        task->tVisible ^= TRUE;
        task->tTimer = BLINK_TIMER;
    }

    if (task->tRedraw)
    {
        FillWindowPixelBuffer(WIN_MAIN, PIXEL_FILL(0));

        if (task->tVisible)
        {
            left = GetStringCenterAlignXOffset(FONT_SMALL, sTitleScreenPressA, 160);
            AddTextPrinterParameterized3(WIN_MAIN, FONT_SMALL, left, 7, sTitleScreenTextColor, 0, sTitleScreenPressA);
        }

        CopyWindowToVram(WIN_MAIN, COPYWIN_GFX);
        task->tRedraw = FALSE;
    }

    if (JOY_NEW(A_BUTTON) || JOY_NEW(START_BUTTON))
    {
        PlaySE(SE_SELECT);
        task->func = Task_TitleScreenCheckSave;
    }

    if ((gMPlayInfo_BGM.status & 0xFFFF) == 0)
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_WHITEALPHA);
        SetMainCallback2(CB2_GoToCopyrightScreen);
    }
}

static void Task_TitleScreenCheckSave(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    SetGpuReg(REG_OFFSET_BG2Y_L, 0);
    SetGpuReg(REG_OFFSET_BG2Y_H, 0);
    EnableMysteryEvent();
    EnableMysteryGift();

    switch (gSaveFileStatus)
    {
        case SAVE_STATUS_OK:
            task->tMenuType = HAS_SAVED_GAME;
            if (IsMysteryEventEnabled())
                task->tMenuType++;
            task->func = Task_TitleScreenCheckBattery;
            break;
        case SAVE_STATUS_CORRUPT:
            CreateTitleScreenErrorWindow(gText_SaveFileErased, 12);
            task->tMenuType = HAS_NO_SAVED_GAME;
            task->func = Task_WaitForTitleScreenSaveErrorMessage;
            break;
        case SAVE_STATUS_ERROR:
            CreateTitleScreenErrorWindow(gText_SaveFileCorrupted, 2);
            task->func = Task_WaitForTitleScreenSaveErrorMessage;
            task->tMenuType = HAS_SAVED_GAME;
            if (IsMysteryGiftEnabled() == TRUE)
                task->tMenuType++;
            break;
        case SAVE_STATUS_EMPTY:
        default:
            task->tMenuType = HAS_NO_SAVED_GAME;
            task->func = Task_TitleScreenCheckBattery;
            break;
        case SAVE_STATUS_NO_FLASH:
            CreateTitleScreenErrorWindow(gText_No1MSubCircuit, 20);
            task->tMenuType = HAS_NO_SAVED_GAME;
            task->func = Task_WaitForTitleScreenSaveErrorMessage;
            break;
    }

    task->tItemCount = task->tMenuType + 2;
}

static void Task_WaitForTitleScreenSaveErrorMessage(u8 taskId)
{
    if (GetGpuReg(REG_OFFSET_BLDY) < 8)
    {
        SetGpuReg(REG_OFFSET_BLDY, GetGpuReg(REG_OFFSET_BLDY) + 1);
    }
    else
    {
        if (!IsTextPrinterActive(WIN_MAIN) && (JOY_NEW(A_BUTTON)))
        {
            FillWindowPixelBuffer(WIN_MAIN, PIXEL_FILL(0));
            CopyWindowToVram(WIN_MAIN, COPYWIN_GFX);
            gTasks[taskId].func = Task_TitleScreenCheckBattery;
        }
    }

    if ((gMPlayInfo_BGM.status & 0xFFFF) == 0)
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
        SetMainCallback2(CB2_GoToCopyrightScreen);
    }
}

static void Task_TitleScreenCheckBattery(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    u32 rtcErrorStatus = RtcGetErrorStatus();

    if (!(rtcErrorStatus & RTC_ERR_FLAG_MASK))
    {
        gTasks[taskId].func = Task_WaitForBackgroundFade;
    }
    else
    {
        CreateTitleScreenErrorWindow(gText_BatteryRunDry, 4);
        gTasks[taskId].func = Task_WaitForTitleScreenBatteryErrorMessage;
    }
}

static void Task_WaitForTitleScreenBatteryErrorMessage(u8 taskId)
{
    if (GetGpuReg(REG_OFFSET_BLDY) < 8)
    {
        SetGpuReg(REG_OFFSET_BLDY, GetGpuReg(REG_OFFSET_BLDY) + 1);
    }
    else
    {
        if (!IsTextPrinterActive(WIN_MAIN) && (JOY_NEW(A_BUTTON)))
        {
            FillWindowPixelBuffer(WIN_MAIN, PIXEL_FILL(0));
            CopyWindowToVram(WIN_MAIN, COPYWIN_GFX);
            gTasks[taskId].func = Task_WaitForBackgroundFade;
        }
    }

    if ((gMPlayInfo_BGM.status & 0xFFFF) == 0)
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
        SetMainCallback2(CB2_GoToCopyrightScreen);
    }
}

static void Task_WaitForBackgroundFade(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    if (GetGpuReg(REG_OFFSET_BLDY) > 0)
    {
        SetGpuReg(REG_OFFSET_BLDY, GetGpuReg(REG_OFFSET_BLDY) - 1);
    }
    else
    {
        task->func = Task_BuildTitleScreenMenu;
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
    }

    if ((gMPlayInfo_BGM.status & 0xFFFF) == 0)
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_WHITEALPHA);
        SetMainCallback2(CB2_GoToCopyrightScreen);
    }
}

static void Task_BuildTitleScreenMenu(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    u8 text[16];
    u8 spriteId;

    FillWindowPixelBuffer(WIN_MAIN, PIXEL_FILL(0));

    switch (task->tMenuType)
    {
        case HAS_NO_SAVED_GAME:
        default:
            AddTextPrinterParameterized3(WIN_MAIN, FONT_SMALL, 8, 5, sTitleScreenTextColor, 0, gText_MainMenuNewGame);
            AddTextPrinterParameterized3(WIN_MAIN, FONT_SMALL, 104, 5, sTitleScreenTextColor, 0, gText_MainMenuOption);
            break;
        case HAS_SAVED_GAME:
            AddTextPrinterParameterized3(WIN_MAIN, FONT_SMALL, 8, 5, sTitleScreenTextColor, 0, gText_MainMenuContinue);
            AddTextPrinterParameterized3(WIN_MAIN, FONT_SMALL, 8, 17, sTitleScreenTextColor, 0, gText_MainMenuNewGame);
            AddTextPrinterParameterized3(WIN_MAIN, FONT_SMALL, 104, 5, sTitleScreenTextColor, 0, gText_MainMenuOption);
            break;
        case HAS_MYSTERY_EVENTS:
            AddTextPrinterParameterized3(WIN_MAIN, FONT_SMALL, 8, 5, sTitleScreenTextColor, 0, gText_MainMenuContinue);
            AddTextPrinterParameterized3(WIN_MAIN, FONT_SMALL, 8, 17, sTitleScreenTextColor, 0, gText_MainMenuNewGame);
            AddTextPrinterParameterized3(WIN_MAIN, FONT_SMALL, 104, 5, sTitleScreenTextColor, 0, gText_MainMenuOption);
            AddTextPrinterParameterized3(WIN_MAIN, FONT_SMALL, 104, 17, sTitleScreenTextColor, 0, gText_MainMenuMysteryEventsGift);
            break;
    }

    CopyWindowToVram(WIN_MAIN, COPYWIN_FULL);
    task->tCurrItem = 0;
    UpdateActionSelectionCursor(&task->tCurrItem, sCurrActionOptionCheck);
    sCurrActionOptionCheck = FALSE;
    task->func = Task_TitleScreenPhase3;
}

// Show full titlescreen and process main title screen input
static void Task_TitleScreenPhase3(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    if (JOY_HELD(HIDE_MENU_BUTTON_COMBO) == HIDE_MENU_BUTTON_COMBO)
    {
        HideBg(1);
    }
    else if (JOY_NEW(A_BUTTON))
    {
        FadeOutBGM(2);
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
        task->func = Task_TitleScreenHandleAPress;
    }
    else if (JOY_NEW(DPAD_LEFT))
    {
        if (task->tCurrItem & 1 && (task->tCurrItem > 0))
        {
            PlaySE(SE_SELECT);
            UpdateActionSelectionCursor(&task->tCurrItem, 1);
        }
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        if (!(task->tCurrItem & 1) && (task->tCurrItem ^ 1) < task->tItemCount)
        {
            PlaySE(SE_SELECT);
            UpdateActionSelectionCursor(&task->tCurrItem, 1);
        }
    }
    else if (JOY_NEW(DPAD_UP))
    {
        if (task->tCurrItem & 2 && (task->tCurrItem > 0))
        {
            PlaySE(SE_SELECT);
            UpdateActionSelectionCursor(&task->tCurrItem, 2);
        }
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        if (!(task->tCurrItem & 2) && (task->tCurrItem ^ 2) < task->tItemCount)
        {
            PlaySE(SE_SELECT);
            UpdateActionSelectionCursor(&task->tCurrItem, 2);
        }
    }
    else if (JOY_HELD(CLEAR_SAVE_BUTTON_COMBO) == CLEAR_SAVE_BUTTON_COMBO)
    {
        SetMainCallback2(CB2_GoToClearSaveDataScreen);
    }
    else if (JOY_HELD(RESET_RTC_BUTTON_COMBO) == RESET_RTC_BUTTON_COMBO)
    {
        FadeOutBGM(4);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        SetMainCallback2(CB2_GoToResetRtcScreen);
    }
    else if (JOY_HELD(BERRY_UPDATE_BUTTON_COMBO) == BERRY_UPDATE_BUTTON_COMBO)
    {
        FadeOutBGM(4);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        SetMainCallback2(CB2_GoToBerryFixScreen);
    }
    else
    {
        ShowBg(1);
        if ((gMPlayInfo_BGM.status & 0xFFFF) == 0)
        {
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_WHITEALPHA);
            SetMainCallback2(CB2_GoToCopyrightScreen);
        }
    }

    if (GetGpuReg(REG_OFFSET_BLDY) > 0)
    {
        SetGpuReg(REG_OFFSET_BLDY, GetGpuReg(REG_OFFSET_BLDY) - 1);
    }
    else
    {
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
    }
}

static void Task_TitleScreenHandleAPress(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    if (!gPaletteFade.active)
    {
        ScanlineEffect_Stop();
        ScanlineEffect_Clear();
        sCurrActionOptionCheck = FALSE;

        switch (task->tMenuType)
        {
            case HAS_NO_SAVED_GAME:
            default:
                switch (task->tCurrItem)
                {
                    case 0:
                    default:
                        task->tAction = ACTION_NEW_GAME;
                        break;
                    case 1:
                        task->tAction = ACTION_OPTION;
                        break;
                }
                break;
            case HAS_SAVED_GAME:
                switch (task->tCurrItem)
                {
                    case 0:
                    default:
                        task->tAction = ACTION_CONTINUE;
                        break;
                    case 1:
                        task->tAction = ACTION_OPTION;
                        break;
                    case 2:
                        task->tAction = ACTION_NEW_GAME;
                        break;
                }
                break;
            case HAS_MYSTERY_EVENTS:
                switch (task->tCurrItem)
                {
                    case 0:
                    default:
                        task->tAction = ACTION_CONTINUE;
                        break;
                    case 1:
                        task->tAction = ACTION_OPTION;
                        break;
                    case 2:
                        task->tAction = ACTION_NEW_GAME;
                        break;
                    case 3:
                        if (IsWirelessAdapterConnected())
                            task->tAction = ACTION_MYSTERY_GIFT;
                        else
                            task->tAction = ACTION_MYSTERY_EVENTS;
                        break;
                }
                break;
        }

        switch (task->tAction)
        {
            case ACTION_NEW_GAME:
            default:
                gPlttBufferUnfaded[0] = RGB_BLACK;
                gPlttBufferFaded[0] = RGB_BLACK;
                SetMainCallback2(CB2_GoToNewGame);
                DestroyTask(taskId);
                break;
            case ACTION_CONTINUE:
                gPlttBufferUnfaded[0] = RGB_BLACK;
                gPlttBufferFaded[0] = RGB_BLACK;
                SetMainCallback2(CB2_ContinueSavedGame);
                DestroyTask(taskId);
                break;
            case ACTION_OPTION:
                sCurrActionOptionCheck = TRUE;
                gMain.savedCallback = CB2_InitTitleScreen;
                SetMainCallback2(CB2_InitOptionMenu);
                DestroyTask(taskId);
                break;
            case ACTION_MYSTERY_GIFT:
                SetMainCallback2(CB2_InitMysteryGift);
                DestroyTask(taskId);
                break;
            case ACTION_MYSTERY_EVENTS:
                SetMainCallback2(CB2_InitMysteryEventMenu);
                DestroyTask(taskId);
                break;
        }
        FreeAllWindowBuffers();
    }
}

static void CB2_GoToMainMenu(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitMainMenu);
}

static void CB2_GoToCopyrightScreen(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitCopyrightScreenAfterTitleScreen);
}

static void CB2_GoToClearSaveDataScreen(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitClearSaveDataScreen);
}

static void CB2_GoToNewGame(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_NewGameBirchSpeech);
}

static void CB2_GoToContinueSavedGame(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_ContinueSavedGame);
}

static void CB2_GoToResetRtcScreen(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitResetRtcScreen);
}

static void CB2_GoToBerryFixScreen(void)
{
    if (!UpdatePaletteFade())
    {
        m4aMPlayAllStop();
        SetMainCallback2(CB2_InitBerryFixProgram);
    }
}

static void CreateTitleScreenErrorWindow(const u8 *string, u8 left)
{
    FillWindowPixelBuffer(WIN_MAIN, PIXEL_FILL(0));
    AddTextPrinterParameterized3(WIN_MAIN, FONT_SMALL, left, 2, sTitleScreenTextColor, 2, string);
    CopyWindowToVram(WIN_MAIN, COPYWIN_FULL);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_DARKEN | BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG2 | BLDCNT_TGT1_OBJ);
}

static void UpdateActionSelectionCursor(s16 *currItem, u8 delta)
{
    FillWindowPixelRect(WIN_MAIN, PIXEL_FILL(0), (*currItem & 1) * 96 + 2, (*currItem & 2) * 6 + 9, 4, 7);
    *currItem ^= delta;
    BlitBitmapRectToWindow(WIN_MAIN, sTitleScreenCursorGfx, 0, 0, 8, 8, (*currItem & 1) * 96 + 2, (*currItem & 2) * 6 + 9, 8, 8);
    CopyWindowToVram(WIN_MAIN, COPYWIN_GFX);
}
