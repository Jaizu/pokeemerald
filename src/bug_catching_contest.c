#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "bug_catching_contest.h"
#include "data.h"
#include "event_data.h"
#include "fieldmap.h"
#include "field_screen_effect.h"
#include "load_save.h"
#include "malloc.h"
#include "overworld.h"
#include "party_menu.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "pokemon_summary_screen.h"
#include "random.h"
#include "script.h"
#include "sort.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "tv.h"
#include "wild_encounter.h"
#include "constants/event_objects.h"
#include "constants/heal_locations.h"
#include "constants/layouts.h"
#include "constants/trainers.h"
#include "data/bug_catching_contest.h"

extern const u8 ValoonReserve_EventScript_RetirePrompt[];
extern const u8 ValoonReserve_EventScript_OutOfBallsMidBattle[];
extern const u8 ValoonReserve_EventScript_OutOfBallsBeginJudging[];

EWRAM_DATA u8 gNumParkBalls = 0;
EWRAM_DATA static struct BugCatchingContestant sContestants[CONTESTANT_COUNT + 1] =
{
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
};

void ResetCaughtBug(void);
void ResetContestants(void);
void SelectContestants(void);
void SetContestantObjectEventSprites(void);

bool32 GetBugCatchingContestFlag(void)
{
    return FlagGet(FLAG_SYS_BUG_CATCHING_CONTEST_MODE);
}

void SetBugCatchingContestFlag(void)
{
    FlagSet(FLAG_SYS_BUG_CATCHING_CONTEST_MODE);
}

void ResetBugCatchingContestFlag(void)
{
    FlagClear(FLAG_SYS_BUG_CATCHING_CONTEST_MODE);
}

bool8 InValoonReserve(void)
{
    return gMapHeader.mapLayoutId == LAYOUT_VALOON_RESERVE;
}

void ResetValoonReserveState(void)
{
    *GetVarPointer(VAR_VALOON_RESERVE_STATE) = 0;
}

void ReducePlayerPartyToSelectedMon(void)
{
    struct Pokemon party[1];

    CpuFill32(0, party, sizeof party);
    party[0] = gPlayerParty[gSpecialVar_0x8004];
    CpuFill32(0, gPlayerParty, sizeof gPlayerParty);
    gPlayerParty[0] = party[0];

    CalculatePlayerPartyCount();
}

void EnterBugCatchingContestMode(void)
{
    SavePlayerParty();
    ReducePlayerPartyToSelectedMon();
    ResetCaughtBug();
    SetBugCatchingContestFlag();
    ResetValoonReserveState();
    SetLastHealLocationWarp(HEAL_LOCATION_VALOON_TOWN_RANGERS_HQ);
    SelectContestants();
    SetContestantObjectEventSprites();
    gNumParkBalls = 20;
}

void ExitBugCatchingContestMode(void)
{
    LoadPlayerParty();
    ResetBugCatchingContestFlag();
    ResetValoonReserveState();
    gNumParkBalls = 0;
}

bool8 PlayerHasCaughtBug(void)
{
    // You cannot catch a Pokémon at 0HP, so we just set the HP to 0 if
    // nothing has been caught yet
    return gSaveBlock1Ptr->caughtBug.hp != 0;
}

void BugCatchingContestRetirePrompt(void)
{
    ScriptContext1_SetupScript(ValoonReserve_EventScript_RetirePrompt);
}

