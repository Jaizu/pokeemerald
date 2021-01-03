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
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "pokemon_summary_screen.h"
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

void EnterBugCatchingContestMode(void)
{
    SetBugCatchingContestFlag();
    ResetValoonReserveState();
    ResetCaughtBug();
    SetLastHealLocationWarp(HEAL_LOCATION_VALOON_TOWN_RANGERS_HQ);
    gNumParkBalls = 20;
}

void ExitBugCatchingContestMode(void)
{
    ResetBugCatchingContestFlag();
    ResetValoonReserveState();
    ResetCaughtBug();
    SetLastHealLocationWarp(HEAL_LOCATION_VALOON_TOWN);
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
