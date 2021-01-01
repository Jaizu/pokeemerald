#include "global.h"
#include "bug_catching_contest.h"
#include "event_data.h"
#include "fieldmap.h"
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

void EnterBugCatchingContestMode(void)
{
    SetBugCatchingContestFlag();
    SetLastHealLocationWarp(HEAL_LOCATION_VALOON_TOWN_RANGERS_HQ);
    gNumParkBalls = 20;
}

void ExitBugCatchingContestMode(void)
{
    ResetBugCatchingContestFlag();
    SetLastHealLocationWarp(HEAL_LOCATION_VALOON_TOWN);
    gNumParkBalls = 0;
}

bool8 PlayerHasCaughtBug(void)
{
    return FALSE;
}

void BugCatchingContestRetirePrompt(void)
{
    ScriptContext1_SetupScript(ValoonReserve_EventScript_RetirePrompt);
}
