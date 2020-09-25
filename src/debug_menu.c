#if DEBUG

#include "global.h"
#include "event_data.h"
#include "item.h"
#include "list_menu.h"
#include "main.h"
#include "map_name_popup.h"
#include "menu.h"
#include "money.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "sound.h"
#include "strings.h"
#include "task.h"
#include "wild_encounter.h"
#include "constants/items.h"
#include "constants/songs.h"
#include "constants/species.h"

#define DEBUG_MAIN_MENU_HEIGHT 7
#define DEBUG_MAIN_MENU_WIDTH 11

void Debug_ShowMainMenu(void);
static void Debug_DestroyMainMenu(u8);
static void DebugAction_GivePokemon(u8);
static void DebugAction_GiveItem(u8);
static void DebugAction_GiveMoney(u8);
static void DebugAction_GiveBadge(u8);
static void DebugAction_ToggleCollision(u8);
static void DebugAction_Warp(u8);
static void DebugAction_Cancel(u8);
static void DebugTask_HandleMainMenuInput(u8);


// List of Debug options
enum {
    DEBUG_MENU_ITEM_GIVE_POKEMON,
    DEBUG_MENU_ITEM_GIVE_ITEM,
    DEBUG_MENU_ITEM_GIVE_MONEY,
    DEBUG_MENU_ITEM_GIVE_BADGE,
    DEBUG_MENU_ITEM_TOGGLE_COLLISION,
    DEBUG_MENU_ITEM_WARP,
    DEBUG_MENU_ITEM_CANCEL,
};

// Labels for each debug option
static const u8 gDebugText_Give_Pokemon[] = _("Give Pokémon");
static const u8 gDebugText_Give_Item[] = _("Give Item");
static const u8 gDebugText_Give_Money[] = _("Give Money");
static const u8 gDebugText_Give_Badge[] = _("Give Badge");
static const u8 gDebugText_Toggle_Collision[] = _("Collision");
static const u8 gDebugText_Warp[] = _("Warp");
static const u8 gDebugText_Cancel[] = _("Cancel");

// Ties the name and enum ID together
static const struct ListMenuItem sDebugMenuItems[] =
{
    [DEBUG_MENU_ITEM_GIVE_POKEMON] = {gDebugText_Give_Pokemon, DEBUG_MENU_ITEM_GIVE_POKEMON},
    [DEBUG_MENU_ITEM_GIVE_ITEM] = {gDebugText_Give_Item, DEBUG_MENU_ITEM_GIVE_ITEM},
    [DEBUG_MENU_ITEM_GIVE_MONEY] = {gDebugText_Give_Money, DEBUG_MENU_ITEM_GIVE_MONEY},
    [DEBUG_MENU_ITEM_GIVE_BADGE] = {gDebugText_Give_Badge, DEBUG_MENU_ITEM_GIVE_BADGE},
    [DEBUG_MENU_ITEM_TOGGLE_COLLISION] = {gDebugText_Toggle_Collision, DEBUG_MENU_ITEM_TOGGLE_COLLISION},
    [DEBUG_MENU_ITEM_WARP] = {gDebugText_Warp, DEBUG_MENU_ITEM_WARP},
    [DEBUG_MENU_ITEM_CANCEL] = {gDebugText_Cancel, DEBUG_MENU_ITEM_CANCEL}
};

// List of functions to execute when the option is selected
static void (*const sDebugMenuActions[])(u8) =
{
    [DEBUG_MENU_ITEM_GIVE_POKEMON] = DebugAction_GivePokemon,
    [DEBUG_MENU_ITEM_GIVE_ITEM] = DebugAction_GiveItem,
    [DEBUG_MENU_ITEM_GIVE_MONEY] = DebugAction_GiveMoney,
    [DEBUG_MENU_ITEM_GIVE_BADGE] = DebugAction_GiveBadge,
    [DEBUG_MENU_ITEM_TOGGLE_COLLISION] = DebugAction_ToggleCollision,
    [DEBUG_MENU_ITEM_WARP] = NULL,
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

static void DebugAction_GivePokemon(u8 taskId)
{
    ScriptGiveMon(SPECIES_MEWTWO, 100, ITEM_NONE, 0, 0, 0);
    Debug_DestroyMainMenu(taskId);
}

static void DebugAction_GiveItem(u8 taskId)
{
    u16 i;
    for (i = 1; i < ITEMS_COUNT; i++)
        AddBagItem(i,99);
    Debug_DestroyMainMenu(taskId);
}

static void DebugAction_GiveMoney(u8 taskId)
{
    AddMoney(&gSaveBlock1Ptr->money, 999999);
    gSaveBlock2Ptr->frontier.battlePoints = 9999;
    Debug_DestroyMainMenu(taskId);
}

static void DebugAction_GiveBadge(u8 taskId)
{
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_BADGE02_GET);
    FlagSet(FLAG_BADGE03_GET);
    FlagSet(FLAG_BADGE04_GET);
    FlagSet(FLAG_BADGE05_GET);
    FlagSet(FLAG_BADGE06_GET);
    FlagSet(FLAG_BADGE07_GET);
    FlagSet(FLAG_BADGE08_GET);
    FlagSet(FLAG_LANDMARK_BATTLE_FRONTIER);
    Debug_DestroyMainMenu(taskId);
}

static void DebugAction_ToggleCollision(u8 taskId)
{
    if (FlagGet(FLAG_SYS_COLLISIONS_DISABLED))
    {
        FlagClear(FLAG_SYS_COLLISIONS_DISABLED);
        DisableWildEncounters(FALSE);
    }
    else
    {
        FlagSet(FLAG_SYS_COLLISIONS_DISABLED);
        DisableWildEncounters(TRUE);
    }    

    Debug_DestroyMainMenu(taskId);
}

static void DebugAction_Cancel(u8 taskId)
{
    Debug_DestroyMainMenu(taskId);
}

#endif 