void CB2_EndBugCatchingContestBattle(void)
{
    if (gNumParkBalls == 0)
    {
        if (gBattleOutcome == B_OUTCOME_NO_PARK_BALLS)
            ScriptContext1_SetupScript(ValoonReserve_EventScript_OutOfBallsMidBattle);
        else if (gBattleOutcome == B_OUTCOME_CAUGHT)
            ScriptContext1_SetupScript(ValoonReserve_EventScript_OutOfBallsBeginJudging);
        
        ScriptContext1_Stop();
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
    else
    {
        SetMainCallback2(CB2_ReturnToField);
    }
}

void ResetCaughtBug(void)
{
    ZeroBoxMonData(&gSaveBlock1Ptr->caughtBug.mon);
    gSaveBlock1Ptr->caughtBug.hp = 0;
}

void SetCaughtBug(struct Pokemon *mon)
{
    SetMonData(mon, MON_DATA_OT_NAME, gSaveBlock2Ptr->playerName);
    SetMonData(mon, MON_DATA_OT_GENDER, &gSaveBlock2Ptr->playerGender);
    SetMonData(mon, MON_DATA_OT_ID, gSaveBlock2Ptr->playerTrainerId);

    gSaveBlock1Ptr->caughtBug.mon = mon->box;
    gSaveBlock1Ptr->caughtBug.hp = GetMonData(mon, MON_DATA_HP);
}

void ViewCaughtBug(void)
{
    ShowPokemonSummaryScreen(PSS_MODE_BUG_CATCHING_CONTEST, &gSaveBlock1Ptr->caughtBug.mon, 0, 0, CB2_ReturnToField);
}

void BufferCaughtBugSpecies(void)
{
    u8 nick[POKEMON_NAME_LENGTH];
    GetBoxMonData(&gSaveBlock1Ptr->caughtBug.mon, MON_DATA_NICKNAME, nick);
    StringCopy(gStringVar1, nick);
    VarSet(VAR_TEMP_1, GetBoxMonData(&gSaveBlock1Ptr->caughtBug.mon, MON_DATA_SPECIES, NULL));
}

u8 GiveAndResetCaughtBug(void)
{
    u8 sentToPc;
    struct Pokemon mon;
    
    BoxMonToMon(&gSaveBlock1Ptr->caughtBug.mon, &mon);
    sentToPc = GiveMonToPlayer(&mon);
    
    ResetCaughtBug();
    
    return sentToPc;
}

void ResetContestants(void)
{
    u8 i;
    for (i = 0; i < CONTESTANT_COUNT; i++)
    {
        sContestants[i].contestantId = 0;
        sContestants[i].pkmnId = 0;
        sContestants[i].score = 0;
    }
}

void SelectContestants(void)
{
    u8 i, j, contestantId;
    
    ResetContestants();
    
    for (j = 0; j < CONTESTANT_COUNT; j++)
    {
        if (j == 0 && !FlagGet(FLAG_UNLOCK_VALOON_GYM_DOOR))
            sContestants[j].contestantId = BUG_CATCHING_CONTEST_TRAINER_VERNON;
        else
        {
            do
            {
                contestantId = Random() % NUM_BUG_CATCHING_CONTEST_TRAINERS;
                for (i = 0; i < j; i++)
                {
                    if (sContestants[i].contestantId == contestantId)
                        break;
                }
            } while (i != j);
            sContestants[i].contestantId = contestantId;
        }
    }
}

void SetContestantObjectEventSprites(void)
{
    u8 i;
    for (i = 0; i < CONTESTANT_COUNT; i++)
        VarSet(VAR_OBJ_GFX_ID_0 + i, sBugCatchingContestTrainers[sContestants[i].contestantId].sprite);
}

static u8 GetMinLevel(u16 species)
{
    u16 headerId;
    u8 minLevel = MAX_LEVEL;
    const struct WildPokemonInfo *landMonsInfo;
    const struct WildPokemonInfo *waterMonsInfo;
    u8 i;
    
    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == 0xFFFF)
        return MAX_LEVEL;
    
    landMonsInfo = gWildMonHeaders[headerId].landMonsInfo;
    for (i = 0; i < NUM_LAND_MON_SLOTS; i++)
    {
        if (landMonsInfo->wildPokemon[i].species == species)
        {
            if (landMonsInfo->wildPokemon[i].minLevel < minLevel)
            {
                minLevel = landMonsInfo->wildPokemon[i].minLevel;
            }
        }
    }
    
    waterMonsInfo = gWildMonHeaders[headerId].waterMonsInfo;
    for (i = 0; i < NUM_WATER_MON_SLOTS; i++)
    {
        if (landMonsInfo->wildPokemon[i].species == species)
        {
            if (landMonsInfo->wildPokemon[i].minLevel < minLevel)
            {
                minLevel = landMonsInfo->wildPokemon[i].minLevel;
            }
        }
    }
    
    return minLevel;
}

static u8 GetMaxLevel(u16 species)
{
    u16 headerId;
    u8 maxLevel = MIN_LEVEL;
    const struct WildPokemonInfo *landMonsInfo;
    const struct WildPokemonInfo *waterMonsInfo;
    u8 i;
    
    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == 0xFFFF)
        return MIN_LEVEL;
    
    landMonsInfo = gWildMonHeaders[headerId].landMonsInfo;
    for (i = 0; i < NUM_LAND_MON_SLOTS; i++)
    {
        if (landMonsInfo->wildPokemon[i].species == species)
        {
            if (landMonsInfo->wildPokemon[i].maxLevel > maxLevel)
            {
                maxLevel = landMonsInfo->wildPokemon[i].maxLevel;
            }
        }
    }
    
    waterMonsInfo = gWildMonHeaders[headerId].waterMonsInfo;
    for (i = 0; i < NUM_WATER_MON_SLOTS; i++)
    {
        if (landMonsInfo->wildPokemon[i].species == species)
        {
            if (landMonsInfo->wildPokemon[i].maxLevel > maxLevel)
            {
                maxLevel = landMonsInfo->wildPokemon[i].maxLevel;
            }
        }
    }
    
    return maxLevel;
}

