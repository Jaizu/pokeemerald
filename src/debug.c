#if DEBUG

#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "list_menu.h"
#include "main.h"
#include "map_name_popup.h"
#include "menu.h"
#include "region_map.h"
#include "save_location.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "sound.h"
#include "strings.h"
#include "task.h"
#include "constants/songs.h"
#include "constants/event_objects.h"
#include "constants/event_object_movement.h"

// Constants
#define DEBUG_MAIN_MENU_WIDTH 7
#define DEBUG_UTILITY_MENU_WIDTH 12
#define DEBUG_TOGGLES_MENU_WIDTH 9

// Funtions
void Debug_OpenDebugMenu(void);
static void Debug_ShowMainMenu(void (*HandleInput)(u8), struct ListMenuTemplate ListMenuTemplate);
static void Debug_ShowTogglesSubMenu(void (*HandleInput)(u8), struct ListMenuTemplate ListMenuTemplate);
static void Debug_ShowUtilitySubMenu(void (*HandleInput)(u8), struct ListMenuTemplate ListMenuTemplate);
static void Debug_DestroyMenu(u8);

static void DebugTask_HandleMenuInput_Main(u8);
static void DebugTask_HandleMenuInput_Utility(u8);
static void DebugTask_HandleMenuInput_Toggles(u8);

// Main Menu Functions
static void DebugAction_OpenMenu_Utility(u8);
static void DebugAction_OpenMenu_Toggles(u8);
static void DebugAction_Cancel(u8);

// Utility Menu Functions
static void DebugAction_HealParty(u8);
static void DebugAction_ResetMapFlags(u8);
static void DebugAction_Fly(u8);

// Toggles Menu Funtions
static void DebugAction_ToggleTrainers(u8);
static void DebugAction_ToggleEncounters(u8);
static void DebugAction_TogglePokedex(u8);
static void DebugAction_ToggleBadges(u8);

// Enums
enum {
    DEBUG_MENU_ITEM_UTILITY,
    DEBUG_MENU_ITEM_TOGGLES,
    DEBUG_MENU_ITEM_CANCEL,
};

enum {
    DEBUG_MENU_ITEM_HEAL_PARTY,
    DEBUG_MENU_ITEM_RESET_MAP_FLAGS,
    DEBUG_MENU_ITEM_FLY,
};

enum {
    DEBUG_MENU_ITEM_TOGGLE_TRAINERS,
    DEBUG_MENU_ITEM_TOGGLE_ENCOUNTER,
    DEBUG_MENU_ITEM_TOGGLE_POKEDEX,
    DEBUG_MENU_ITEM_TOGGLE_BADGES,
};

// Text
static const u8 gDebugText_Utility[] = _("UTILITY");
static const u8 gDebugText_Toggles[] = _("TOGGLES");
static const u8 gDebugText_Cancel[] = _("CANCEL");

static const u8 gDebugText_HealParty[] = _("HEAL PARTY");
static const u8 gDebugText_ResetAllMapFlags[] = _("RESET MAP FLAGS");
static const u8 gDebugText_Fly[] = _("FLY");

static const u8 gDebugText_Toggles_Trainers[] = _("TRAINERS");
static const u8 gDebugText_Toggles_Encounters[] = _("ENCOUNTERS");
static const u8 gDebugText_Toggles_Pokedex[] = _("POKEDEX");
static const u8 gDebugText_Toggles_Badges[] = _("BADGES");

// Scripts
extern const u8 EventScript_ResetAllMapFlags[];

// List Menu Items
static const struct ListMenuItem sDebugMenuItems_Main[] =
{
    [DEBUG_MENU_ITEM_UTILITY] = {gDebugText_Utility, DEBUG_MENU_ITEM_UTILITY},
    [DEBUG_MENU_ITEM_TOGGLES] = {gDebugText_Toggles, DEBUG_MENU_ITEM_TOGGLES},
    [DEBUG_MENU_ITEM_CANCEL] = {gDebugText_Cancel, DEBUG_MENU_ITEM_CANCEL},
};

static const struct ListMenuItem sDebugMenuItems_Utility[] =
{
    [DEBUG_MENU_ITEM_HEAL_PARTY] = {gDebugText_HealParty, DEBUG_MENU_ITEM_HEAL_PARTY},
    [DEBUG_MENU_ITEM_RESET_MAP_FLAGS] = {gDebugText_ResetAllMapFlags, DEBUG_MENU_ITEM_RESET_MAP_FLAGS},
    [DEBUG_MENU_ITEM_FLY] = {gDebugText_Fly, DEBUG_MENU_ITEM_FLY},
};

