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
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "tv.h"
#include "constants/event_objects.h"
#include "constants/heal_locations.h"
#include "constants/layouts.h"
#include "constants/trainers.h"
#include "data/bug_catching_contest.h"

extern const u8 ValoonReserve_EventScript_RetirePrompt[];
extern const u8 ValoonReserve_EventScript_OutOfBallsMidBattle[];
extern const u8 ValoonReserve_EventScript_OutOfBallsBeginJudging[];

EWRAM_DATA u8 gNumParkBalls = 0;
EWRAM_DATA static u8 sBugCatchingContestants[CONTESTANTS_COUNT] = {0, 0, 0, 0};
EWRAM_DATA static u8 sBugCatchingFinalists[3] = {0, 0, 0};

void ResetCaughtBug(void);
void ResetContestants(void);
void SelectContestants(void);

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
    GetMonData(&gSaveBlock1Ptr->caughtBug.mon, MON_DATA_NICKNAME, nick);
    StringCopy(gStringVar1, nick);
    VarSet(VAR_TEMP_1, GetMonData(&gSaveBlock1Ptr->caughtBug.mon, MON_DATA_SPECIES, NULL));
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
    for (i = 0; i < CONTESTANTS_COUNT; i++)
    {
        sBugCatchingContestants[i] = 0;
    }
}

void SelectContestants(void)
{
    u8 i, j, contestantId;
    
    ResetContestants();
    
    for (j = 0; j < CONTESTANTS_COUNT; j++)
    {
        if (j == 0 && !FlagGet(FLAG_UNLOCK_VALOON_GYM_DOOR))
            sBugCatchingContestants[j] = BUG_CATCHING_CONTEST_TRAINER_VERNON;
        else
        {
            do
            {
                contestantId = Random() % NUM_BUG_CATCHING_CONTEST_TRAINERS;
                for (i = 0; i < j; i++)
                {
                    if (sBugCatchingContestants[i] == contestantId)
                        break;
                }
            } while (i != j);
            sBugCatchingContestants[i] = contestantId;
        }
    }
}

#define FIRST_PLACE  2
#define SECOND_PLACE 1
#define THIRD_PLACE  0

void SelectBugCatchingContestWinners(void)
{
    // Decide the scores for 3rd, 2nd and 1st place
    sBugCatchingFinalists[FIRST_PLACE]  = sBugCatchingContestants[2];
    sBugCatchingFinalists[SECOND_PLACE] = sBugCatchingContestants[1];
    sBugCatchingFinalists[THIRD_PLACE]  = sBugCatchingContestants[0];
    // Determine whether the player is a finalist
    // Select and store the contestants and their Pokémon
}

u16 GetContestantIdInPosition(u16 pos)
{
    return sBugCatchingFinalists[pos];
}

u8 GetPokemonIdForContestantInPosition(u16 pos)
{
    // If pos = 0, return the Pokémon ID for the contestant in 3rd place
    // If pos = 1, return the Pokémon ID for the contestant in 2nd place
    // Otherwise,  return the Pokémon ID for the contestant in 1st place
    return 0;
}

void BufferBugCatchingContestStrings(void)
{
    u16 id = GetContestantIdInPosition(gSpecialVar_Result);
    u8 pkmnID = GetPokemonIdForContestantInPosition(gSpecialVar_Result);
    
    // Buffer the contestant's Trainer Class
    StringCopy(gStringVar1, gTrainerClassNames[contestants[id].trainerClass]);
    // Buffer the contestant's name
    StringCopy(gStringVar2, contestants[id].name);
    // Buffer the species of the contestant's entry
    StringCopy(gStringVar3, gSpeciesNames[contestants[id].pokemon[pkmnID].species]);
}

void BufferBugCatchingContestScore(void)
{
    u16 id = GetContestantIdInPosition(gSpecialVar_Result);
    u8 pkmnID = GetPokemonIdForContestantInPosition(gSpecialVar_Result);
    
    u16 num = contestants[id].pokemon[pkmnID].score;
    u8 numDigits = CountDigits(num);

    ConvertIntToDecimalStringN(gStringVar1, num, STR_CONV_MODE_LEFT_ALIGN, numDigits);
}

bool8 IsVernonCompeting(void)
{
    return (sBugCatchingContestants[0] == BUG_CATCHING_CONTEST_TRAINER_VERNON);
}