static u16 GetLevelScore()
{
    u16 score;
    struct BoxPokemon *mon = &gSaveBlock1Ptr->caughtBug.mon;
    u16 species = GetBoxMonData(mon, MON_DATA_SPECIES);
    u8 level = GetLevelFromBoxMonExp(mon);
    u8 minLevel, maxLevel;
    
    minLevel = GetMinLevel(species);
    maxLevel = GetMaxLevel(species);
    
    if (minLevel > maxLevel || minLevel < MIN_LEVEL || maxLevel > MAX_LEVEL)
        return 0;
    
    score = ((level - minLevel) * 100) / (maxLevel - minLevel);
    
    if (score > 100)
        return 100;
    
    if (score < 1)
        return 0;
    
    return score;
}

static u16 GetIVScore()
{
    u16 score;
    struct BoxPokemon *mon = &gSaveBlock1Ptr->caughtBug.mon;
    u8 ivTotal = 0;
    u8 i;
    
    for (i = 0; i < NUM_STATS; i++)
    {
        ivTotal += GetBoxMonData(mon, MON_DATA_HP_IV + i);
    }
    
    score = (ivTotal * 100) / MAX_IVS_TOTAL;
    
    if (score > 100)
        return 100;
    
    if (score < 1)
        return 0;
    
    return score;
}

static u16 GetHPScore()
{
    u16 score;
    u16 maxHP, curHP;
    struct Pokemon pokemon;
    
    BoxMonToMon(&gSaveBlock1Ptr->caughtBug.mon, &pokemon);
    maxHP = GetMonData(&pokemon, MON_DATA_MAX_HP);
    curHP = gSaveBlock1Ptr->caughtBug.hp;
    
    score = (curHP * 100) / maxHP;
    
    if (score > 100)
        return 100;
    
    if (score < 1)
        return 0;
    
    return score;
}

static bool8 IsSpeciesCommon(u16 species)
{
    u8 i;
    for (i = 0; i < NUM_COMMON_SPECIES; i++)
        if (sCommonSpecies[i] == species)
            return TRUE;
    
    return FALSE;
}

static bool8 IsSpeciesRare(u16 species)
{
    u8 i;
    for (i = 0; i < NUM_RARE_SPECIES; i++)
        if (sRareSpecies[i] == species)
            return TRUE;
    
    return FALSE;
}

static u16 GetRarityScore()
{
    u16 score;
    struct BoxPokemon *mon = &gSaveBlock1Ptr->caughtBug.mon;
    u16 species = GetBoxMonData(mon, MON_DATA_SPECIES);
    
    if (IsSpeciesCommon(species))
        score = 60;
    else if (IsSpeciesRare(species))
        score = 100;
    else
        score = 80;
    
    return score;
}

static u16 GetShinyScore()
{
    u16 score = 0;
    struct BoxPokemon *mon = &gSaveBlock1Ptr->caughtBug.mon;
    
    if (IsBoxMonShiny(mon))
        score = 100;
    
    return score;
}

static u16 CalculatePlayerScore(void)
{
    // + The Pokémon's level relative to the max level for its species in the map, as a percentage
    // + The Pokémon's IVs relative to the max (186), as a percentage
    // + The Pokémon's HP relative to its max, as a percentage
    // + The Pokémon's rarity factor: 60, 80 or 100
    // + 100 if the Pokémon is shiny
    u16 score = 0;
    score += GetLevelScore();
    score += GetIVScore();
    score += GetHPScore();
    score += GetRarityScore();
    score += GetShinyScore();
    return score;
}

void GenerateContestantScores(void)
{
    u8 i;
    
    for (i = 0; i < CONTESTANT_COUNT; i++)
    {
        sContestants[i].pkmnId = Random() % 3;
        sContestants[i].score = sBugCatchingContestTrainers[sContestants[i].contestantId].pokemon[sContestants[i].pkmnId].score + Random() % 8;
    }
}

int CompareBugCatchingContestantScores(const void *a, const void *b)
{
    struct BugCatchingContestant *a1 = (struct BugCatchingContestant *)a;
    struct BugCatchingContestant *b1 = (struct BugCatchingContestant *)b;
    return (a1->score <= b1->score);
}

void SelectBugCatchingContestWinners(void)
{
    // Generate the 4 NPC contestants' scores
    GenerateContestantScores();
    
    // Add the player's score to the end of the array
    sContestants[CONTESTANT_COUNT].contestantId = BUG_CATCHING_CONTEST_PLAYER;
    sContestants[CONTESTANT_COUNT].score = CalculatePlayerScore();
    
    // Sort the array s.t. element 0 is the contestant in 1st place, element 1 is 2nd place, etc.
    MergeSort(sContestants, CONTESTANT_COUNT + 1, sizeof(struct BugCatchingContestant), CompareBugCatchingContestantScores);
}