static const struct ListMenuItem sDebugMenuItems_Toggles[] = 
{
    [DEBUG_MENU_ITEM_TOGGLE_TRAINERS] = {gDebugText_Toggles_Trainers, DEBUG_MENU_ITEM_TOGGLE_TRAINERS},
    [DEBUG_MENU_ITEM_TOGGLE_ENCOUNTER] = {gDebugText_Toggles_Encounters, DEBUG_MENU_ITEM_TOGGLE_ENCOUNTER},
    [DEBUG_MENU_ITEM_TOGGLE_POKEDEX] = {gDebugText_Toggles_Pokedex, DEBUG_MENU_ITEM_TOGGLE_POKEDEX},
    [DEBUG_MENU_ITEM_TOGGLE_BADGES] = {gDebugText_Toggles_Badges, DEBUG_MENU_ITEM_TOGGLE_BADGES},
};

// List Menu Actions
static void (*const sDebugMenuActions_Main[])(u8) =
{
    [DEBUG_MENU_ITEM_UTILITY] = DebugAction_OpenMenu_Utility,
    [DEBUG_MENU_ITEM_TOGGLES] = DebugAction_OpenMenu_Toggles,
    [DEBUG_MENU_ITEM_CANCEL] = DebugAction_Cancel,
};

static void (*const sDebugMenuActions_Utility[])(u8) =
{
    [DEBUG_MENU_ITEM_HEAL_PARTY] = DebugAction_HealParty,
    [DEBUG_MENU_ITEM_RESET_MAP_FLAGS] = DebugAction_ResetMapFlags,
    [DEBUG_MENU_ITEM_FLY] = DebugAction_Fly,
};

static void (*const sDebugMenuActions_Toggles[])(u8) =
{
    [DEBUG_MENU_ITEM_TOGGLE_TRAINERS] = DebugAction_ToggleTrainers,
    [DEBUG_MENU_ITEM_TOGGLE_ENCOUNTER] = DebugAction_ToggleEncounters,
    [DEBUG_MENU_ITEM_TOGGLE_POKEDEX] = DebugAction_TogglePokedex,
    [DEBUG_MENU_ITEM_TOGGLE_BADGES] = DebugAction_ToggleBadges,
};

// Windows
static const struct WindowTemplate sDebugMainMenuWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = DEBUG_MAIN_MENU_WIDTH,
    .height = 2 * ARRAY_COUNT(sDebugMenuItems_Main),
    .paletteNum = 15,
    .baseBlock = 1,
};

static const struct WindowTemplate sDebugSubMenuUtilityWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = DEBUG_UTILITY_MENU_WIDTH,
    .height = 2 * ARRAY_COUNT(sDebugMenuItems_Utility),
    .paletteNum = 15,
    .baseBlock = 1,
};

static const struct WindowTemplate sDebugSubMenuTogglesWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = DEBUG_TOGGLES_MENU_WIDTH,
    .height = 2 * ARRAY_COUNT(sDebugMenuItems_Toggles),
    .paletteNum = 15,
    .baseBlock = 1,
};

// List Menu Templates
static const struct ListMenuTemplate sDebugMenu_ListTemplate_Main =
{
    .items = sDebugMenuItems_Main,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenuItems_Main),
};


static const struct ListMenuTemplate sDebugMenu_ListTemplate_Utility = 
{
    .items = sDebugMenuItems_Utility,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenuItems_Utility),
};

static const struct ListMenuTemplate sDebugMenu_ListTemplate_Toggles = 
{
    .items = sDebugMenuItems_Toggles,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenuItems_Toggles),
};

// Funtions Universal
void Debug_OpenDebugMenu()
{
    Debug_ShowMainMenu(DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
}

static void Debug_ShowMainMenu(void (*HandleInput)(u8), struct ListMenuTemplate ListMenuTemplate)
{
    struct ListMenuTemplate menuTemplate;
    u8 windowId;
    u8 menuTaskId;
    u8 inputTaskId;

    // create window
    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMainMenuWindowTemplate);
    DrawStdWindowFrame(windowId, FALSE);

    // create list menu
    menuTemplate = ListMenuTemplate;
    menuTemplate.maxShowed = ARRAY_COUNT(sDebugMenuItems_Main);
    menuTemplate.windowId = windowId;
    menuTemplate.header_X = 0;
    menuTemplate.item_X = 8;
    menuTemplate.cursor_X = 0;
    menuTemplate.upText_Y = 1;
    menuTemplate.cursorPal = 2;
    menuTemplate.fillValue = 1;
    menuTemplate.cursorShadowPal = 3;
    menuTemplate.lettersSpacing = 1;
    menuTemplate.itemVerticalPadding = 1;
    menuTemplate.scrollMultiple = LIST_NO_MULTIPLE_SCROLL;
    menuTemplate.fontId = 1;
    menuTemplate.cursorKind = 0;
    menuTaskId = ListMenuInit(&menuTemplate, 0, 0);

    // draw everything
    CopyWindowToVram(windowId, 3);

    // create input handler task
    inputTaskId = CreateTask(HandleInput, 3);
    gTasks[inputTaskId].data[0] = menuTaskId;
    gTasks[inputTaskId].data[1] = windowId;
}

