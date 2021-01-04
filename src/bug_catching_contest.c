#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "bug_catching_contest.h"
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
#include "script.h"
#include "string_util.h"
#include "task.h"
#include "constants/heal_locations.h"
#include "constants/layouts.h"

extern const u8 ValoonReserve_EventScript_RetirePrompt[];
extern const u8 ValoonReserve_EventScript_OutOfBallsMidBattle[];
extern const u8 ValoonReserve_EventScript_OutOfBallsBeginJudging[];

EWRAM_DATA u8 gNumParkBalls = 0;

void ResetCaughtBug(void);

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