void BufferBugCatchingContestStrings(void)
{
    u16 contestantId = sContestants[gSpecialVar_Result].contestantId;
    if (contestantId == BUG_CATCHING_CONTEST_PLAYER)
    {
        u8 nick[POKEMON_NAME_LENGTH];
        
        StringCopy(gStringVar1, gTrainerClassNames[TRAINER_CLASS_PKMN_TRAINER]);
        StringCopy(gStringVar2, gSaveBlock2Ptr->playerName);
        GetBoxMonData(&gSaveBlock1Ptr->caughtBug.mon, MON_DATA_NICKNAME, nick);
        StringCopy(gStringVar3, nick);
    }
    else
    {
        u8 pkmnID = sContestants[gSpecialVar_Result].pkmnId;
        
        StringCopy(gStringVar1, gTrainerClassNames[sBugCatchingContestTrainers[contestantId].trainerClass]);
        StringCopy(gStringVar2, sBugCatchingContestTrainers[contestantId].name);
        StringCopy(gStringVar3, gSpeciesNames[sBugCatchingContestTrainers[contestantId].pokemon[pkmnID].species]);
    }
}

void BufferBugCatchingContestScore(void)
{
    u16 score = sContestants[gSpecialVar_Result].score;
    ConvertIntToDecimalStringN(gStringVar1, score, STR_CONV_MODE_LEFT_ALIGN, CountDigits(score));
}

bool8 IsVernonCompetingInBugCatchingContest(void)
{
    u8 i;
    for (i = 0; i < CONTESTANT_COUNT + 1; i++)
        if (sContestants[i].contestantId == BUG_CATCHING_CONTEST_TRAINER_VERNON)
            return TRUE;

    return FALSE;
}

bool8 IsntGivingPlayerSecondMegaStone(u8 i)
{
    return (!FlagGet(sMegaStonePrizes[i].flag) || sContestants[0].contestantId != BUG_CATCHING_CONTEST_PLAYER);
}

u16 GetMegaStonePrizeFromSpecies(u16 species)
{
    u16 prize = ITEM_NONE;
    u8 i;
    for (i = 0; i < NUM_MEGA_STONE_PRIZES; i++)
        if (sMegaStonePrizes[i].species == species && IsntGivingPlayerSecondMegaStone(i))
            prize = sMegaStonePrizes[i].item;
    
    return prize;
}

u16 GetRandomPrize(void)
{
    return sBugCatchingContestPrizes[Random() % NUM_BUG_CATCHING_CONTEST_PRIZES];
}

u16 GiveFirstPlaceBugCatchingContestPrize(void)
{
    u16 contestantId = sContestants[0].contestantId;
    u8 pkmnID = sContestants[0].pkmnId;
    
    u16 prize = GetMegaStonePrizeFromSpecies(sBugCatchingContestTrainers[contestantId].pokemon[pkmnID].species);
    if (prize == ITEM_NONE)
        prize = GetRandomPrize();
    
    return prize;
}

u16 GetPlayersBugCatchingContestPrize(void)
{
    // Assume the first place prize is still stored in gSpecialVar_0x8004
    if (sContestants[0].contestantId == BUG_CATCHING_CONTEST_PLAYER)
        return gSpecialVar_0x8004;
    else if (sContestants[1].contestantId == BUG_CATCHING_CONTEST_PLAYER)
        return ITEM_EVERSTONE;
    else if (sContestants[2].contestantId == BUG_CATCHING_CONTEST_PLAYER)
        return ITEM_SITRUS_BERRY;
    
    return ITEM_SHED_SHELL;
}

void SetMegaStonePrizeFlag(u16 itemId)
{
    u8 i;
    for (i = 0; i < NUM_MEGA_STONE_PRIZES; i++)
        if (sMegaStonePrizes[i].item == itemId)
            FlagSet(sMegaStonePrizes[i].flag);
}

void TrySetMegaStonePrizeFlag(void)
{
    // Assume the first place prize is still stored in gSpecialVar_0x8004
    if (sContestants[0].contestantId == BUG_CATCHING_CONTEST_PLAYER)
        SetMegaStonePrizeFlag(gSpecialVar_0x8004);
}

void TrySetVernonBeedrilliteFlag(void)
{
    if (sContestants[0].contestantId == BUG_CATCHING_CONTEST_TRAINER_VERNON)
        FlagSet(FLAG_VERNON_WON_BEEDRILLITE);
}