static void Debug_ShowUtilitySubMenu(void (*HandleInput)(u8), struct ListMenuTemplate ListMenuTemplate)
{
    struct ListMenuTemplate menuTemplate;
    u8 windowId;
    u8 menuTaskId;
    u8 inputTaskId;

    // create window
    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugSubMenuUtilityWindowTemplate);
    DrawStdWindowFrame(windowId, FALSE);

    // create list menu
    menuTemplate = ListMenuTemplate;
    menuTemplate.maxShowed = ARRAY_COUNT(sDebugMenuItems_Utility);
    menuTemplate.windowId = windowId;
    menuTemplate.header_X = 0;
    menuTemplate.item_X = 8;
    menuTemplate.cursor_X = 0;
    menuTemplate.upText_Y = 1;
    menuTemplate.cursorPal = 2;
    menuTemplate.fillValue = 1;
    menuTemplate.cursorShadowPal = 3;
    menuTemplate.lettersSpacing = 1;
    menuTemplate.itemVerticalPadding = 0;
    menuTemplate.scrollMultiple = LIST_NO_MULTIPLE_SCROLL;
    menuTemplate.fontId = 1;
    menuTemplate.cursorKind = 0;
    menuTaskId = ListMenuInit(&menuTemplate, 0, 0);

    // draw everything
    CopyWindowToVram(windowId, 3);

    // create input handler task
    inputTaskId = CreateTask(HandleInput, 3);
    gTasks[inputTaskId].data[0] = menuTaskId;
    gTasks[inputTaskId].data[1] = windowId;
}

static void Debug_ShowTogglesSubMenu(void (*HandleInput)(u8), struct ListMenuTemplate ListMenuTemplate)
{
    struct ListMenuTemplate menuTemplate;
    u8 windowId;
    u8 menuTaskId;
    u8 inputTaskId;

    // create window
    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugSubMenuTogglesWindowTemplate);
    DrawStdWindowFrame(windowId, FALSE);

    // create list menu
    menuTemplate = ListMenuTemplate;
    menuTemplate.maxShowed = ARRAY_COUNT(sDebugMenuItems_Toggles);
    menuTemplate.windowId = windowId;
    menuTemplate.header_X = 0;
    menuTemplate.item_X = 8;
    menuTemplate.cursor_X = 0;
    menuTemplate.upText_Y = 1;
    menuTemplate.cursorPal = 2;
    menuTemplate.fillValue = 1;
    menuTemplate.cursorShadowPal = 3;
    menuTemplate.lettersSpacing = 1;
    menuTemplate.itemVerticalPadding = 0;
    menuTemplate.scrollMultiple = LIST_NO_MULTIPLE_SCROLL;
    menuTemplate.fontId = 1;
    menuTemplate.cursorKind = 0;
    menuTaskId = ListMenuInit(&menuTemplate, 0, 0);

    // draw everything
    CopyWindowToVram(windowId, 3);

    // create input handler task
    inputTaskId = CreateTask(HandleInput, 3);
    gTasks[inputTaskId].data[0] = menuTaskId;
    gTasks[inputTaskId].data[1] = windowId;
}

static void Debug_DestroyMenu(u8 taskId)
{
    DestroyListMenuTask(gTasks[taskId].data[0], NULL, NULL);
    ClearStdWindowAndFrame(gTasks[taskId].data[1], TRUE);
    RemoveWindow(gTasks[taskId].data[1]);
    DestroyTask(taskId);
}

// Funtions Handle Input
static void DebugTask_HandleMenuInput_Main(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].data[0]);

    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        if ((func = sDebugMenuActions_Main[input]) != NULL)
            func(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu(taskId);
        EnableBothScriptContexts();
    }
}

