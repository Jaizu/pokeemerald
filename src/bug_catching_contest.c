#include "global.h"
#include "bug_catching_contest.h"
#include "event_data.h"
#include "fieldmap.h"
#include "field_screen_effect.h"
#include "save.h"
#include "battle.h"
#include "random.h"
#include "task.h"
#include "party_menu.h"
#include "malloc.h"
#include "palette.h"
#include "script.h"
#include "battle_setup.h"
#include "overworld.h"
#include "constants/layouts.h"
#include "constants/heal_locations.h"

extern const u8 ValoonReserve_EventScript_RetirePrompt[];
extern const u8 ValoonReserve_EventScript_OutOfBallsMidBattle[];
extern const u8 ValoonReserve_EventScript_OutOfBallsBeginJudging[];

EWRAM_DATA u8 gNumParkBalls = 0;

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

void EnterBugCatchingContestMode(void)
{
    SetBugCatchingContestFlag();
    ResetValoonReserveState();
    SetLastHealLocationWarp(HEAL_LOCATION_VALOON_TOWN_RANGERS_HQ);
    gNumParkBalls = 20;
}

void ExitBugCatchingContestMode(void)
{
    ResetBugCatchingContestFlag();
    ResetValoonReserveState();
    SetLastHealLocationWarp(HEAL_LOCATION_VALOON_TOWN);
    gNumParkBalls = 0;
}

bool8 PlayerHasCaughtBug(void)
{
    // TODO: Implement properly
    return CalculatePlayerPartyCount() > 1;
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
