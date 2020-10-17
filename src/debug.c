#if DEBUG

#include "global.h"
#include "debug.h"
#include "field_screen_effect.h"
#include "list_menu.h"
#include "main.h"
#include "map_name_popup.h"
#include "menu.h"
#include "overworld.h"
#include "script.h"
#include "sound.h"
#include "strings.h"
#include "task.h"
#include "constants/maps.h"
#include "constants/songs.h"

#define DEBUG_MAIN_MENU_HEIGHT 7
#define DEBUG_MAIN_MENU_WIDTH 11

static void Debug_DestroyMainMenu(u8);
static void DebugAction_FastForward(u8);
static void DebugAction_GetParty(u8);
static void DebugAction_GetItems(u8);
static void DebugAction_Cancel(u8);
static void DebugTask_HandleMainMenuInput(u8);

extern const u8 Debug_EventScript_SetUpFastForward[];
extern const u8 Debug_EventScript_GetParty[];
extern const u8 Debug_EventScript_GetItems[];

enum {
    DEBUG_MENU_ITEM_FAST_FORWARD,
    DEBUG_MENU_ITEM_GET_PARTY,
    DEBUG_MENU_ITEM_GET_ITEMS,
    DEBUG_MENU_ITEM_CANCEL,
};

static const u8 gDebugText_FastForward[] = _("Fast forward");
static const u8 gDebugText_GetParty[] = _("Get party");
static const u8 gDebugText_GetItems[] = _("Get items");
static const u8 gDebugText_Cancel[] = _("Cancel");

static const struct ListMenuItem sDebugMenuItems[] =
{
    [DEBUG_MENU_ITEM_FAST_FORWARD] = {gDebugText_FastForward, DEBUG_MENU_ITEM_FAST_FORWARD},
    [DEBUG_MENU_ITEM_GET_PARTY] = {gDebugText_GetParty, DEBUG_MENU_ITEM_GET_PARTY},
    [DEBUG_MENU_ITEM_GET_ITEMS] = {gDebugText_GetItems, DEBUG_MENU_ITEM_GET_ITEMS},
    [DEBUG_MENU_ITEM_CANCEL] = {gDebugText_Cancel, DEBUG_MENU_ITEM_CANCEL}
};

static void (*const sDebugMenuActions[])(u8) =
{
    [DEBUG_MENU_ITEM_FAST_FORWARD] = DebugAction_FastForward,
    [DEBUG_MENU_ITEM_GET_PARTY] = DebugAction_GetParty,
    [DEBUG_MENU_ITEM_GET_ITEMS] = DebugAction_GetItems,
    [DEBUG_MENU_ITEM_CANCEL] = DebugAction_Cancel
};

static const struct WindowTemplate sDebugMenuWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = DEBUG_MAIN_MENU_WIDTH,
    .height = 2 * DEBUG_MAIN_MENU_HEIGHT,
    .paletteNum = 15,
    .baseBlock = 1,
};

static const struct ListMenuTemplate sDebugMenuListTemplate =
{
    .items = sDebugMenuItems,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenuItems),
    .maxShowed = DEBUG_MAIN_MENU_HEIGHT,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = 1,
    .cursorKind = 0
};

void Debug_ShowMainMenu(void) {
    struct ListMenuTemplate menuTemplate;
    u8 windowId;
    u8 menuTaskId;
    u8 inputTaskId;

    // create window
    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplate);
    DrawStdWindowFrame(windowId, FALSE);

    // create list menu
    menuTemplate = sDebugMenuListTemplate;
    menuTemplate.windowId = windowId;
    menuTaskId = ListMenuInit(&menuTemplate, 0, 0);

    // draw everything
    CopyWindowToVram(windowId, 3);

    // create input handler task
    inputTaskId = CreateTask(DebugTask_HandleMainMenuInput, 3);
    gTasks[inputTaskId].data[0] = menuTaskId;
    gTasks[inputTaskId].data[1] = windowId;
}

static void Debug_DestroyMainMenu(u8 taskId)
{
    DestroyListMenuTask(gTasks[taskId].data[0], NULL, NULL);
    ClearStdWindowAndFrame(gTasks[taskId].data[1], TRUE);
    RemoveWindow(gTasks[taskId].data[1]);
    DestroyTask(taskId);
    EnableBothScriptContexts();
}

static void DebugTask_HandleMainMenuInput(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].data[0]);

    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        if ((func = sDebugMenuActions[input]) != NULL)
            func(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMainMenu(taskId);
    }
}

static void DebugAction_FastForward(u8 taskId)
{
    Debug_DestroyMainMenu(taskId);
    ScriptContext2_RunNewScript(Debug_EventScript_SetUpFastForward);
    SetWarpDestination(MAP_GROUP(IGNIS_ROOST), MAP_NUM(IGNIS_ROOST), 3, 0, 0);
    DoWarp();
}

static void DebugAction_GetParty(u8 taskId)
{
    Debug_DestroyMainMenu(taskId);
    ScriptContext2_RunNewScript(Debug_EventScript_GetParty);
}

static void DebugAction_GetItems(u8 taskId)
{
    Debug_DestroyMainMenu(taskId);
    ScriptContext2_RunNewScript(Debug_EventScript_GetItems);
}

static void DebugAction_Cancel(u8 taskId)
{
    Debug_DestroyMainMenu(taskId);
}

#endif