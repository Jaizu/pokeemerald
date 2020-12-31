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
#include "constants/layouts.h"

bool8 InValoonReserve(void)
{
    return gMapHeader.mapLayoutId == LAYOUT_VALOON_RESERVE;
}

bool8 PlayerHasCaughtBug(void)
{
    return FALSE;
}