static void DebugTask_HandleMenuInput_Utility(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].data[0]);

    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        if ((func = sDebugMenuActions_Utility[input]) != NULL)
            func(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu(taskId);
        Debug_ShowMainMenu(DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
    }
}

static void DebugTask_HandleMenuInput_Toggles(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].data[0]);

    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        if ((func = sDebugMenuActions_Toggles[input]) != NULL)
            func(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu(taskId);
        Debug_ShowMainMenu(DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
    }
}

// Funtions Menus
static void DebugAction_OpenMenu_Utility(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowUtilitySubMenu(DebugTask_HandleMenuInput_Utility, sDebugMenu_ListTemplate_Utility);
}

static void DebugAction_OpenMenu_Toggles(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowTogglesSubMenu(DebugTask_HandleMenuInput_Toggles, sDebugMenu_ListTemplate_Toggles);
}

static void DebugAction_Cancel(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    EnableBothScriptContexts();
}

// Behaviour Funtions
// Utility
static void DebugAction_HealParty(u8 taskId)
{
    HealPlayerParty();
    PlaySE(SE_USE_ITEM);
}

static void DebugAction_ResetMapFlags(u8 taskId)
{
    ScriptContext2_RunNewScript(EventScript_ResetAllMapFlags);
    PlaySE(SE_USE_ITEM);
}

static void DebugAction_Fly(u8 taskId)
{
    FlagSet(FLAG_VISITED_SUNSET_TOWN);
    FlagSet(FLAG_VISITED_CEDARRED_TOWN);
    FlagSet(FLAG_VISITED_FIRWEALD_CITY);
    FlagSet(FLAG_VISITED_LAVARIDGE_TOWN);
    FlagSet(FLAG_VISITED_FALLARBOR_TOWN);
    FlagSet(FLAG_VISITED_VERDANTURF_TOWN);
    FlagSet(FLAG_VISITED_PACIFIDLOG_TOWN);
    FlagSet(FLAG_VISITED_PETALBURG_CITY);
    FlagSet(FLAG_VISITED_SLATEPORT_CITY);
    FlagSet(FLAG_VISITED_MAUVILLE_CITY);
    FlagSet(FLAG_VISITED_RUSTBORO_CITY);
    FlagSet(FLAG_VISITED_FORTREE_CITY);
    FlagSet(FLAG_VISITED_LILYCOVE_CITY);
    FlagSet(FLAG_VISITED_MOSSDEEP_CITY);
    FlagSet(FLAG_VISITED_SOOTOPOLIS_CITY);
    FlagSet(FLAG_VISITED_EVER_GRANDE_CITY);
    FlagSet(FLAG_LANDMARK_POKEMON_LEAGUE);
    FlagSet(FLAG_LANDMARK_BATTLE_FRONTIER);
    Debug_DestroyMenu(taskId);
    SetMainCallback2(CB2_OpenFlyMap);
}

// Toggles
static void DebugAction_ToggleTrainers(u8 taskId)
{
    if (FlagGet(FLAG_DISABLE_TRAINERS))
        PlaySE(SE_PC_LOGIN);
    else
        PlaySE(SE_PC_OFF);
    FlagToggle(FLAG_DISABLE_TRAINERS);
}

static void DebugAction_ToggleEncounters(u8 taskId)
{
    if (FlagGet(FLAG_DISABLE_ENCOUNTERS))
        PlaySE(SE_PC_LOGIN);
    else
        PlaySE(SE_PC_OFF);
    FlagToggle(FLAG_DISABLE_ENCOUNTERS);
}

static void DebugAction_TogglePokedex(u8 taskId)
{
    if (FlagGet(FLAG_SYS_POKEDEX_GET))
    {
        DisableNationalPokedex();
        PlaySE(SE_PC_OFF);
    }
    else
    {
        EnableNationalPokedex();
        SetUnlockedPokedexFlags();
        PlaySE(SE_PC_LOGIN);
    }  
    FlagToggle(FLAG_SYS_POKEDEX_GET);
}

static void DebugAction_ToggleBadges(u8 taskId)
{
    if(FlagGet(FLAG_BADGE08_GET))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_BADGE01_GET);
    FlagToggle(FLAG_BADGE02_GET);
    FlagToggle(FLAG_BADGE03_GET);
    FlagToggle(FLAG_BADGE04_GET);
    FlagToggle(FLAG_BADGE05_GET);
    FlagToggle(FLAG_BADGE06_GET);
    FlagToggle(FLAG_BADGE07_GET);
    FlagToggle(FLAG_BADGE08_GET);
}

#endif