#ifndef GUARD_DEBUG_H
#define GUARD_DEBUG_H
#if DEBUG

#define DEBUG_NUMBER_DIGITS_FLAGS 4
#define DEBUG_NUMBER_DIGITS_VARIABLES 5
#define TAG_CONFETTI 1001
#define BOB_OTID 23501

enum {
    DEBUG_MENUITEM_CREDITS,
    DEBUG_MENUITEM_GODMODE,
    DEBUG_MENUITEM_UTILITY,
    DEBUG_MENUITEM_PARTY,
    DEBUG_MENUITEM_CANCEL,
};

enum {
    DEBUG_MENUITEM_SAVEBLOCKS,
    DEBUG_MENUITEM_RESET_BERRIES,
    DEBUG_MENUITEM_RESTOCK_BAG,
    DEBUG_MENUITEM_MANAGE_FLAGS,
    DEBUG_MENUITEM_MANAGE_VARS,
    DEBUG_MENUITEM_WARP,
    DEBUG_MENUITEM_CHANGE_NAME,
    DEBUG_MENUITEM_CHANGE_GENDER,
    DEBUG_MENUITEM_PLAYER_INVISIBLE,
};

enum {
    DEBUG_MENUITEM_HEAL_PARTY,
    DEBUG_MENUITEM_SAVE_PARTY,
    DEBUG_MENUITEM_LOAD_PARTY,
    DEBUG_MENUITEM_GIVE_MONS,
};

void Debug_OpenDebugMenu(void);

#endif
#endif // GUARD_DEBUG_H