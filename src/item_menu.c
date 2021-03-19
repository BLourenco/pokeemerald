#include "global.h"
#include "item_menu.h"
#include "battle.h"
#include "battle_controllers.h"
#include "battle_pyramid.h"
#include "frontier_util.h"
#include "battle_pyramid_bag.h"
#include "berry_tag_screen.h"
#include "bg.h"
#include "constants/items.h"
#include "constants/songs.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_specials.h"
#include "graphics.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "item.h"
#include "item_menu_icons.h"
#include "item_use.h"
#include "lilycove_lady.h"
#include "list_menu.h"
#include "link.h"
#include "mail.h"
#include "main.h"
#include "malloc.h"
#include "map_name_popup.h"
#include "menu.h"
#include "money.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "player_pc.h"
#include "pokemon.h"
#include "pokemon_summary_screen.h"
#include "scanline_effect.h"
#include "script.h"
#include "shop.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text_window.h"
#include "menu_helpers.h"
#include "window.h"
#include "apprentice.h"
#include "battle_pike.h"
#include "constants/rgb.h"

enum
{
    SWITCH_POCKET_NONE,
    SWITCH_POCKET_LEFT,
    SWITCH_POCKET_RIGHT
};

void GoToBagMenu(u8 bagMenuType, u8 pocketId, void (*postExitMenuMainCallback2)());
void CB2_Bag(void);
bool8 SetupBagMenu(void);
void BagMenu_InitBGs(void);
bool8 LoadBagMenu_Graphics(void);
void SetupBagMenu_Textboxes(void);
void AllocateBagItemListBuffers(void);
void LoadBagItemListBuffers(u8);
void BagMenu_PrintPocketNames(const u8*, const u8*);
void BagMenu_CopyPocketNameToWindow(u32);
static void DrawPocketIndicatorSquare(u8 x, bool8 isCurrentPocket);
void CreatePocketScrollArrowPair(void);
void CreatePocketSwitchArrowPair(void);
void BagMenu_PrepareTMHMMoveWindow(void);
bool8 IsWallysBag(void);
void Task_WallyTutorialBagMenu(u8);
void Task_BagMenu_HandleInput(u8);
void GetItemName(s8*, u16);
u16 ItemIdToBattleMoveId(u16);
u16 BagGetItemIdByPocketPosition(u8, u16);
void BagMenu_PrintDescription(int);
void BagMenu_PrintCursor(u8, u8);
void BagMenu_Print(u8, u8, const u8*, u8, u8, u8, u8, u8, u8);
bool8 ItemId_GetImportance(u16);
u16 BagGetQuantityByPocketPosition(u8, u16);
void BagDestroyPocketSwitchArrowPair(void);
void TaskCloseBagMenu_2(u8);
u8 AddItemMessageWindow(u8);
void BagMenu_RemoveBagItemMessageindow(u8);
void set_callback3_to_bag(u8);
void PrintItemDepositAmount(u8, s16);
static u8 BagMenu_AddWindow(u8);
static u8 GetSwitchBagPocketDirection(void);
static void SwitchBagPocket(u8, s16, u16);
static bool8 CanSwapItems(void);
static void BagMenu_SwapItems(u8 taskId);
static void sub_81AC10C(u8);
static void Task_HandleSwappingItemsInput(u8);
void sub_81AC498(u8);
void sub_81AC590(u8);
void PrintTMHMMoveData(u16);
void sub_81ACAF8(u8);
void sub_81ACB54(u8, u8, u8);
void Task_HandleInBattleItemMenuInput(u8);
void Task_HandleOutOfBattleItemMenuInput(u8);
bool8 sub_81ACDFC(s8);
void BagMenu_RemoveWindow(u8);
void BagMenu_PrintThereIsNoPokemon(u8);
void Task_ChooseHowManyToToss(u8);
void BagMenu_TossItems(u8);
void BagMenu_YesNo(u8, u8, const struct YesNoFuncTable*);
void Task_ActuallyToss(u8);
void ItemMenu_Cancel(u8);
void sub_81AD350(u8);
static void BagMenu_PrintItemCantBeHeld(u8);
static void DisplayCurrentMoneyWindow(void);
static void DisplaySellItemPriceAndConfirm(u8);
void sub_81AD730(u8);
void sub_81AD6E4(u8);
static void RemoveMoneyWindow(void);
static void Task_SellHowManyDialogueHandleInput(u8);
static void BagMenu_Sell_UpdateItemListAndMoney(u8);
static void BagMenu_Sell_WaitForABPress(u8);
static void BagMenu_TryDepositItem(u8);
static void Task_ChooseHowManyToDeposit(u8 taskId);
static void BagMenu_Deposit_WaitForABPress(u8);
void CB2_ApprenticeExitBagMenu(void);
void CB2_FavorLadyExitBagMenu(void);
void CB2_QuizLadyExitBagMenu(void);
void CB2_FossilScientistExitBagMenu(void);
void All_CalculateNItemsAndMaxShowed(void);
static void SetPocketListPositions(void);
void UpdatePocketScrollPositions(void);
u8 CreateBagInputHandlerTask(u8);
void sub_81AC23C(u8);
void BagMenu_MoveCursorCallback(s32 a, bool8 b, struct ListMenu*);
void BagMenu_ItemPrintCallback(u8 windowId, s32 itemIndex, u8 a);
void ItemMenu_UseOutOfBattle(u8 taskId);
void ItemMenu_Toss(u8 taskId);
static void ItemMenu_Register(u8 taskId);
void ItemMenu_Give(u8 taskId);
void ItemMenu_Cancel(u8 taskId);
void ItemMenu_UseInBattle(u8 taskId);
void ItemMenu_CheckTag(u8 taskId);
void Task_FadeAndCloseBagMenu(u8 taskId);
void unknown_ItemMenu_Show(u8 taskId);
void unknown_ItemMenu_Give2(u8 taskId);
void unknown_ItemMenu_Confirm2(u8 taskId);
void Task_ItemContext_FieldOrBattle(u8 taskId);
void Task_ItemContext_FieldGive(u8 taskId);
void Task_ItemContext_Sell(u8 taskId);
void Task_ItemContext_Deposit(u8 taskId);
void Task_ItemContext_ItemPC_2(u8 taskId);
void BagMenu_ConfirmToss(u8 taskId);
void BagMenu_CancelToss(u8 taskId);
void BagMenu_ConfirmSell(u8 taskId);
void BagMenu_CancelSell(u8 taskId);
//bag sort
static void Task_LoadBagSortOptions(u8 taskId);
static void ItemMenu_SortByName(u8 taskId);
static void ItemMenu_SortByType(u8 taskId);
static void ItemMenu_SortByQuantity(u8 taskId);
static void ItemMenu_SortByNumber(u8 taskId);
static void SortBagItems(u8 taskId);
static void Task_SortFinish(u8 taskId);
static void SortItemsInBag(u8 pocket, u8 type);
static void MergeSort(struct ItemSlot* array, u32 low, u32 high, s8 (*comparator)(struct ItemSlot*, struct ItemSlot*));
static void Merge(struct ItemSlot* array, u32 low, u32 mid, u32 high, s8 (*comparator)(struct ItemSlot*, struct ItemSlot*));
static s8 CompareItemsAlphabetically(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2);
static s8 CompareItemsByMost(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2);
static s8 CompareItemsByType(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2);
static s8 CompareItemsById(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2);
// new
static void ItemMenu_RegisterSelect(u8 taskId);
static void ItemMenu_RegisterL(u8 taskId);
static void ItemMenu_RegisterR(u8 taskId);
static void ItemMenu_Deselect(u8 taskId);

// .rodata

static const struct BgTemplate sBgTemplates_ItemMenu[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    {
        .bg = 2,
        .charBaseIndex = 3,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0,
    },
};

static const struct ListMenuTemplate sItemListMenu =
{
    .items = NULL,
    .moveCursorFunc = BagMenu_MoveCursorCallback,
    .itemPrintFunc = BagMenu_ItemPrintCallback,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 1,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 7,
    .cursorKind = 0
};

static const u8 sMenuText_ByName[] = _("Name");
static const u8 sMenuText_ByType[] = _("Type");
static const u8 sMenuText_ByQuantity[] = _("Quantity");
static const u8 sMenuText_ByNumber[] = _("Number");
static const u8 sMenuText_Select[] = _("Select");
static const u8 sMenuText_L[] = _("L Button");
static const u8 sMenuText_R[] = _("R Button");
static const struct MenuAction sItemMenuActions[] = {
    [ITEMMENUACTION_USE] =          {gMenuText_Use, ItemMenu_UseOutOfBattle},
    [ITEMMENUACTION_TOSS] =         {gMenuText_Toss, ItemMenu_Toss},
    [ITEMMENUACTION_REGISTER] =     {gMenuText_Register, ItemMenu_Register},
    [ITEMMENUACTION_GIVE] =         {gMenuText_Give, ItemMenu_Give},
    [ITEMMENUACTION_CANCEL] =       {gText_Cancel2, ItemMenu_Cancel},
    [ITEMMENUACTION_BATTLE_USE] =   {gMenuText_Use, ItemMenu_UseInBattle},
    [ITEMMENUACTION_CHECK] =        {gMenuText_Check, ItemMenu_UseOutOfBattle},
    [ITEMMENUACTION_WALK] =         {gMenuText_Walk, ItemMenu_UseOutOfBattle},
    [ITEMMENUACTION_DESELECT] =     {gMenuText_Deselect, ItemMenu_Deselect},
    [ITEMMENUACTION_CHECK_TAG] =    {gMenuText_CheckTag, ItemMenu_CheckTag},
    [ITEMMENUACTION_CONFIRM] =      {gMenuText_Confirm, Task_FadeAndCloseBagMenu},
    [ITEMMENUACTION_SHOW] =         {gMenuText_Show, unknown_ItemMenu_Show},
    [ITEMMENUACTION_GIVE_2] =       {gMenuText_Give2, unknown_ItemMenu_Give2},
    [ITEMMENUACTION_CONFIRM_2] =    {gMenuText_Confirm, unknown_ItemMenu_Confirm2},
    [ITEMMENUACTION_BY_NAME] =      {sMenuText_ByName, ItemMenu_SortByName},
    [ITEMMENUACTION_BY_TYPE] =      {sMenuText_ByType, ItemMenu_SortByType},
    [ITEMMENUACTION_BY_NUMBER] =    {sMenuText_ByNumber, ItemMenu_SortByNumber},
    [ITEMMENUACTION_BY_QUANTITY] =  {sMenuText_ByQuantity, ItemMenu_SortByQuantity},
    [ITEMMENUACTION_SELECT_BUTTON] ={sMenuText_Select, ItemMenu_RegisterSelect},
    [ITEMMENUACTION_L_BUTTON] =     {sMenuText_L, ItemMenu_RegisterL},
    [ITEMMENUACTION_R_BUTTON] =     {sMenuText_R, ItemMenu_RegisterR},
    [ITEMMENUACTION_DUMMY] =        {gText_EmptyString2, NULL}
};

// these are all 2D arrays with a width of 2 but are represented as 1D arrays
// ITEMMENUACTION_DUMMY is used to represent blank spaces
static const u8 sContextMenuItems_ItemsPocket[] = {
    ITEMMENUACTION_USE,         ITEMMENUACTION_GIVE,
    ITEMMENUACTION_TOSS,        ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_MedicinePocket[] = {
    ITEMMENUACTION_USE,         ITEMMENUACTION_GIVE,
    ITEMMENUACTION_TOSS,        ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_BallsPocket[] = {
    ITEMMENUACTION_GIVE,        ITEMMENUACTION_DUMMY,
    ITEMMENUACTION_TOSS,        ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_CompetitivePocket[] = {
    ITEMMENUACTION_GIVE,        ITEMMENUACTION_DUMMY,
    ITEMMENUACTION_TOSS,        ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_BerriesPocket[] = {
    ITEMMENUACTION_CHECK_TAG,   ITEMMENUACTION_DUMMY,
    ITEMMENUACTION_USE,         ITEMMENUACTION_GIVE,
    ITEMMENUACTION_TOSS,        ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_TrainingPocket[] = {
    ITEMMENUACTION_USE,         ITEMMENUACTION_GIVE,
    ITEMMENUACTION_DUMMY,       ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_TmHmPocket[] = {
    ITEMMENUACTION_USE,         ITEMMENUACTION_GIVE,
    ITEMMENUACTION_DUMMY,       ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_KeyItemsPocket[] = {
    ITEMMENUACTION_USE,         ITEMMENUACTION_REGISTER,
    ITEMMENUACTION_DUMMY,       ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_BattleUse[] = {
    ITEMMENUACTION_BATTLE_USE,  ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_Give[] = {
    ITEMMENUACTION_GIVE,        ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_Cancel[] = {
    ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_BerryBlenderCrush[] = {
    ITEMMENUACTION_CONFIRM,     ITEMMENUACTION_CHECK_TAG,
    ITEMMENUACTION_DUMMY,       ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_Apprentice[] = {
    ITEMMENUACTION_SHOW,        ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_FavorLady[] = {
    ITEMMENUACTION_GIVE_2,      ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_QuizLady[] = {
    ITEMMENUACTION_CONFIRM_2,   ITEMMENUACTION_CANCEL
};

static const u8 sContextMenuItems_FossilScientist[] = {
    ITEMMENUACTION_SHOW,      ITEMMENUACTION_CANCEL
};

static const u8 sContextMenu_RegisterKeyItem[] = {
    ITEMMENUACTION_SELECT_BUTTON,   ITEMMENUACTION_L_BUTTON,
    ITEMMENUACTION_DUMMY,           ITEMMENUACTION_R_BUTTON
};

static const TaskFunc gUnknown_08614054[] = {
    [ITEMMENULOCATION_FIELD] =                  Task_ItemContext_FieldOrBattle,
    [ITEMMENULOCATION_BATTLE] =                 Task_ItemContext_FieldOrBattle,
    [ITEMMENULOCATION_PARTY] =                  Task_ItemContext_FieldGive,
    [ITEMMENULOCATION_SHOP] =                   Task_ItemContext_Sell,
    [ITEMMENULOCATION_BERRY_TREE] =             Task_FadeAndCloseBagMenu,
    [ITEMMENULOCATION_BERRY_BLENDER_CRUSH] =    Task_ItemContext_FieldOrBattle,
    [ITEMMENULOCATION_ITEMPC] =                 Task_ItemContext_Deposit,
    [ITEMMENULOCATION_FAVOR_LADY] =             Task_ItemContext_FieldOrBattle,
    [ITEMMENULOCATION_QUIZ_LADY] =              Task_ItemContext_FieldOrBattle,
    [ITEMMENULOCATION_APPRENTICE] =             Task_ItemContext_FieldOrBattle,
    [ITEMMENULOCATION_WALLY] =                  NULL,
    [ITEMMENULOCATION_PCBOX] =                  Task_ItemContext_ItemPC_2,
    [ITEMMENULOCATION_FOSSIL_SCIENTIST] =       Task_ItemContext_FieldOrBattle
};

static const struct YesNoFuncTable sYesNoTossFunctions = {BagMenu_ConfirmToss, BagMenu_CancelToss};

static const struct YesNoFuncTable sYesNoSellItemFunctions = {BagMenu_ConfirmSell, BagMenu_CancelSell};

static const struct ScrollArrowsTemplate sBagScrollArrowsTemplate = {
    .firstArrowType = SCROLL_ARROW_LEFT,
    .firstX = 28,
    .firstY = 16,
    .secondArrowType = SCROLL_ARROW_RIGHT,
    .secondX = 100,
    .secondY = 16,
    .fullyUpThreshold = -1,
    .fullyDownThreshold = -1,
    .tileTag = 111,
    .palTag = 111,
    .palNum = 0,
};

static const u8 sSelectButtonGfx[] = INCBIN_U8("graphics/interface/select_button.4bpp");
static const u8 sLButtonGfx[] = INCBIN_U8("graphics/interface/L_button.4bpp");
static const u8 sRButtonGfx[] = INCBIN_U8("graphics/interface/R_button.4bpp");

static const u8 sFontColorTable[][3] = {
// bgColor, textColor, shadowColor
    {0, 1, 3},
    {0, 1, 4},
    {0, 3, 6},
    {2, 1, 3},
    {0, 14, 10}
};

const struct WindowTemplate sDefaultBagWindows[] =
{
    { // Item names
        .bg = 0,
        .tilemapLeft = 14,
        .tilemapTop = 2,
        .width = 15,
        .height = 16,
        .paletteNum = 1,
        .baseBlock = 0x27,
    },
    { // Description
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 13,
        .width = 14,
        .height = 6,
        .paletteNum = 1,
        .baseBlock = 0x117,
    },
    { // Pocket name
        .bg = 0,
        .tilemapLeft = 4,
        .tilemapTop = 1,
        .width = 8,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 0x1A1,
    },
    { // TM/HM info icons
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 13,
        .width = 5,
        .height = 6,
        .paletteNum = 12,
        .baseBlock = 0x16B,
    },
    {// TM/HM info
        .bg = 0,
        .tilemapLeft = 7,
        .tilemapTop = 13,
        .width = 4,
        .height = 6,
        .paletteNum = 12,
        .baseBlock = 0x189,
    },
    { // Field message box
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x1B1,
    },
    DUMMY_WIN_TEMPLATE,
};

const struct WindowTemplate sContextMenuWindowTemplates[] =
{
    {
        .bg = 1,
        .tilemapLeft = 22,
        .tilemapTop = 17,
        .width = 7,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 22,
        .tilemapTop = 15,
        .width = 7,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 15,
        .tilemapTop = 15,
        .width = 14,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 15,
        .tilemapTop = 13,
        .width = 14,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x1B1,
    },
    {
        .bg = 1,
        .tilemapLeft = 24,
        .tilemapTop = 15,
        .width = 5,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 21,
        .tilemapTop = 9,
        .width = 5,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 24,
        .tilemapTop = 17,
        .width = 5,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 18,
        .tilemapTop = 11,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x245,
    },
    {
        .bg = 1,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x231,
    },
};

// .text

struct ListBuffer1 {
    struct ListMenuItem subBuffers[MAX_POCKET_ITEMS];
};

struct ListBuffer2 {
    s8 name[MAX_POCKET_ITEMS][24];
};

struct TempWallyStruct {
    struct ItemSlot bagPocket_Medicine[BAG_MEDICINE_COUNT];
    struct ItemSlot bagPocket_PokeBalls[BAG_POKEBALLS_COUNT];
    u16 cursorPosition[POCKETS_COUNT];
    u16 scrollPosition[POCKETS_COUNT];
    u8 filler[2];
    u16 pocket;
};

EWRAM_DATA struct BagMenuStruct *gBagMenu = 0;
EWRAM_DATA struct BagStruct gBagPositionStruct = {0};
static EWRAM_DATA struct ListBuffer1 *sListBuffer1 = 0;
static EWRAM_DATA struct ListBuffer2 *sListBuffer2 = 0;
EWRAM_DATA u16 gSpecialVar_ItemId = 0;
static EWRAM_DATA struct TempWallyStruct *sTempWallyBag = 0;
static EWRAM_DATA bool8 sRegisterSubMenu = FALSE;

extern u8 *const gPocketNamesStringsTable[];
extern u8* gReturnToXStringsTable[];
extern const u8 EventScript_SelectWithoutRegisteredItem[];
extern const u16 gUnknown_0860F074[];

void ResetBagScrollPositions(void)
{
    gBagPositionStruct.pocket = MEDICINE_POCKET;
    memset(gBagPositionStruct.cursorPosition, 0, 10);
    memset(gBagPositionStruct.scrollPosition, 0, 10);
}

void CB2_BagMenuFromStartMenu(void)
{
    GoToBagMenu(ITEMMENULOCATION_FIELD, POCKETS_COUNT, CB2_ReturnToFieldWithOpenMenu);
}

void CB2_BagMenuFromBattle(void)
{
    if (!InBattlePyramid())
        GoToBagMenu(ITEMMENULOCATION_BATTLE, POCKETS_COUNT, CB2_SetUpReshowBattleScreenAfterMenu2);
    else
        GoToBattlePyramidBagMenu(1, CB2_SetUpReshowBattleScreenAfterMenu2);
}

// Choosing berry to plant
void CB2_ChooseBerry(void)
{
    GoToBagMenu(ITEMMENULOCATION_BERRY_TREE, BERRIES_POCKET, CB2_ReturnToFieldContinueScript);
}

// Choosing berry for Berry Blender or Berry Crush
void ChooseBerryForMachine(void (*exitCallback)(void))
{
    GoToBagMenu(ITEMMENULOCATION_BERRY_BLENDER_CRUSH, BERRIES_POCKET, exitCallback);
}

void CB2_GoToSellMenu(void)
{
    GoToBagMenu(ITEMMENULOCATION_SHOP, POCKETS_COUNT, CB2_ExitSellMenu);
}

void CB2_GoToItemDepositMenu(void)
{
    GoToBagMenu(ITEMMENULOCATION_ITEMPC, POCKETS_COUNT, sub_816B31C);
}

void ApprenticeOpenBagMenu(void)
{
    GoToBagMenu(ITEMMENULOCATION_APPRENTICE, POCKETS_COUNT, CB2_ApprenticeExitBagMenu);
    gSpecialVar_0x8005 = ITEM_NONE;
    gSpecialVar_Result = FALSE;
}

void FavorLadyOpenBagMenu(void)
{
    GoToBagMenu(ITEMMENULOCATION_FAVOR_LADY, POCKETS_COUNT, CB2_FavorLadyExitBagMenu);
    gSpecialVar_Result = FALSE;
}

void QuizLadyOpenBagMenu(void)
{
    GoToBagMenu(ITEMMENULOCATION_QUIZ_LADY, POCKETS_COUNT, CB2_QuizLadyExitBagMenu);
    gSpecialVar_Result = FALSE;
}

void FossilScientistOpenBagMenu(void)
{
    GoToBagMenu(ITEMMENULOCATION_FOSSIL_SCIENTIST, ITEMS_POCKET, CB2_FossilScientistExitBagMenu);
    gSpecialVar_Result = FALSE;
}

bool8 IsItemFossil(void)
{
    switch (gSpecialVar_ItemId)
    {
        case ITEM_HELIX_FOSSIL:
        case ITEM_DOME_FOSSIL:
        case ITEM_OLD_AMBER:
        case ITEM_ROOT_FOSSIL:
        case ITEM_CLAW_FOSSIL:
        case ITEM_SKULL_FOSSIL:
        case ITEM_ARMOR_FOSSIL:
        case ITEM_COVER_FOSSIL:
        case ITEM_PLUME_FOSSIL:
        case ITEM_JAW_FOSSIL:
        case ITEM_SAIL_FOSSIL:
            return TRUE;
    }

    return FALSE;
}

void GoToBagMenu(u8 location, u8 pocket, void ( *postExitMenuMainCallback2)())
{
    gBagMenu = AllocZeroed(sizeof(struct BagMenuStruct));
    if (gBagMenu == NULL)
    {
        SetMainCallback2(postExitMenuMainCallback2);
    }
    else
    {
        if (location != ITEMMENULOCATION_LAST)
            gBagPositionStruct.location = location;
        if (postExitMenuMainCallback2)
            gBagPositionStruct.bagCallback = postExitMenuMainCallback2;
        if (pocket < POCKETS_COUNT)
            gBagPositionStruct.pocket = pocket;
        if (gBagPositionStruct.location == ITEMMENULOCATION_BERRY_TREE ||
            gBagPositionStruct.location == ITEMMENULOCATION_BERRY_BLENDER_CRUSH ||
            gBagPositionStruct.location == ITEMMENULOCATION_FOSSIL_SCIENTIST)
            gBagMenu->pocketSwitchDisabled = TRUE;
        gBagMenu->exitCallback = NULL;
        gBagMenu->itemOriginalLocation = 0xFF;
        gBagMenu->pocketScrollArrowsTask = 0xFF;
        gBagMenu->pocketSwitchArrowsTask = 0xFF;
        memset(gBagMenu->spriteId, 0xFF, sizeof(gBagMenu->spriteId));
        memset(gBagMenu->windowPointers, 0xFF, 10);
        SetMainCallback2(CB2_Bag);
    }
}

void CB2_BagMenuRun(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

void VBlankCB_BagMenuRun(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

#define tItemCount data[8]

void CB2_Bag(void)
{
    while(MenuHelpers_CallLinkSomething() != TRUE && SetupBagMenu() != TRUE && MenuHelpers_LinkSomething() != TRUE) {};
}

bool8 SetupBagMenu(void)
{
    u8 taskId;

    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        gMain.state++;
        break;
    case 2:
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 3:
        ResetPaletteFade();
        gPaletteFade.bufferTransferDisabled = TRUE;
        gMain.state++;
        break;
    case 4:
        ResetSpriteData();
        gMain.state++;
        break;
    case 5:
        gMain.state++;
        break;
    case 6:
        if (!MenuHelpers_LinkSomething())
            ResetTasks();
        gMain.state++;
        break;
    case 7:
        BagMenu_InitBGs();
        gBagMenu->graphicsLoadState = 0;
        gMain.state++;
        break;
    case 8:
        if (!LoadBagMenu_Graphics())
            break;
        gMain.state++;
        break;
    case 9:
        SetupBagMenu_Textboxes();
        gMain.state++;
        break;
    case 10:
        All_CalculateNItemsAndMaxShowed();
        SetPocketListPositions();
        UpdatePocketScrollPositions();
        gMain.state++;
        break;
    case 11:
        AllocateBagItemListBuffers();
        gMain.state++;
        break;
    case 12:
        LoadBagItemListBuffers(gBagPositionStruct.pocket);
        gMain.state++;
        break;
    case 13:
        BagMenu_PrintPocketNames(gPocketNamesStringsTable[gBagPositionStruct.pocket], 0);
        BagMenu_CopyPocketNameToWindow(0);
        DrawPocketIndicatorSquare(0, FALSE);
        DrawPocketIndicatorSquare(5, FALSE);
        DrawPocketIndicatorSquare(6, FALSE);
        DrawPocketIndicatorSquare(7, FALSE);
        DrawPocketIndicatorSquare(gBagPositionStruct.pocket, TRUE);
        gMain.state++;
        break;
    case 14:
        taskId = CreateBagInputHandlerTask(gBagPositionStruct.location);
        gTasks[taskId].data[0] = ListMenuInit(&gMultiuseListMenuTemplate, gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
        gTasks[taskId].data[3] = 0;
        gTasks[taskId].tItemCount = 0;
        gMain.state++;
        break;
    case 15:
        AddBagVisualSprite(gBagPositionStruct.pocket);
        gMain.state++;
        break;
    case 16:
        sub_80D4FAC();
        gMain.state++;
        break;
    case 17:
        CreatePocketScrollArrowPair();
        CreatePocketSwitchArrowPair();
        gMain.state++;
        break;
    case 18:
        BagMenu_PrepareTMHMMoveWindow();
        gMain.state++;
        break;
    case 19:
        BlendPalettes(0xFFFFFFFF, 16, 0);
        gMain.state++;
        break;
    case 20:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gPaletteFade.bufferTransferDisabled = FALSE;
        gMain.state++;
        break;
    default:
        SetVBlankCallback(VBlankCB_BagMenuRun);
        SetMainCallback2(CB2_BagMenuRun);
        return TRUE;
    }
    return FALSE;
}

void BagMenu_InitBGs(void)
{
    ResetVramOamAndBgCntRegs();
    memset(gBagMenu->tilemapBuffer, 0, 0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplates_ItemMenu, ARRAY_COUNT(sBgTemplates_ItemMenu));
    SetBgTilemapBuffer(2, gBagMenu->tilemapBuffer);
    ResetAllBgsCoordinates();
    ScheduleBgCopyTilemapToVram(2);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
}

bool8 LoadBagMenu_Graphics(void)
{
    switch (gBagMenu->graphicsLoadState)
    {
        case 0:
            ResetTempTileDataBuffers();
            DecompressAndCopyTileDataToVram(2, gBagScreen_Gfx, 0, 0, 0);
            gBagMenu->graphicsLoadState++;
            break;
        case 1:
            if (FreeTempTileDataBuffersIfPossible() != TRUE)
            {
                LZDecompressWram(gBagScreen_GfxTileMap, gBagMenu->tilemapBuffer);
                gBagMenu->graphicsLoadState++;
            }
            break;
        case 2:
            if (!IsWallysBag() && gSaveBlock2Ptr->playerGender != MALE)
                LoadCompressedPalette(gBagScreenFemale_Pal, 0, 0x40);
            else
                LoadCompressedPalette(gBagScreenMale_Pal, 0, 0x40);
            gBagMenu->graphicsLoadState++;
            break;
        case 3:
            if (IsWallysBag() == TRUE || gSaveBlock2Ptr->playerGender == MALE)
                LoadCompressedSpriteSheet(&gBagMaleSpriteSheet);
            else
                LoadCompressedSpriteSheet(&gBagFemaleSpriteSheet);
            gBagMenu->graphicsLoadState++;
            break;
        case 4:
            LoadCompressedSpritePalette(&gBagPaletteTable);
            gBagMenu->graphicsLoadState++;
            break;
        default:
            LoadListMenuArrowsGfx();
            gBagMenu->graphicsLoadState = 0;
            return TRUE;
    }
    return FALSE;
}

u8 CreateBagInputHandlerTask(u8 location)
{
    u8 taskId;
    if (location == ITEMMENULOCATION_WALLY)
        taskId = CreateTask(Task_WallyTutorialBagMenu, 0);
    else
        taskId = CreateTask(Task_BagMenu_HandleInput, 0);
    return taskId;
}

void AllocateBagItemListBuffers(void)
{
    sListBuffer1 = Alloc(sizeof(struct ListBuffer1));
    sListBuffer2 = Alloc(sizeof(struct ListBuffer2));
}

void LoadBagItemListBuffers(u8 pocketId)
{
    u16 i;
    struct BagPocket *pocket = &gBagPockets[pocketId];
    struct ListMenuItem *subBuffer;

    if (!gBagMenu->hideCloseBagText)
    {
        for (i = 0; i < gBagMenu->numItemStacks[pocketId] - 1; i++)
        {
            GetItemName(sListBuffer2->name[i], pocket->itemSlots[i].itemId);
            subBuffer = sListBuffer1->subBuffers;
            subBuffer[i].name = sListBuffer2->name[i];
            subBuffer[i].id = i;
        }
        StringCopy(sListBuffer2->name[i], gText_CloseBag);
        subBuffer = sListBuffer1->subBuffers;
        subBuffer[i].name = sListBuffer2->name[i];
        subBuffer[i].id = LIST_CANCEL;
    }
    else
    {
        for (i = 0; i < gBagMenu->numItemStacks[pocketId]; i++)
        {
            GetItemName(sListBuffer2->name[i], pocket->itemSlots[i].itemId);
            subBuffer = sListBuffer1->subBuffers;
            subBuffer[i].name = sListBuffer2->name[i];
            subBuffer[i].id = i;
        }
    }
    gMultiuseListMenuTemplate = sItemListMenu;
    gMultiuseListMenuTemplate.totalItems = gBagMenu->numItemStacks[pocketId];
    gMultiuseListMenuTemplate.items = sListBuffer1->subBuffers;
    gMultiuseListMenuTemplate.maxShowed = gBagMenu->numShownItems[pocketId];
}

void GetItemName(s8 *dest, u16 itemId)
{
    switch (gBagPositionStruct.pocket)
    {
        case TMHM_POCKET:
            StringCopy(gStringVar2, gMoveNames[ItemIdToBattleMoveId(itemId)]);
            if (itemId >= ITEM_HM01)
            {
                ConvertIntToDecimalStringN(gStringVar1, itemId - ITEM_HM01 + 1, STR_CONV_MODE_LEADING_ZEROS, 2);
                StringExpandPlaceholders(dest, gText_ClearTo11Var1Clear5Var2);
            }
            else
            {
                ConvertIntToDecimalStringN(gStringVar1, itemId - ITEM_TM01 + 1, STR_CONV_MODE_LEADING_ZEROS, 3);
                StringExpandPlaceholders(dest, gText_NumberVar1Clear7Var2);
            }
            break;
        case BERRIES_POCKET:
            ConvertIntToDecimalStringN(gStringVar1, itemId - FIRST_BERRY_INDEX + 1, STR_CONV_MODE_LEADING_ZEROS, 2);
            CopyItemName(itemId, gStringVar2);
            StringExpandPlaceholders(dest, gText_NumberVar1Clear7Var2);
            break;
        default:
            CopyItemName(itemId, dest);
            break;
    }
}

void BagMenu_MoveCursorCallback(s32 itemIndex, bool8 onInit, struct ListMenu *list)
{
    if (onInit != TRUE)
    {
        PlaySE(SE_SELECT);
        ShakeBagSprite();
    }
    if (gBagMenu->itemOriginalLocation == 0xFF)
    {
        RemoveBagItemIconSprite(gBagMenu->itemIconSlot ^ 1);
        if (itemIndex != LIST_CANCEL)
           AddBagItemIconSprite(BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, itemIndex), gBagMenu->itemIconSlot);
        else
           AddBagItemIconSprite(-1, gBagMenu->itemIconSlot);
        gBagMenu->itemIconSlot ^= 1;
        if (!gBagMenu->inhibitItemDescriptionPrint)
            BagMenu_PrintDescription(itemIndex);
    }
}

void BagMenu_ItemPrintCallback(u8 windowId, s32 itemIndex, u8 y)
{
    u16 itemId;
    u16 itemQuantity;
    int offset;

    if (itemIndex != LIST_CANCEL)
    {
        if (gBagMenu->itemOriginalLocation != 0xFF)
        {
            if (gBagMenu->itemOriginalLocation == (u8)itemIndex)
                BagMenu_PrintCursor(y, 2);
            else
                BagMenu_PrintCursor(y, 0xFF);
        }

        itemId = BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, itemIndex);
        itemQuantity = BagGetQuantityByPocketPosition(gBagPositionStruct.pocket + 1, itemIndex);

        if (itemId >= ITEM_HM01 && itemId <= ITEM_HM08)
            BlitBitmapToWindow(windowId, gBagMenuHMIcon_Gfx, 8, y - 1, 16, 16);

        if (gBagPositionStruct.pocket == BERRIES_POCKET)
        {
            ConvertIntToDecimalStringN(gStringVar1, itemQuantity, STR_CONV_MODE_RIGHT_ALIGN, BERRY_CAPACITY_DIGITS);
            StringExpandPlaceholders(gStringVar4, gText_xVar1);
            offset = GetStringRightAlignXOffset(7, gStringVar4, 119);
            BagMenu_Print(windowId, 7, gStringVar4, offset, y, 0, 0, -1, 0);
        }
        else if (gBagPositionStruct.pocket != KEYITEMS_POCKET && ItemId_GetImportance(itemId) == FALSE)
        {
            ConvertIntToDecimalStringN(gStringVar1, itemQuantity, STR_CONV_MODE_RIGHT_ALIGN, BAG_ITEM_CAPACITY_DIGITS);
            StringExpandPlaceholders(gStringVar4, gText_xVar1);
            offset = GetStringRightAlignXOffset(7, gStringVar4, 119);
            BagMenu_Print(windowId, 7, gStringVar4, offset, y, 0, 0, -1, 0);
        }
        else
        {
            if (gSaveBlock1Ptr->registeredItemSelect && gSaveBlock1Ptr->registeredItemSelect == itemId)
                BlitBitmapToWindow(windowId, sSelectButtonGfx, 96, y - 1, 24, 16);
            
            if (gSaveBlock1Ptr->registeredItemL && gSaveBlock1Ptr->registeredItemL == itemId)
                BlitBitmapToWindow(windowId, sLButtonGfx, 96, y - 1, 24, 16);
            
            if (gSaveBlock1Ptr->registeredItemR && gSaveBlock1Ptr->registeredItemR == itemId)
                BlitBitmapToWindow(windowId, sRButtonGfx, 96, y - 1, 24, 16);
        }
    }
}

void BagMenu_PrintDescription(int itemIndex)
{
    const u8 *str;
    if (itemIndex != LIST_CANCEL)
    {
        str = ItemId_GetDescription(BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, itemIndex));
    }
    else
    {
        StringCopy(gStringVar1, gReturnToXStringsTable[gBagPositionStruct.location]);
        StringExpandPlaceholders(gStringVar4, gText_ReturnToVar1);
        str = gStringVar4;
    }
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    BagMenu_Print(1, 1, str, 3, 1, 0, 0, 0, 0);
}

void BagMenu_PrintCursor_(u8 listTaskId, u8 colorIndex)
{
    BagMenu_PrintCursor(ListMenuGetYCoordForPrintingArrowCursor(listTaskId), colorIndex);
}

void BagMenu_PrintCursor(u8 y, u8 colorIndex)
{
    if (colorIndex == 0xFF)
        FillWindowPixelRect(0, PIXEL_FILL(0), 0, y, GetMenuCursorDimensionByFont(1, 0), GetMenuCursorDimensionByFont(1, 1));
    else
        BagMenu_Print(0, 1, gText_SelectorArrow2, 0, y, 0, 0, 0, colorIndex);

}

void CreatePocketScrollArrowPair(void)
{
    if (gBagMenu->pocketScrollArrowsTask == 0xFF)
        gBagMenu->pocketScrollArrowsTask = AddScrollIndicatorArrowPairParameterized(
            SCROLL_ARROW_UP,
            172,
            12,
            148,
            gBagMenu->numItemStacks[gBagPositionStruct.pocket] - gBagMenu->numShownItems[gBagPositionStruct.pocket],
            110,
            110,
            &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket]);
}

void BagDestroyPocketScrollArrowPair(void)
{
    if (gBagMenu->pocketScrollArrowsTask != 0xFF)
    {
        RemoveScrollIndicatorArrowPair(gBagMenu->pocketScrollArrowsTask);
        gBagMenu->pocketScrollArrowsTask = 0xFF;
    }
    BagDestroyPocketSwitchArrowPair();
}

void CreatePocketSwitchArrowPair(void)
{
    if (gBagMenu->pocketSwitchDisabled != TRUE && gBagMenu->pocketSwitchArrowsTask == 0xFF)
        gBagMenu->pocketSwitchArrowsTask = AddScrollIndicatorArrowPair(&sBagScrollArrowsTemplate, &gBagPositionStruct.unk6);
}

void BagDestroyPocketSwitchArrowPair(void)
{
    if (gBagMenu->pocketSwitchArrowsTask != 0xFF)
    {
        RemoveScrollIndicatorArrowPair(gBagMenu->pocketSwitchArrowsTask);
        gBagMenu->pocketSwitchArrowsTask = 0xFF;
    }
}

void FreeBagItemListBuffers(void)
{
    Free(sListBuffer2);
    Free(sListBuffer1);
    FreeAllWindowBuffers();
    Free(gBagMenu);
}

void Task_FadeAndCloseBagMenu(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = TaskCloseBagMenu_2;
}

void TaskCloseBagMenu_2(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {
        DestroyListMenuTask(data[0], &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
        if (gBagMenu->exitCallback != NULL)
            SetMainCallback2(gBagMenu->exitCallback);
        else
            SetMainCallback2(gBagPositionStruct.bagCallback);
        BagDestroyPocketScrollArrowPair();
        ResetSpriteData();
        FreeAllSpritePalettes();
        FreeBagItemListBuffers();
        DestroyTask(taskId);
    }
}

void UpdatePocketItemList(u8 pocketId)
{
    u16 i;
    struct BagPocket *pocket = &gBagPockets[pocketId];
    switch (pocketId)
    {
        case TMHM_POCKET:
        case BERRIES_POCKET:
            SortBerriesOrTMHMs(pocket);
            break;
        default:
            CompactItemsInBagPocket(pocket);
            break;
    }

    gBagMenu->numItemStacks[pocketId] = 0;

    for (i = 0; i < pocket->capacity && pocket->itemSlots[i].itemId; i++)
        gBagMenu->numItemStacks[pocketId]++;

    if (!gBagMenu->hideCloseBagText)
        gBagMenu->numItemStacks[pocketId]++;

    if (gBagMenu->numItemStacks[pocketId] > 8)
        gBagMenu->numShownItems[pocketId] = 8;
    else
        gBagMenu->numShownItems[pocketId] = gBagMenu->numItemStacks[pocketId];
}

void All_CalculateNItemsAndMaxShowed(void)
{
    u8 i;
    for (i = 0; i < POCKETS_COUNT; i++)
        UpdatePocketItemList(i);
}

void SetInitialScrollAndCursorPositions(u8 pocketId)
{
    sub_812225C(&gBagPositionStruct.scrollPosition[pocketId], &gBagPositionStruct.cursorPosition[pocketId], gBagMenu->numShownItems[pocketId], gBagMenu->numItemStacks[pocketId]);
}

static void SetPocketListPositions(void)
{
    u8 i;
    for (i = 0; i < POCKETS_COUNT; i++)
        SetInitialScrollAndCursorPositions(i);
}

void UpdatePocketScrollPositions(void)
{
    u8 i;
    for (i = 0; i < POCKETS_COUNT; i++)
        sub_8122298(&gBagPositionStruct.scrollPosition[i], &gBagPositionStruct.cursorPosition[i], gBagMenu->numShownItems[i], gBagMenu->numItemStacks[i], 8);
}

u8 GetItemListPosition(u8 pocketId)
{
    return gBagPositionStruct.scrollPosition[pocketId] + gBagPositionStruct.cursorPosition[pocketId];
}

void DisplayItemMessage(u8 taskId, u8 fontId, const u8 *str, void (*callback)(u8 taskId))
{
    s16* data = gTasks[taskId].data;

    data[10] = AddItemMessageWindow(4);
    FillWindowPixelBuffer(data[10], PIXEL_FILL(1));
    DisplayMessageAndContinueTask(taskId, data[10], 10, 13, fontId, GetPlayerTextSpeedDelay(), str, callback);
    ScheduleBgCopyTilemapToVram(1);
}

void BagMenu_InitListsMenu(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    BagMenu_RemoveBagItemMessageindow(4);
    DestroyListMenuTask(data[0], scrollPos, cursorPos);
    UpdatePocketItemList(gBagPositionStruct.pocket);
    SetInitialScrollAndCursorPositions(gBagPositionStruct.pocket);
    LoadBagItemListBuffers(gBagPositionStruct.pocket);
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
    ScheduleBgCopyTilemapToVram(0);
    set_callback3_to_bag(taskId);
}

void sub_81ABC3C(u8 a)
{
    PrintItemDepositAmount(BagMenu_AddWindow(a), 1);
}

void PrintItemDepositAmount(u8 windowId, s16 numDeposited)
{
    u8 numDigits = (gBagPositionStruct.pocket == BERRIES_POCKET) ? BERRY_CAPACITY_DIGITS : BAG_ITEM_CAPACITY_DIGITS;
    ConvertIntToDecimalStringN(gStringVar1, numDeposited, STR_CONV_MODE_LEADING_ZEROS, numDigits);
    StringExpandPlaceholders(gStringVar4, gText_xVar1);
    AddTextPrinterParameterized(windowId, 1, gStringVar4, GetStringCenterAlignXOffset(1, gStringVar4, 0x28), 2, 0, 0);
}

void PrintItemSoldAmount(int windowId, int numSold, int moneyEarned)
{
    u8 numDigits = (gBagPositionStruct.pocket == BERRIES_POCKET) ? BERRY_CAPACITY_DIGITS : BAG_ITEM_CAPACITY_DIGITS;
    ConvertIntToDecimalStringN(gStringVar1, numSold, STR_CONV_MODE_LEADING_ZEROS, numDigits);
    StringExpandPlaceholders(gStringVar4, gText_xVar1);
    AddTextPrinterParameterized(windowId, 1, gStringVar4, 0, 1, -1, 0);
    PrintMoneyAmount(windowId, 38, 1, moneyEarned, 0);
}

void Task_BagMenu_HandleInput(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    s32 listPosition;

    if (MenuHelpers_CallLinkSomething() != TRUE && !gPaletteFade.active)
    {
        switch (GetSwitchBagPocketDirection())
        {
            case SWITCH_POCKET_LEFT:
                SwitchBagPocket(taskId, MENU_CURSOR_DELTA_LEFT, 0);
                return;
            case SWITCH_POCKET_RIGHT:
                SwitchBagPocket(taskId, MENU_CURSOR_DELTA_RIGHT, 0);
                return;
            default:
                if (JOY_NEW(SELECT_BUTTON))
                {
                    if (CanSwapItems() == TRUE)
                    {
                        PlaySE(SE_SELECT);
                        BagMenu_SwapItems(taskId);
                    }
                    return;
                }
                else if (JOY_NEW(START_BUTTON))
                {
                    if ((gBagMenu->numItemStacks[gBagPositionStruct.pocket] - 1) <= 1) //can't sort with 0 or 1 item in bag
                    {
                        static const u8 sText_NothingToSort[] = _("There's nothing to sort!");
                        PlaySE(SE_SELECT);
                        DisplayItemMessage(taskId, 1, sText_NothingToSort, sub_81AD350);
                        break;
                    }
                    
                    data[1] = GetItemListPosition(gBagPositionStruct.pocket);
                    data[2] = BagGetQuantityByPocketPosition(gBagPositionStruct.pocket + 1, data[1]);
                    if (gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket] == gBagMenu->numItemStacks[gBagPositionStruct.pocket] - 1)
                        break;
                    else
                        gSpecialVar_ItemId = BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, data[1]);
                    
                    PlaySE(SE_SELECT);
                    BagDestroyPocketScrollArrowPair();
                    BagMenu_PrintCursor_(data[0], 2);
                    ListMenuGetScrollAndRow(data[0], scrollPos, cursorPos);
                    gTasks[taskId].func = Task_LoadBagSortOptions;
                }
                else
                {
                    listPosition = ListMenu_ProcessInput(data[0]);
                    ListMenuGetScrollAndRow(data[0], scrollPos, cursorPos);
                    switch (listPosition)
                    {
                        case LIST_NOTHING_CHOSEN:
                            break;
                        case LIST_CANCEL:
                            if (gBagPositionStruct.location == ITEMMENULOCATION_BERRY_BLENDER_CRUSH)
                            {
                                PlaySE(SE_FAILURE);
                                break;
                            }
                            PlaySE(SE_SELECT);
                            gSpecialVar_ItemId = ITEM_NONE;
                            gTasks[taskId].func = Task_FadeAndCloseBagMenu;
                            break;
                        default: // A_BUTTON
                            PlaySE(SE_SELECT);
                            BagDestroyPocketScrollArrowPair();
                            BagMenu_PrintCursor_(data[0], 2);
                            data[1] = listPosition;
                            data[2] = BagGetQuantityByPocketPosition(gBagPositionStruct.pocket + 1, listPosition);
                            gSpecialVar_ItemId = BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, listPosition);
                            gUnknown_08614054[gBagPositionStruct.location](taskId);
                            break;
                    }
                }
                break;
        }
    }
}

void set_callback3_to_bag(u8 taskId)
{
    CreatePocketScrollArrowPair();
    CreatePocketSwitchArrowPair();
    ClearWindowTilemap(3);
    ClearWindowTilemap(4);
    PutWindowTilemap(1);
    ScheduleBgCopyTilemapToVram(0);
    gTasks[taskId].func = Task_BagMenu_HandleInput;
}

static u8 GetSwitchBagPocketDirection(void)
{
    if (gBagMenu->pocketSwitchDisabled)
        return SWITCH_POCKET_NONE;
    if (JOY_NEW(DPAD_LEFT))
    {
        PlaySE(SE_SELECT);
        return SWITCH_POCKET_LEFT;
    }
    if (JOY_NEW(DPAD_RIGHT))
    {
        PlaySE(SE_SELECT);
        return SWITCH_POCKET_RIGHT;
    }
    return SWITCH_POCKET_NONE;
}

static void ChangeBagPocketId(u8 *bagPocketId, s8 deltaBagPocketId)
{
    if (deltaBagPocketId == 1 && *bagPocketId == POCKETS_COUNT - 1)
        *bagPocketId = 0;
    else if (deltaBagPocketId == -1 && *bagPocketId == 0)
        *bagPocketId = POCKETS_COUNT - 1;
    else
        *bagPocketId += deltaBagPocketId;
}

static void SwitchBagPocket(u8 taskId, s16 deltaBagPocketId, u16 a3)
{
    s16* data = gTasks[taskId].data;
    u8 pocketId;

    data[13] = 0;
    data[12] = 0;
    data[11] = deltaBagPocketId;
    if (a3 == 0)
    {
        ClearWindowTilemap(0);
        ClearWindowTilemap(1);
        DestroyListMenuTask(data[0], &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
        ScheduleBgCopyTilemapToVram(0);
        gSprites[gBagMenu->spriteId[2 + (gBagMenu->itemIconSlot ^ 1)]].invisible = TRUE;
        BagDestroyPocketScrollArrowPair();
    }
    pocketId = gBagPositionStruct.pocket;
    ChangeBagPocketId(&pocketId, deltaBagPocketId);
    if (deltaBagPocketId == MENU_CURSOR_DELTA_RIGHT)
    {
        BagMenu_PrintPocketNames(gPocketNamesStringsTable[gBagPositionStruct.pocket], gPocketNamesStringsTable[pocketId]);
        BagMenu_CopyPocketNameToWindow(0);
    }
    else
    {
        BagMenu_PrintPocketNames(gPocketNamesStringsTable[pocketId], gPocketNamesStringsTable[gBagPositionStruct.pocket]);
        BagMenu_CopyPocketNameToWindow(8);
    }
    DrawPocketIndicatorSquare(gBagPositionStruct.pocket, FALSE);
    DrawPocketIndicatorSquare(pocketId, TRUE);
    FillBgTilemapBufferRect_Palette0(2, 11, 14, 2, 15, 16);
    ScheduleBgCopyTilemapToVram(2);
    SetBagVisualPocketId(pocketId, 1);
    //SetBagVisualPocketId(-1, 1);
    RemoveBagSprite(1);
    AddSwitchPocketRotatingBallSprite(deltaBagPocketId);
    SetTaskFuncWithFollowupFunc(taskId, sub_81AC10C, gTasks[taskId].func);
}

void sub_81AC10C(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (!MenuHelpers_LinkSomething() && !IsWallysBag())
    {
        switch (GetSwitchBagPocketDirection())
        {
            case SWITCH_POCKET_LEFT:
                ChangeBagPocketId(&gBagPositionStruct.pocket, data[11]);
                SwitchTaskToFollowupFunc(taskId);
                SwitchBagPocket(taskId, MENU_CURSOR_DELTA_LEFT, 1);
                return;
            case SWITCH_POCKET_RIGHT:
                ChangeBagPocketId(&gBagPositionStruct.pocket, data[11]);
                SwitchTaskToFollowupFunc(taskId);
                SwitchBagPocket(taskId, MENU_CURSOR_DELTA_RIGHT, 1);
                return;
        }
    }
    switch (data[13])
    {
        case 0:
            sub_81AC23C(data[12]);
            if (!(++data[12] & 1))
            {
                if (data[11] == 1)
                    BagMenu_CopyPocketNameToWindow((u8)(data[12] >> 1));
                else
                    BagMenu_CopyPocketNameToWindow((u8)(8 - (data[12] >> 1)));
            }
            if (data[12] == 16)
                data[13]++;
            break;
        case 1:
            ChangeBagPocketId(&gBagPositionStruct.pocket, data[11]);
            LoadBagItemListBuffers(gBagPositionStruct.pocket);
            data[0] = ListMenuInit(&gMultiuseListMenuTemplate, gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
            PutWindowTilemap(1);
            PutWindowTilemap(2);
            ScheduleBgCopyTilemapToVram(0);
            CreatePocketScrollArrowPair();
            CreatePocketSwitchArrowPair();
            SwitchTaskToFollowupFunc(taskId);
    }
}

void sub_81AC23C(u8 a)
{
    FillBgTilemapBufferRect_Palette0(2, 17, 14, a + 2, 15, 1);
    ScheduleBgCopyTilemapToVram(2);
}

static void DrawPocketIndicatorSquare(u8 x, bool8 isCurrentPocket)
{
    if (!isCurrentPocket)
        FillBgTilemapBufferRect_Palette0(2, 0x1017, x + 4, 3, 1, 1);
    else
        FillBgTilemapBufferRect_Palette0(2, 0x102B, x + 4, 3, 1, 1);
    ScheduleBgCopyTilemapToVram(2);
}

static bool8 CanSwapItems(void)
{
    if (gBagPositionStruct.location <= ITEMMENULOCATION_BATTLE)
    {
        u8 temp = gBagPositionStruct.pocket - 2;
        if (temp > 1)
            return TRUE;
    }
    return FALSE;
}

void BagMenu_SwapItems(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    ListMenuSetUnkIndicatorsStructField(data[0], 16, 1);
    data[1] = gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket] + gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    gBagMenu->itemOriginalLocation = data[1];
    CopyItemName(BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, data[1]), gStringVar1);
    StringExpandPlaceholders(gStringVar4, gText_MoveVar1Where);
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
    sub_80D4FEC(data[1]);
    BagDestroyPocketSwitchArrowPair();
    BagMenu_PrintCursor_(data[0], 2);
    gTasks[taskId].func = Task_HandleSwappingItemsInput;
}

static void Task_HandleSwappingItemsInput(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    int input;

    if (MenuHelpers_CallLinkSomething() != TRUE)
    {
        if (JOY_NEW(SELECT_BUTTON))
        {
            PlaySE(SE_SELECT);
            ListMenuGetScrollAndRow(data[0], &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
            sub_81AC498(taskId);
        }
        else
        {
            input = ListMenu_ProcessInput(data[0]);
            ListMenuGetScrollAndRow(data[0], &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
            sub_80D4FC8(0);
            sub_80D4FEC(gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
            switch (input)
            {
                case LIST_NOTHING_CHOSEN:
                    break;
                case LIST_CANCEL:
                    PlaySE(SE_SELECT);
                    if (JOY_NEW(A_BUTTON))
                        sub_81AC498(taskId);
                    else
                        sub_81AC590(taskId);
                    break;
                default:
                    PlaySE(SE_SELECT);
                    sub_81AC498(taskId);
            }
        }
    }
}

void sub_81AC498(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    u16 realPos = (*scrollPos + *cursorPos);

    if (data[1] == realPos || data[1] == (realPos - 1))
        sub_81AC590(taskId);
    else
    {
        MoveItemSlotInList(gBagPockets[gBagPositionStruct.pocket].itemSlots, data[1], realPos);
        gBagMenu->itemOriginalLocation = -1;
        DestroyListMenuTask(data[0], scrollPos, cursorPos);
        if (data[1] < realPos)
            gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]--;
        LoadBagItemListBuffers(gBagPositionStruct.pocket);
        data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
        sub_80D4FC8(1);
        CreatePocketSwitchArrowPair();
        gTasks[taskId].func = Task_BagMenu_HandleInput;
    }
}

void sub_81AC590(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];

    gBagMenu->itemOriginalLocation = -1;
    DestroyListMenuTask(data[0], scrollPos, cursorPos);
    if (data[1] < (*scrollPos + *cursorPos))
        gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]--;
    LoadBagItemListBuffers(gBagPositionStruct.pocket);
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
    sub_80D4FC8(1);
    CreatePocketSwitchArrowPair();
    gTasks[taskId].func = Task_BagMenu_HandleInput;
}

void OpenContextMenu(u8 unused)
{
    switch (gBagPositionStruct.location)
    {
        case ITEMMENULOCATION_BATTLE:
        case ITEMMENULOCATION_WALLY:
            if (ItemId_GetBattleUsage(gSpecialVar_ItemId))
            {
                gBagMenu->contextMenuItemsPtr = sContextMenuItems_BattleUse;
                gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_BattleUse);
            }
            else
            {
                gBagMenu->contextMenuItemsPtr = sContextMenuItems_Cancel;
                gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_Cancel);
            }
            break;
        case ITEMMENULOCATION_BERRY_BLENDER_CRUSH:
            gBagMenu->contextMenuItemsPtr = sContextMenuItems_BerryBlenderCrush;
            gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_BerryBlenderCrush);
            break;
        case ITEMMENULOCATION_APPRENTICE:
            if (!ItemId_GetImportance(gSpecialVar_ItemId) && gSpecialVar_ItemId != ITEM_ENIGMA_BERRY)
            {
                gBagMenu->contextMenuItemsPtr = sContextMenuItems_Apprentice;
                gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_Apprentice);
            }
            else
            {
                gBagMenu->contextMenuItemsPtr = sContextMenuItems_Cancel;
                gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_Cancel);
            }
            break;
        case ITEMMENULOCATION_FAVOR_LADY:
            if (!ItemId_GetImportance(gSpecialVar_ItemId) && gSpecialVar_ItemId != ITEM_ENIGMA_BERRY)
            {
                gBagMenu->contextMenuItemsPtr = sContextMenuItems_FavorLady;
                gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_FavorLady);
            }
            else
            {
                gBagMenu->contextMenuItemsPtr = sContextMenuItems_Cancel;
                gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_Cancel);
            }
            break;
        case ITEMMENULOCATION_QUIZ_LADY:
            if (!ItemId_GetImportance(gSpecialVar_ItemId) && gSpecialVar_ItemId != ITEM_ENIGMA_BERRY)
            {
                gBagMenu->contextMenuItemsPtr = sContextMenuItems_QuizLady;
                gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_QuizLady);
            }
            else
            {
                gBagMenu->contextMenuItemsPtr = sContextMenuItems_Cancel;
                gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_Cancel);
            }
            break;
        case ITEMMENULOCATION_FOSSIL_SCIENTIST:
            if (!ItemId_GetImportance(gSpecialVar_ItemId) && gSpecialVar_ItemId != ITEM_ENIGMA_BERRY)
            {
                gBagMenu->contextMenuItemsPtr = sContextMenuItems_FossilScientist;
                gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_FossilScientist);
            }
            else
            {
                gBagMenu->contextMenuItemsPtr = sContextMenuItems_Cancel;
                gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_Cancel);
            }
            break;
        case ITEMMENULOCATION_PARTY:
        case ITEMMENULOCATION_SHOP:
        case ITEMMENULOCATION_BERRY_TREE:
        case ITEMMENULOCATION_ITEMPC:
        default:
            if (MenuHelpers_LinkSomething() == TRUE || InUnionRoom() == TRUE)
            {
                if (gBagPositionStruct.pocket == KEYITEMS_POCKET || !sub_8122148(gSpecialVar_ItemId))
                {
                    gBagMenu->contextMenuItemsPtr = sContextMenuItems_Cancel;
                    gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_Cancel);
                }
                else
                {
                    gBagMenu->contextMenuItemsPtr = sContextMenuItems_Give;
                    gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_Give);
                }
            }
            else
            {
                switch (gBagPositionStruct.pocket)
                {
                    case ITEMS_POCKET:
                        gBagMenu->contextMenuItemsPtr = gBagMenu->contextMenuItemsBuffer;
                        gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_ItemsPocket);
                        memcpy(&gBagMenu->contextMenuItemsBuffer, &sContextMenuItems_ItemsPocket, sizeof(sContextMenuItems_ItemsPocket));
                        if (ItemIsMail(gSpecialVar_ItemId) == TRUE)
                            gBagMenu->contextMenuItemsBuffer[0] = ITEMMENUACTION_CHECK;
                        break;
                    case KEYITEMS_POCKET:
                        gBagMenu->contextMenuItemsPtr = gBagMenu->contextMenuItemsBuffer;
                        
                        if (sRegisterSubMenu == FALSE)
                        {
                            gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_KeyItemsPocket);
                            memcpy(&gBagMenu->contextMenuItemsBuffer, &sContextMenuItems_KeyItemsPocket, sizeof(sContextMenuItems_KeyItemsPocket));
                            
                            // check replacing USE with WALK
                            if (gSpecialVar_ItemId == ITEM_MACH_BIKE || gSpecialVar_ItemId == ITEM_ACRO_BIKE)
                            {
                                if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
                                    gBagMenu->contextMenuItemsBuffer[0] = ITEMMENUACTION_WALK;
                            }
                        }
                        else
                        {
                            gBagMenu->contextMenuNumItems = NELEMS(sContextMenu_RegisterKeyItem);
                            memcpy(&gBagMenu->contextMenuItemsBuffer, &sContextMenu_RegisterKeyItem, sizeof(sContextMenu_RegisterKeyItem));
                            sRegisterSubMenu = FALSE;
                        }
                        
                        if (gSaveBlock1Ptr->registeredItemSelect == gSpecialVar_ItemId)
                            gBagMenu->contextMenuItemsBuffer[1] = ITEMMENUACTION_DESELECT;
                        else if (gSaveBlock1Ptr->registeredItemL == gSpecialVar_ItemId)
                            gBagMenu->contextMenuItemsBuffer[1] = ITEMMENUACTION_DESELECT;
                        else if (gSaveBlock1Ptr->registeredItemR == gSpecialVar_ItemId)
                            gBagMenu->contextMenuItemsBuffer[1] = ITEMMENUACTION_DESELECT;
                        
                        break;
                    case BALLS_POCKET:
                        gBagMenu->contextMenuItemsPtr = sContextMenuItems_BallsPocket;
                        gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_BallsPocket);
                        break;
                    case TMHM_POCKET:
                        gBagMenu->contextMenuItemsPtr = sContextMenuItems_TmHmPocket;
                        gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_TmHmPocket);
                        break;
                    case BERRIES_POCKET:
                        gBagMenu->contextMenuItemsPtr = sContextMenuItems_BerriesPocket;
                        gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_BerriesPocket);
                        break;
                    case MEDICINE_POCKET:
                        gBagMenu->contextMenuItemsPtr = sContextMenuItems_ItemsPocket;
                        gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_MedicinePocket);
                        break;
                    case COMPETITIVE_POCKET:
                        gBagMenu->contextMenuItemsPtr = sContextMenuItems_ItemsPocket;
                        gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_CompetitivePocket);
                        break;
                    case TRAINING_POCKET:
                        gBagMenu->contextMenuItemsPtr = sContextMenuItems_ItemsPocket;
                        gBagMenu->contextMenuNumItems = ARRAY_COUNT(sContextMenuItems_TrainingPocket);
                        break;
                }
            }
    }
    if (gBagPositionStruct.pocket == TMHM_POCKET)
    {
        ClearWindowTilemap(1);
        PrintTMHMMoveData(gSpecialVar_ItemId);
        PutWindowTilemap(3);
        PutWindowTilemap(4);
        ScheduleBgCopyTilemapToVram(0);
    }
    else
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_Var1IsSelected);
        FillWindowPixelBuffer(1, PIXEL_FILL(0));
        BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
    }
    if (gBagMenu->contextMenuNumItems == 1)
        sub_81ACAF8(BagMenu_AddWindow(0));
    else if (gBagMenu->contextMenuNumItems == 2)
        sub_81ACAF8(BagMenu_AddWindow(1));
    else if (gBagMenu->contextMenuNumItems == 4)
        sub_81ACB54(BagMenu_AddWindow(2), 2, 2);
    else
        sub_81ACB54(BagMenu_AddWindow(3), 2, 3);
}

void sub_81ACAF8(u8 a)
{
    AddItemMenuActionTextPrinters(a, 7, 8, 1, 0, 16, gBagMenu->contextMenuNumItems, sItemMenuActions, gBagMenu->contextMenuItemsPtr);
    InitMenuInUpperLeftCornerPlaySoundWhenAPressed(a, gBagMenu->contextMenuNumItems, 0);
}

void sub_81ACB54(u8 a, u8 b, u8 c)
{
    sub_8198DBC(a, 7, 8, 1, 0x38, b, c, sItemMenuActions, gBagMenu->contextMenuItemsPtr);
    sub_8199944(a, 0x38, b, c, 0);
}

void Task_ItemContext_FieldOrBattle(u8 taskId)
{
    OpenContextMenu(taskId);
    if (gBagMenu->contextMenuNumItems <= 2)
        gTasks[taskId].func = Task_HandleInBattleItemMenuInput;
    else
        gTasks[taskId].func = Task_HandleOutOfBattleItemMenuInput;
}

void Task_HandleInBattleItemMenuInput(u8 taskId)
{
    if (MenuHelpers_CallLinkSomething() != TRUE)
    {
        s8 selection = Menu_ProcessInputNoWrap();
        switch (selection)
        {
            case MENU_NOTHING_CHOSEN:
                break;
            case MENU_B_PRESSED:
                PlaySE(SE_SELECT);
                sItemMenuActions[ITEMMENUACTION_CANCEL].func.void_u8(taskId);
                break;
            default:
                PlaySE(SE_SELECT);
                sItemMenuActions[gBagMenu->contextMenuItemsPtr[selection]].func.void_u8(taskId);
                break;
        }
    }
}

void Task_HandleOutOfBattleItemMenuInput(u8 taskId)
{
    if (MenuHelpers_CallLinkSomething() != TRUE)
    {
        s8 cursorPos = Menu_GetCursorPos();
        if (JOY_NEW(DPAD_UP))
        {
            if (cursorPos > 0 && sub_81ACDFC(cursorPos - 2))
            {
                PlaySE(SE_SELECT);
                ChangeListMenuCursorPosition(MENU_CURSOR_DELTA_NONE, MENU_CURSOR_DELTA_UP);
            }
        }
        else if (JOY_NEW(DPAD_DOWN))
        {
            if (cursorPos < (gBagMenu->contextMenuNumItems - 2) && sub_81ACDFC(cursorPos + 2))
            {
                PlaySE(SE_SELECT);
                ChangeListMenuCursorPosition(MENU_CURSOR_DELTA_NONE, MENU_CURSOR_DELTA_DOWN);
            }
        }
        else if (JOY_NEW(DPAD_LEFT))
        {
            if ((cursorPos & 1) && sub_81ACDFC(cursorPos - 1))
            {
                PlaySE(SE_SELECT);
                ChangeListMenuCursorPosition(MENU_CURSOR_DELTA_LEFT, MENU_CURSOR_DELTA_NONE);
            }
        }
        else if (JOY_NEW(DPAD_RIGHT))
        {
            if (!(cursorPos & 1) && sub_81ACDFC(cursorPos + 1))
            {
                PlaySE(SE_SELECT);
                ChangeListMenuCursorPosition(MENU_CURSOR_DELTA_RIGHT, MENU_CURSOR_DELTA_NONE);
            }
        }
        else if (JOY_NEW(A_BUTTON))
        {
            PlaySE(SE_SELECT);
            sItemMenuActions[gBagMenu->contextMenuItemsPtr[cursorPos]].func.void_u8(taskId);
        }
        else if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_SELECT);
            sItemMenuActions[ITEMMENUACTION_CANCEL].func.void_u8(taskId);
        }
    }
}

bool8 sub_81ACDFC(s8 a)
{
    if (a < 0)
        return FALSE;
    if (a > gBagMenu->contextMenuNumItems)
        return FALSE;
    if (gBagMenu->contextMenuItemsPtr[a] == ITEMMENUACTION_DUMMY)
        return FALSE;
    return TRUE;
}

void BagMenu_RemoveSomeWindow(void)
{
    if (gBagMenu->contextMenuNumItems == 1)
        BagMenu_RemoveWindow(0);
    else if (gBagMenu->contextMenuNumItems == 2)
    {
        BagMenu_RemoveWindow(1);
    }
    else if (gBagMenu->contextMenuNumItems == 4)
    {
        BagMenu_RemoveWindow(2);
    }
    else
        BagMenu_RemoveWindow(3);
}

void ItemMenu_UseOutOfBattle(u8 taskId)
{
    if (ItemId_GetFieldFunc(gSpecialVar_ItemId))
    {
        BagMenu_RemoveSomeWindow();
        if (CalculatePlayerPartyCount() == 0 && ItemId_GetType(gSpecialVar_ItemId) == ITEM_USE_PARTY_MENU)
            BagMenu_PrintThereIsNoPokemon(taskId);
        else
        {
            FillWindowPixelBuffer(1, PIXEL_FILL(0));
            ScheduleBgCopyTilemapToVram(0);
            if (gBagPositionStruct.pocket != BERRIES_POCKET)
                ItemId_GetFieldFunc(gSpecialVar_ItemId)(taskId);
            else
                ItemUseOutOfBattle_Berry(taskId);
        }
    }
}

void ItemMenu_Toss(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    BagMenu_RemoveSomeWindow();
    tItemCount = 1;
    if (data[2] == 1)
    {
        BagMenu_TossItems(taskId);
    }
    else
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_TossHowManyVar1s);
        FillWindowPixelBuffer(1, PIXEL_FILL(0));
        BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
        sub_81ABC3C(7);
        gTasks[taskId].func = Task_ChooseHowManyToToss;
    }
}

void BagMenu_TossItems(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    CopyItemName(gSpecialVar_ItemId, gStringVar1);
    ConvertIntToDecimalStringN(gStringVar2, tItemCount, STR_CONV_MODE_LEFT_ALIGN, MAX_ITEM_DIGITS);
    StringExpandPlaceholders(gStringVar4, gText_ConfirmTossItems);
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
    BagMenu_YesNo(taskId, 5, &sYesNoTossFunctions);
}

void BagMenu_CancelToss(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    BagMenu_PrintDescription(data[1]);
    BagMenu_PrintCursor_(data[0], 0);
    set_callback3_to_bag(taskId);
}

void Task_ChooseHowManyToToss(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&tItemCount, data[2]) == TRUE)
    {
        PrintItemDepositAmount(gBagMenu->windowPointers[7], tItemCount);
    }
    else if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        BagMenu_RemoveWindow(7);
        BagMenu_TossItems(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BagMenu_RemoveWindow(7);
        BagMenu_CancelToss(taskId);
    }
}

void BagMenu_ConfirmToss(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    CopyItemName(gSpecialVar_ItemId, gStringVar1);
    ConvertIntToDecimalStringN(gStringVar2, tItemCount, STR_CONV_MODE_LEFT_ALIGN, MAX_ITEM_DIGITS);
    StringExpandPlaceholders(gStringVar4, gText_ThrewAwayVar2Var1s);
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
    gTasks[taskId].func = Task_ActuallyToss;
}

void Task_ActuallyToss(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];

    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        RemoveBagItem(gSpecialVar_ItemId, tItemCount);
        DestroyListMenuTask(data[0], scrollPos, cursorPos);
        UpdatePocketItemList(gBagPositionStruct.pocket);
        SetInitialScrollAndCursorPositions(gBagPositionStruct.pocket);
        LoadBagItemListBuffers(gBagPositionStruct.pocket);
        data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
        ScheduleBgCopyTilemapToVram(0);
        set_callback3_to_bag(taskId);
    }
}

void ItemMenu_Give(u8 taskId)
{
    BagMenu_RemoveSomeWindow();
    if (!itemid_80BF6D8_mail_related(gSpecialVar_ItemId))
    {
        DisplayItemMessage(taskId, 1, gText_CantWriteMail, sub_81AD350);
    }
    else if (!ItemId_GetImportance(gSpecialVar_ItemId))
    {
        if (CalculatePlayerPartyCount() == 0)
            BagMenu_PrintThereIsNoPokemon(taskId);
        else
        {
            gBagMenu->exitCallback = CB2_ChooseMonToGiveItem;
            Task_FadeAndCloseBagMenu(taskId);
        }
    }
    else
    {
        BagMenu_PrintItemCantBeHeld(taskId);
    }
}

void BagMenu_PrintThereIsNoPokemon(u8 taskId)
{
    DisplayItemMessage(taskId, 1, gText_NoPokemon, sub_81AD350);
}

static void BagMenu_PrintItemCantBeHeld(u8 taskId)
{
    CopyItemName(gSpecialVar_ItemId, gStringVar1);
    StringExpandPlaceholders(gStringVar4, gText_Var1CantBeHeld);
    DisplayItemMessage(taskId, 1, gStringVar4, sub_81AD350);
}

void sub_81AD350(u8 taskId)
{
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        BagMenu_InitListsMenu(taskId);
    }
}

void ItemMenu_CheckTag(u8 taskId)
{
    gBagMenu->exitCallback = DoBerryTagScreen;
    Task_FadeAndCloseBagMenu(taskId);
}

void ItemMenu_Cancel(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    
    sRegisterSubMenu = FALSE;
    
    BagMenu_RemoveSomeWindow();
    BagMenu_PrintDescription(data[1]);
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);
    BagMenu_PrintCursor_(data[0], 0);
    set_callback3_to_bag(taskId);
}

void ItemMenu_UseInBattle(u8 taskId)
{
    if (ItemId_GetBattleFunc(gSpecialVar_ItemId))
    {
        BagMenu_RemoveSomeWindow();
        ItemId_GetBattleFunc(gSpecialVar_ItemId)(taskId);
    }
}

void CB2_ReturnToBagMenuPocket(void)
{
    GoToBagMenu(ITEMMENULOCATION_LAST, POCKETS_COUNT, NULL);
}

void Task_ItemContext_FieldGive(u8 taskId)
{
    if (!itemid_80BF6D8_mail_related(gSpecialVar_ItemId))
    {
        DisplayItemMessage(taskId, 1, gText_CantWriteMail, sub_81AD350);
    }
    else if (!sub_8122148(gSpecialVar_ItemId))
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_Var1CantBeHeldHere);
        DisplayItemMessage(taskId, 1, gStringVar4, sub_81AD350);
    }
    else if (gBagPositionStruct.pocket != KEYITEMS_POCKET && !ItemId_GetImportance(gSpecialVar_ItemId))
    {
        Task_FadeAndCloseBagMenu(taskId);
    }
    else
    {
        BagMenu_PrintItemCantBeHeld(taskId);
    }
}

void Task_ItemContext_ItemPC_2(u8 taskId)
{
    if (ItemIsMail(gSpecialVar_ItemId) == TRUE)
        DisplayItemMessage(taskId, 1, gText_CantWriteMail, sub_81AD350);
    else if (gBagPositionStruct.pocket != KEYITEMS_POCKET && !ItemId_GetImportance(gSpecialVar_ItemId))
        gTasks[taskId].func = Task_FadeAndCloseBagMenu;
    else
        BagMenu_PrintItemCantBeHeld(taskId);
}

void Task_ItemContext_Sell(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (ItemId_GetPrice(gSpecialVar_ItemId) == 0)
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar2);
        StringExpandPlaceholders(gStringVar4, gText_CantBuyKeyItem);
        DisplayItemMessage(taskId, 1, gStringVar4, BagMenu_InitListsMenu);
    }
    else
    {
        tItemCount = 1;
        if (data[2] == 1)
        {
            DisplayCurrentMoneyWindow();
            DisplaySellItemPriceAndConfirm(taskId);
        }
        else
        {
            CopyItemName(gSpecialVar_ItemId, gStringVar2);
            StringExpandPlaceholders(gStringVar4, gText_HowManyToSell);
            DisplayItemMessage(taskId, 1, gStringVar4, sub_81AD730);
        }
    }
}

static void DisplaySellItemPriceAndConfirm(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    ConvertIntToDecimalStringN(gStringVar1, (ItemId_GetPrice(gSpecialVar_ItemId) / 2) * tItemCount, STR_CONV_MODE_LEFT_ALIGN, 6);
    StringExpandPlaceholders(gStringVar4, gText_ICanPayVar1);
    DisplayItemMessage(taskId, 1, gStringVar4, sub_81AD6E4);
}

void sub_81AD6E4(u8 taskId)
{
    BagMenu_YesNo(taskId, 6, &sYesNoSellItemFunctions);
}

void BagMenu_CancelSell(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    RemoveMoneyWindow();
    BagMenu_RemoveBagItemMessageindow(4);
    BagMenu_PrintCursor_(data[0], 0);
    set_callback3_to_bag(taskId);
}

void sub_81AD730(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u8 windowId = BagMenu_AddWindow(8);

    PrintItemSoldAmount(windowId, 1, (ItemId_GetPrice(gSpecialVar_ItemId) / 2) * tItemCount);
    DisplayCurrentMoneyWindow();
    gTasks[taskId].func = Task_SellHowManyDialogueHandleInput;
}

static void Task_SellHowManyDialogueHandleInput(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&tItemCount, data[2]) == TRUE)
    {
        PrintItemSoldAmount(gBagMenu->windowPointers[8], tItemCount, (ItemId_GetPrice(gSpecialVar_ItemId) / 2) * tItemCount);
    }
    else if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        BagMenu_RemoveWindow(8);
        DisplaySellItemPriceAndConfirm(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BagMenu_PrintCursor_(data[0], 0);
        RemoveMoneyWindow();
        BagMenu_RemoveWindow(8);
        BagMenu_RemoveBagItemMessageindow(4);
        set_callback3_to_bag(taskId);
    }
}

void BagMenu_ConfirmSell(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    CopyItemName(gSpecialVar_ItemId, gStringVar2);
    ConvertIntToDecimalStringN(gStringVar1, (ItemId_GetPrice(gSpecialVar_ItemId) / 2) * tItemCount, STR_CONV_MODE_LEFT_ALIGN, 6);
    StringExpandPlaceholders(gStringVar4, gText_TurnedOverVar1ForVar2);
    DisplayItemMessage(taskId, 1, gStringVar4, BagMenu_Sell_UpdateItemListAndMoney);
}

static void BagMenu_Sell_UpdateItemListAndMoney(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];

    PlaySE(SE_SHOP);
    RemoveBagItem(gSpecialVar_ItemId, tItemCount);
    AddMoney(&gSaveBlock1Ptr->money, (ItemId_GetPrice(gSpecialVar_ItemId) / 2) * tItemCount);
    DestroyListMenuTask(data[0], scrollPos, cursorPos);
    UpdatePocketItemList(gBagPositionStruct.pocket);
    SetInitialScrollAndCursorPositions(gBagPositionStruct.pocket);
    LoadBagItemListBuffers(gBagPositionStruct.pocket);
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
    BagMenu_PrintCursor_(data[0], 2);
    PrintMoneyAmountInMoneyBox(gBagMenu->windowPointers[9], GetMoney(&gSaveBlock1Ptr->money), 0);
    gTasks[taskId].func = BagMenu_Sell_WaitForABPress;
}

static void BagMenu_Sell_WaitForABPress(u8 taskId)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        RemoveMoneyWindow();
        BagMenu_InitListsMenu(taskId);
    }
}

void Task_ItemContext_Deposit(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    tItemCount = 1;
    if (data[2] == 1)
    {
        BagMenu_TryDepositItem(taskId);
    }
    else
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_DepositHowManyVar1);
        FillWindowPixelBuffer(1, PIXEL_FILL(0));
        BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
        sub_81ABC3C(7);
        gTasks[taskId].func = Task_ChooseHowManyToDeposit;
    }
}

static void Task_ChooseHowManyToDeposit(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&tItemCount, data[2]) == TRUE)
    {
        PrintItemDepositAmount(gBagMenu->windowPointers[7], tItemCount);
    }
    else if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        BagMenu_RemoveWindow(7);
        BagMenu_TryDepositItem(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BagMenu_PrintDescription(data[1]);
        BagMenu_PrintCursor_(data[0], 0);
        BagMenu_RemoveWindow(7);
        set_callback3_to_bag(taskId);
    }
}

static void BagMenu_TryDepositItem(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    if (ItemId_GetImportance(gSpecialVar_ItemId))
    {
        BagMenu_Print(1, 1, gText_CantStoreImportantItems, 3, 1, 0, 0, 0, 0);
        gTasks[taskId].func = BagMenu_Deposit_WaitForABPress;
    }
    else if (AddPCItem(gSpecialVar_ItemId, tItemCount) == TRUE)
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar1);
        ConvertIntToDecimalStringN(gStringVar2, tItemCount, STR_CONV_MODE_LEFT_ALIGN, MAX_ITEM_DIGITS);
        StringExpandPlaceholders(gStringVar4, gText_DepositedVar2Var1s);
        BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
        gTasks[taskId].func = Task_ActuallyToss;
    }
    else
    {
        BagMenu_Print(1, 1, gText_NoRoomForItems, 3, 1, 0, 0, 0, 0);
        gTasks[taskId].func = BagMenu_Deposit_WaitForABPress;
    }
}

static void BagMenu_Deposit_WaitForABPress(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BagMenu_PrintDescription(data[1]);
        BagMenu_PrintCursor_(data[0], 0);
        set_callback3_to_bag(taskId);
    }
}

bool8 IsWallysBag(void)
{
    if (gBagPositionStruct.location == 10)
        return TRUE;
    return FALSE;
}

void PrepareBagForWallyTutorial(void)
{
    u32 i;

    sTempWallyBag = AllocZeroed(sizeof(struct TempWallyStruct));
    memcpy(sTempWallyBag->bagPocket_Medicine, gSaveBlock1Ptr->bagPocket_Medicine, sizeof(gSaveBlock1Ptr->bagPocket_Medicine));
    memcpy(sTempWallyBag->bagPocket_PokeBalls, gSaveBlock1Ptr->bagPocket_PokeBalls, sizeof(gSaveBlock1Ptr->bagPocket_PokeBalls));
    sTempWallyBag->pocket = gBagPositionStruct.pocket;
    for (i = 0; i <= 4; i++)
    {
        sTempWallyBag->cursorPosition[i] = gBagPositionStruct.cursorPosition[i];
        sTempWallyBag->scrollPosition[i] = gBagPositionStruct.scrollPosition[i];
    }
    ClearItemSlots(gSaveBlock1Ptr->bagPocket_Medicine, BAG_MEDICINE_COUNT);
    ClearItemSlots(gSaveBlock1Ptr->bagPocket_PokeBalls, BAG_POKEBALLS_COUNT);
    ResetBagScrollPositions();
}

void RestoreBagAfterWallyTutorial(void)
{
    u32 i;

    memcpy(gSaveBlock1Ptr->bagPocket_Medicine, sTempWallyBag->bagPocket_Medicine, sizeof(sTempWallyBag->bagPocket_Medicine));
    memcpy(gSaveBlock1Ptr->bagPocket_PokeBalls, sTempWallyBag->bagPocket_PokeBalls, sizeof(sTempWallyBag->bagPocket_PokeBalls));
    gBagPositionStruct.pocket = sTempWallyBag->pocket;
    for (i = 0; i <= 4; i++)
    {
        gBagPositionStruct.cursorPosition[i] = sTempWallyBag->cursorPosition[i];
        gBagPositionStruct.scrollPosition[i] = sTempWallyBag->scrollPosition[i];
    }
    Free(sTempWallyBag);
}

void DoWallyTutorialBagMenu(void)
{
    PrepareBagForWallyTutorial();
    AddBagItem(ITEM_POTION, 1);
    AddBagItem(ITEM_POKE_BALL, 1);
    GoToBagMenu(ITEMMENULOCATION_WALLY, MEDICINE_POCKET, CB2_SetUpReshowBattleScreenAfterMenu2);
}

void Task_WallyTutorialBagMenu(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        switch (data[8])
        {
            case 0x66:
                PlaySE(SE_SELECT);
                SwitchBagPocket(taskId, MENU_CURSOR_DELTA_RIGHT, 0);
                data[8]++;
                break;
            case 0xCC:
                PlaySE(SE_SELECT);
                BagMenu_PrintCursor_(data[0], 2);
                gSpecialVar_ItemId = ITEM_POKE_BALL;
                OpenContextMenu(taskId);
                data[8]++;
                break;
            case 0x132:
                PlaySE(SE_SELECT);
                BagMenu_RemoveSomeWindow();
                DestroyListMenuTask(data[0], 0, 0);
                RestoreBagAfterWallyTutorial();
                Task_FadeAndCloseBagMenu(taskId);
                break;
            default:
                data[8]++;
                break;
        }
    }
}

#undef tItemCount

void unknown_ItemMenu_Show(u8 taskId)
{
    gSpecialVar_0x8005 = gSpecialVar_ItemId;
    gSpecialVar_Result = 1;
    BagMenu_RemoveSomeWindow();
    Task_FadeAndCloseBagMenu(taskId);
}

void CB2_ApprenticeExitBagMenu(void)
{
    gFieldCallback = Apprentice_EnableBothScriptContexts;
    SetMainCallback2(CB2_ReturnToField);
}

void unknown_ItemMenu_Give2(u8 taskId)
{
    RemoveBagItem(gSpecialVar_ItemId, 1);
    gSpecialVar_Result = 1;
    BagMenu_RemoveSomeWindow();
    Task_FadeAndCloseBagMenu(taskId);
}

void CB2_FavorLadyExitBagMenu(void)
{
    gFieldCallback = FieldCallback_FavorLadyEnableScriptContexts;
    SetMainCallback2(CB2_ReturnToField);
}

void CB2_FossilScientistExitBagMenu(void)
{
    gFieldCallback = FieldCallback_FavorLadyEnableScriptContexts; // Simply enables both script contexts
    SetMainCallback2(CB2_ReturnToField);
}

void unknown_ItemMenu_Confirm2(u8 taskId)
{
    gSpecialVar_Result = 1;
    BagMenu_RemoveSomeWindow();
    Task_FadeAndCloseBagMenu(taskId);
}

void CB2_QuizLadyExitBagMenu(void)
{
    gFieldCallback = FieldCallback_QuizLadyEnableScriptContexts;
    SetMainCallback2(CB2_ReturnToField);
}

void BagMenu_PrintPocketNames(const u8 *pocketName1, const u8 *pocketName2)
{
    struct WindowTemplate window = {0, 0, 0, 0, 0, 0, 0};
    u16 windowId;
    int offset;

    window.width = 16;
    window.height = 2;
    windowId = AddWindow(&window);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(0));
    offset = GetStringCenterAlignXOffset(1, pocketName1, 0x40);
    BagMenu_Print(windowId, 1, pocketName1, offset, 1, 0, 0, -1, 1);
    if (pocketName2)
    {
        offset = GetStringCenterAlignXOffset(1, pocketName2, 0x40);
        BagMenu_Print(windowId, 1, pocketName2, offset + 0x40, 1, 0, 0, -1, 1);
    }
    CpuCopy32((u8*)GetWindowAttribute(windowId, WINDOW_TILE_DATA), gBagMenu->pocketNameBuffer, 0x400);
    RemoveWindow(windowId);
}

void BagMenu_CopyPocketNameToWindow(u32 a)
{
    u8 (* r4)[32][32];
    u8* windowAttribute;
    int b;
    if (a > 8)
        a = 8;
    r4 = &gBagMenu->pocketNameBuffer;
    windowAttribute = (u8*)GetWindowAttribute(2, WINDOW_TILE_DATA);
    CpuCopy32(r4[0][a], windowAttribute, 0x100);
    b = a + 16;
    CpuCopy32(r4[0][b], windowAttribute + 0x100, 0x100);
    CopyWindowToVram(2, 2);
}

void SetupBagMenu_Textboxes(void)
{
    u8 i;

    InitWindows(sDefaultBagWindows);
    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(0, 1, 0xE0);
    LoadMessageBoxGfx(0, 10, 0xD0);
    ListMenuLoadStdPalAt(0xC0, 1);
    LoadPalette(&gUnknown_0860F074, 0xF0, 0x20);
    for (i = 0; i < 3; i++)
    {
        FillWindowPixelBuffer(i, PIXEL_FILL(0));
        PutWindowTilemap(i);
    }
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);
}

void BagMenu_Print(u8 windowId, u8 fontId, const u8 *str, u8 left, u8 top, u8 letterSpacing, u8 lineSpacing, u8 speed, u8 colorIndex)
{
    AddTextPrinterParameterized4(windowId, fontId, left, top, letterSpacing, lineSpacing, sFontColorTable[colorIndex], speed, str);
}

//Unused
u8 sub_81AE124(u8 which)
{
    return gBagMenu->windowPointers[which];
}

u8 BagMenu_AddWindow(u8 which)
{
    u8 *ptr = &gBagMenu->windowPointers[which];
    if (*ptr == 0xFF)
    {
        *ptr = AddWindow(&sContextMenuWindowTemplates[which]);
        DrawStdFrameWithCustomTileAndPalette(*ptr, 0, 1, 14);
        ScheduleBgCopyTilemapToVram(1);
    }
    return *ptr;
}

void BagMenu_RemoveWindow(u8 which)
{
    u8 *ptr = &gBagMenu->windowPointers[which];
    if (*ptr != 0xFF)
    {
        ClearStdWindowAndFrameToTransparent(*ptr, FALSE);
        ClearWindowTilemap(*ptr);
        RemoveWindow(*ptr);
        ScheduleBgCopyTilemapToVram(1);
        *ptr = 0xFF;
    }
}

u8 AddItemMessageWindow(u8 which)
{
    u8 *ptr = &gBagMenu->windowPointers[which];
    if (*ptr == 0xFF)
        *ptr = AddWindow(&sContextMenuWindowTemplates[which]);
    return *ptr;
}

void BagMenu_RemoveBagItemMessageindow(u8 which)
{
    u8 *ptr = &gBagMenu->windowPointers[which];
    if (*ptr != 0xFF)
    {
        ClearDialogWindowAndFrameToTransparent(*ptr, FALSE);
        // This ClearWindowTilemap call is redundant, since ClearDialogWindowAndFrameToTransparent already calls it.
        ClearWindowTilemap(*ptr);
        RemoveWindow(*ptr);
        ScheduleBgCopyTilemapToVram(1);
        *ptr = 0xFF;
    }
}

void BagMenu_YesNo(u8 a, u8 b, const struct YesNoFuncTable *funcTable)
{
    CreateYesNoMenuWithCallbacks(a, &sContextMenuWindowTemplates[b], 1, 0, 2, 1, 14, funcTable);
}

static void DisplayCurrentMoneyWindow(void)
{
    u8 windowId = BagMenu_AddWindow(9);
    PrintMoneyAmountInMoneyBoxWithBorder(windowId, 1, 14, GetMoney(&gSaveBlock1Ptr->money));
    AddMoneyLabelObject(19, 11);
}

static void RemoveMoneyWindow(void)
{
    BagMenu_RemoveWindow(9);
    RemoveMoneyLabelObject();
}

void BagMenu_PrepareTMHMMoveWindow(void)
{
    FillWindowPixelBuffer(3, PIXEL_FILL(0));
    BlitMenuInfoIcon(3, MENU_INFO_ICON_TYPE, 0, 0);
    BlitMenuInfoIcon(3, MENU_INFO_ICON_POWER, 0, 12);
    BlitMenuInfoIcon(3, MENU_INFO_ICON_ACCURACY, 0, 24);
    BlitMenuInfoIcon(3, MENU_INFO_ICON_PP, 0, 36);
    CopyWindowToVram(3, 2);
}

void PrintTMHMMoveData(u16 itemId)
{
    u8 i;
    u16 moveId;
    const u8* text;

    FillWindowPixelBuffer(4, PIXEL_FILL(0));
    if (itemId == ITEM_NONE)
    {
        for (i = 0; i < 4; i++)
            BagMenu_Print(4, 1, gText_ThreeDashes, 7, i * 12, 0, 0, -1, 4);
        CopyWindowToVram(4, 2);
    }
    else
    {
        moveId = ItemIdToBattleMoveId(itemId);
        BlitMenuInfoIcon(4, gBattleMoves[moveId].type + 1, 0, 0);
        if (gBattleMoves[moveId].power <= 1)
        {
            text = gText_ThreeDashes;
        }
        else
        {
            ConvertIntToDecimalStringN(gStringVar1, gBattleMoves[moveId].power, STR_CONV_MODE_RIGHT_ALIGN, 3);
            text = gStringVar1;
        }
        BagMenu_Print(4, 1, text, 7, 12, 0, 0, -1, 4);
        if (gBattleMoves[moveId].accuracy == 0)
        {
            text = gText_ThreeDashes;
        }
        else
        {
            ConvertIntToDecimalStringN(gStringVar1, gBattleMoves[moveId].accuracy, STR_CONV_MODE_RIGHT_ALIGN, 3);
            text = gStringVar1;
        }
        BagMenu_Print(4, 1, text, 7, 24, 0, 0, -1, 4);
        ConvertIntToDecimalStringN(gStringVar1, gBattleMoves[moveId].pp, STR_CONV_MODE_RIGHT_ALIGN, 3);
        BagMenu_Print(4, 1, gStringVar1, 7, 36, 0, 0, -1, 4);
        CopyWindowToVram(4, 2);
    }
}

// bag sorting
enum BagSortOptions
{
    SORT_ALPHABETICALLY,
    SORT_BY_TYPE,
    SORT_BY_NUMBER, //by itemID
    SORT_BY_QUANTITY, //greatest->least
};
enum ItemSortType
{
    // Item Types
	ITEM_TYPE_HELD_ITEM,
	ITEM_TYPE_FLUTE,
	ITEM_TYPE_FIELD_USE,
	ITEM_TYPE_BATTLE_X_ITEM,
    ITEM_TYPE_BATTLE_ITEM,
	ITEM_TYPE_SHARD,
    ITEM_TYPE_APRICORN,
	ITEM_TYPE_VALUABLE,
	ITEM_TYPE_FOSSIL,
	ITEM_TYPE_MAIL,

    // Medicine Types
	ITEM_TYPE_MEDICINE_HP_RECOVERY,
    ITEM_TYPE_MEDICINE_STATUS_RECOVERY,
    ITEM_TYPE_MEDICINE_FAINTED_RECOVERY,
    ITEM_TYPE_MEDICINE_PP_RECOVERY,
    ITEM_TYPE_DRINK_HP_RECOVERY,
    ITEM_TYPE_HERB_HP_RECOVERY,
    ITEM_TYPE_HERB_STATUS_RECOVERY,
    ITEM_TYPE_HERB_FAINTED_RECOVERY,
    ITEM_TYPE_TREAT_STATUS_RECOVERY,
    ITEM_TYPE_SPECIAL_FAINTED_RECOVERY,

    // Poke Ball Types
    ITEM_TYPE_BALL_KANTO,
    ITEM_TYPE_BALL_HOENN,
    ITEM_TYPE_BALL_SINNOH,
    ITEM_TYPE_BALL_JOHTO,
    ITEM_TYPE_BALL_SPECIAL,

    // Competitive Item Types
    ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    ITEM_TYPE_HELD_ITEM_CONTEST,
	ITEM_TYPE_HELD_ITEM_GEM,
    ITEM_TYPE_HELD_ITEM_SPECIES,
	ITEM_TYPE_HELD_ITEM_DRIVE,
	ITEM_TYPE_HELD_ITEM_PLATE,
	ITEM_TYPE_HELD_ITEM_MEMORY,
    ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    ITEM_TYPE_HELD_ITEM_Z_CRYSTAL,

    // Training Item Types
    ITEM_TYPE_HELD_ITEM_TRAINING,
    ITEM_TYPE_HELD_ITEM_BREEDING,
    ITEM_TYPE_HELD_ITEM_EV_TRAINING,
    ITEM_TYPE_CANDY,
	ITEM_TYPE_EV_VITAMIN,
	ITEM_TYPE_EV_WING,
	ITEM_TYPE_EVOLUTION_STONE,
	ITEM_TYPE_HELD_ITEM_EVOLUTION,
	ITEM_TYPE_HELD_ITEM_INCENSE,

    // Berry Types
    ITEM_TYPE_BERRY_HP_RECOVERY,
    ITEM_TYPE_BERRY_STATUS_RECOVERY,
    ITEM_TYPE_BERRY_PP_RECOVERY,
    ITEM_TYPE_BERRY_PINCH_HP_RECOVERY,
    ITEM_TYPE_BERRY_PINCH_STAT_RAISE,
    ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    ITEM_TYPE_BERRY_REDUCE_EV,
    ITEM_TYPE_BERRY_APRICORN,
    ITEM_TYPE_BERRY_SPECIAL,

    // TM/HM Types
    ITEM_TYPE_TECHNICAL_MACHINE,
    ITEM_TYPE_HIDDEN_MACHINE,
    
    // Key Item Types
    ITEM_TYPE_KEY_ITEM_UTILITY,
    ITEM_TYPE_KEY_ITEM_FISHING_ROD,
    ITEM_TYPE_KEY_ITEM_BIKE,
    ITEM_TYPE_KEY_ITEM_CONTAINER,
    ITEM_TYPE_KEY_ITEM_FORM_CHANGE,
    ITEM_TYPE_KEY_ITEM_TRADE,
    ITEM_TYPE_KEY_ITEM_PASSIVE,
    ITEM_TYPE_KEY_ITEM_FRLG,

    ITEM_TYPE_UNKNOWN,
};
static const u8 sText_SortItemsHow[] = _("Sort items how?");
static const u8 sText_Name[] = _("name");
static const u8 sText_Type[] = _("type");
static const u8 sText_Quantity[] = _("quantity");
static const u8 sText_Number[] = _("number");
static const u8 sText_ItemsSorted[] = _("Items sorted by {STR_VAR_1}!");
static const u8 *const sSortTypeStrings[] = 
{
    [SORT_ALPHABETICALLY] = sText_Name,
    [SORT_BY_TYPE] = sText_Type,
    [SORT_BY_NUMBER] = sText_Number,
    [SORT_BY_QUANTITY] = sText_Quantity,
};

static const u8 sBagMenuSortItems[] =
{
    ITEMMENUACTION_BY_NAME,
    ITEMMENUACTION_BY_TYPE,
    ITEMMENUACTION_BY_QUANTITY,
    ITEMMENUACTION_CANCEL,
};

static const u8 sBagMenuSortKeyItems[] =
{
    ITEMMENUACTION_BY_NAME,
    ITEMMENUACTION_BY_TYPE,
    ITEMMENUACTION_DUMMY,
    ITEMMENUACTION_CANCEL,
};

static const u8 sBagMenuSortPokeBalls[] =
{
    ITEMMENUACTION_BY_NAME,
    ITEMMENUACTION_BY_TYPE,
    ITEMMENUACTION_BY_QUANTITY,
    ITEMMENUACTION_CANCEL,
};

static const u8 sBagMenuSortBerries[] =
{
    ITEMMENUACTION_BY_NAME,
    ITEMMENUACTION_DUMMY,
    ITEMMENUACTION_BY_TYPE,
    ITEMMENUACTION_BY_NUMBER,
    ITEMMENUACTION_BY_QUANTITY,
    ITEMMENUACTION_CANCEL,
};

static const u8 sBagMenuSortTMs[] =
{
    ITEMMENUACTION_BY_NAME,
    ITEMMENUACTION_BY_NUMBER,
    ITEMMENUACTION_DUMMY,
    ITEMMENUACTION_CANCEL,
};

static const u16 sItemsByType[ITEMS_COUNT] =
{
    [ITEM_POKE_BALL] = ITEM_TYPE_BALL_KANTO,
    [ITEM_GREAT_BALL] = ITEM_TYPE_BALL_KANTO,
    [ITEM_ULTRA_BALL] = ITEM_TYPE_BALL_KANTO,
    [ITEM_MASTER_BALL] = ITEM_TYPE_BALL_KANTO,

    [ITEM_PREMIER_BALL] = ITEM_TYPE_BALL_HOENN,
    [ITEM_REPEAT_BALL] = ITEM_TYPE_BALL_HOENN,
    [ITEM_TIMER_BALL] = ITEM_TYPE_BALL_HOENN,
    [ITEM_NEST_BALL] = ITEM_TYPE_BALL_HOENN,
    [ITEM_NET_BALL] = ITEM_TYPE_BALL_HOENN,
    [ITEM_DIVE_BALL] = ITEM_TYPE_BALL_HOENN,
    [ITEM_LUXURY_BALL] = ITEM_TYPE_BALL_HOENN,

    [ITEM_DUSK_BALL] = ITEM_TYPE_BALL_SINNOH,
    [ITEM_QUICK_BALL] = ITEM_TYPE_BALL_SINNOH,
    [ITEM_HEAL_BALL] = ITEM_TYPE_BALL_SINNOH,

    [ITEM_LEVEL_BALL] = ITEM_TYPE_BALL_JOHTO,
    [ITEM_LURE_BALL] = ITEM_TYPE_BALL_JOHTO,
    [ITEM_MOON_BALL] = ITEM_TYPE_BALL_JOHTO,
    [ITEM_FRIEND_BALL] = ITEM_TYPE_BALL_JOHTO,
    [ITEM_LOVE_BALL] = ITEM_TYPE_BALL_JOHTO,
    [ITEM_FAST_BALL] = ITEM_TYPE_BALL_JOHTO,
    [ITEM_HEAVY_BALL] = ITEM_TYPE_BALL_JOHTO,

    [ITEM_BEAST_BALL] = ITEM_TYPE_BALL_SPECIAL,
    [ITEM_SAFARI_BALL] = ITEM_TYPE_BALL_SPECIAL,
    [ITEM_SPORT_BALL] = ITEM_TYPE_BALL_SPECIAL,
    [ITEM_PARK_BALL] = ITEM_TYPE_BALL_SPECIAL,
    [ITEM_DREAM_BALL] = ITEM_TYPE_BALL_SPECIAL,
    [ITEM_CHERISH_BALL] = ITEM_TYPE_BALL_SPECIAL,

    [ITEM_POTION] = ITEM_TYPE_MEDICINE_HP_RECOVERY,
    [ITEM_SUPER_POTION] = ITEM_TYPE_MEDICINE_HP_RECOVERY,
    [ITEM_HYPER_POTION] = ITEM_TYPE_MEDICINE_HP_RECOVERY,
    [ITEM_MAX_POTION] = ITEM_TYPE_MEDICINE_HP_RECOVERY,
    [ITEM_FULL_RESTORE] = ITEM_TYPE_MEDICINE_HP_RECOVERY,

    [ITEM_ANTIDOTE] = ITEM_TYPE_MEDICINE_STATUS_RECOVERY,
    [ITEM_AWAKENING] = ITEM_TYPE_MEDICINE_STATUS_RECOVERY,
    [ITEM_PARALYZE_HEAL] = ITEM_TYPE_MEDICINE_STATUS_RECOVERY,
    [ITEM_BURN_HEAL] = ITEM_TYPE_MEDICINE_STATUS_RECOVERY,
    [ITEM_ICE_HEAL] = ITEM_TYPE_MEDICINE_STATUS_RECOVERY,
    [ITEM_FULL_HEAL] = ITEM_TYPE_MEDICINE_STATUS_RECOVERY,

    [ITEM_REVIVE] = ITEM_TYPE_MEDICINE_FAINTED_RECOVERY,
    [ITEM_MAX_REVIVE] = ITEM_TYPE_MEDICINE_FAINTED_RECOVERY,

    [ITEM_ELIXIR] = ITEM_TYPE_MEDICINE_PP_RECOVERY,
    [ITEM_ETHER] = ITEM_TYPE_MEDICINE_PP_RECOVERY,
    [ITEM_MAX_ELIXIR] = ITEM_TYPE_MEDICINE_PP_RECOVERY,
    [ITEM_MAX_ETHER] = ITEM_TYPE_MEDICINE_PP_RECOVERY,

    [ITEM_BERRY_JUICE] = ITEM_TYPE_DRINK_HP_RECOVERY,
    [ITEM_FRESH_WATER] = ITEM_TYPE_DRINK_HP_RECOVERY,
    [ITEM_LEMONADE] = ITEM_TYPE_DRINK_HP_RECOVERY,
    [ITEM_SODA_POP] = ITEM_TYPE_DRINK_HP_RECOVERY,
    [ITEM_MOOMOO_MILK] = ITEM_TYPE_DRINK_HP_RECOVERY,

    [ITEM_ENERGY_POWDER] = ITEM_TYPE_HERB_HP_RECOVERY,
    [ITEM_ENERGY_ROOT] = ITEM_TYPE_HERB_HP_RECOVERY,
    [ITEM_HEAL_POWDER] = ITEM_TYPE_HERB_STATUS_RECOVERY,
    [ITEM_REVIVAL_HERB] = ITEM_TYPE_HERB_FAINTED_RECOVERY,

    [ITEM_LAVA_COOKIE] = ITEM_TYPE_TREAT_STATUS_RECOVERY,
    [ITEM_OLD_GATEAU] = ITEM_TYPE_TREAT_STATUS_RECOVERY,
    [ITEM_SWEET_HEART] = ITEM_TYPE_TREAT_STATUS_RECOVERY,
    [ITEM_BIG_MALASADA] = ITEM_TYPE_TREAT_STATUS_RECOVERY,

    [ITEM_SACRED_ASH] = ITEM_TYPE_SPECIAL_FAINTED_RECOVERY,

    [ITEM_REPEL] = ITEM_TYPE_FIELD_USE,
    [ITEM_SUPER_REPEL] = ITEM_TYPE_FIELD_USE,
    [ITEM_MAX_REPEL] = ITEM_TYPE_FIELD_USE,
    [ITEM_ESCAPE_ROPE] = ITEM_TYPE_FIELD_USE,
    [ITEM_HONEY] = ITEM_TYPE_FIELD_USE,

    [ITEM_POKE_DOLL] = ITEM_TYPE_BATTLE_ITEM,
    [ITEM_FLUFFY_TAIL] = ITEM_TYPE_BATTLE_ITEM,

    [ITEM_X_ATTACK] = ITEM_TYPE_BATTLE_X_ITEM,
    [ITEM_X_DEFENSE] = ITEM_TYPE_BATTLE_X_ITEM,
    [ITEM_X_SP_ATK] = ITEM_TYPE_BATTLE_X_ITEM,
    [ITEM_X_SP_DEF] = ITEM_TYPE_BATTLE_X_ITEM,
    [ITEM_X_SPEED] = ITEM_TYPE_BATTLE_X_ITEM,
    [ITEM_X_ACCURACY] = ITEM_TYPE_BATTLE_X_ITEM,
    [ITEM_DIRE_HIT] = ITEM_TYPE_BATTLE_X_ITEM,
    [ITEM_GUARD_SPEC] = ITEM_TYPE_BATTLE_X_ITEM,

    [ITEM_RARE_CANDY] = ITEM_TYPE_CANDY,
    [ITEM_ABILITY_CAPSULE] = ITEM_TYPE_EV_VITAMIN,

    [ITEM_HP_UP] = ITEM_TYPE_EV_VITAMIN,
    [ITEM_PROTEIN] = ITEM_TYPE_EV_VITAMIN,
    [ITEM_IRON] = ITEM_TYPE_EV_VITAMIN,
    [ITEM_CALCIUM] = ITEM_TYPE_EV_VITAMIN,
    [ITEM_ZINC] = ITEM_TYPE_EV_VITAMIN,
    [ITEM_CARBOS] = ITEM_TYPE_EV_VITAMIN,
    [ITEM_PP_MAX] = ITEM_TYPE_EV_VITAMIN,
    [ITEM_PP_UP] = ITEM_TYPE_EV_VITAMIN,

    [ITEM_CLEVER_WING] = ITEM_TYPE_EV_WING,
    [ITEM_GENIUS_WING] = ITEM_TYPE_EV_WING,
    [ITEM_HEALTH_WING] = ITEM_TYPE_EV_WING,
    [ITEM_MUSCLE_WING] = ITEM_TYPE_EV_WING,
    [ITEM_RESIST_WING] = ITEM_TYPE_EV_WING,
    [ITEM_SWIFT_WING] = ITEM_TYPE_EV_WING,

    [ITEM_BLUE_FLUTE] = ITEM_TYPE_FLUTE,
    [ITEM_RED_FLUTE] = ITEM_TYPE_FLUTE,
    [ITEM_YELLOW_FLUTE] = ITEM_TYPE_FLUTE,
    [ITEM_WHITE_FLUTE] = ITEM_TYPE_FLUTE,
    [ITEM_BLACK_FLUTE] = ITEM_TYPE_FLUTE,
    
    [ITEM_RED_SHARD] = ITEM_TYPE_SHARD,
    [ITEM_BLUE_SHARD] = ITEM_TYPE_SHARD,
    [ITEM_YELLOW_SHARD] = ITEM_TYPE_SHARD,
    [ITEM_GREEN_SHARD] = ITEM_TYPE_SHARD,

    [ITEM_RED_APRICORN] = ITEM_TYPE_APRICORN,
    [ITEM_BLUE_APRICORN] = ITEM_TYPE_APRICORN,
    [ITEM_YELLOW_APRICORN] = ITEM_TYPE_APRICORN,
    [ITEM_GREEN_APRICORN] = ITEM_TYPE_APRICORN,
    [ITEM_PINK_APRICORN] = ITEM_TYPE_APRICORN,
    [ITEM_WHITE_APRICORN] = ITEM_TYPE_APRICORN,
    [ITEM_BLACK_APRICORN] = ITEM_TYPE_APRICORN,

    [ITEM_HEART_SCALE] = ITEM_TYPE_VALUABLE,
    [ITEM_TINY_MUSHROOM] = ITEM_TYPE_VALUABLE,
    [ITEM_BIG_MUSHROOM] = ITEM_TYPE_VALUABLE,
    [ITEM_NUGGET] = ITEM_TYPE_VALUABLE,
    [ITEM_BIG_NUGGET] = ITEM_TYPE_VALUABLE,
    [ITEM_STAR_PIECE] = ITEM_TYPE_VALUABLE,
    [ITEM_STARDUST] = ITEM_TYPE_VALUABLE,
    [ITEM_PEARL] = ITEM_TYPE_VALUABLE,
    [ITEM_BIG_PEARL] = ITEM_TYPE_VALUABLE,
    [ITEM_RARE_BONE] = ITEM_TYPE_VALUABLE,
    [ITEM_SHOAL_SALT] = ITEM_TYPE_VALUABLE,
    [ITEM_SHOAL_SHELL] = ITEM_TYPE_VALUABLE,
    [ITEM_PRETTY_WING] = ITEM_TYPE_VALUABLE,
    [ITEM_ODD_KEYSTONE] = ITEM_TYPE_VALUABLE,

    [ITEM_FIRE_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_WATER_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_THUNDER_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_LEAF_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_SUN_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_MOON_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_DAWN_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_DUSK_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_SHINY_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_ICE_STONE] = ITEM_TYPE_EVOLUTION_STONE,

    [ITEM_HELIX_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_DOME_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_OLD_AMBER] = ITEM_TYPE_FOSSIL,
    [ITEM_CLAW_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_ROOT_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_ARMOR_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_SKULL_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_COVER_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_PLUME_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_JAW_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_SAIL_FOSSIL] = ITEM_TYPE_FOSSIL,

    [ITEM_BEAD_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_DREAM_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_FAB_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_GLITTER_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_HARBOR_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_MECH_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_ORANGE_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_RETRO_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_SHADOW_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_TROPIC_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_WAVE_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_WOOD_MAIL] = ITEM_TYPE_MAIL,

    [ITEM_CHERI_BERRY] = ITEM_TYPE_BERRY_STATUS_RECOVERY,
    [ITEM_CHESTO_BERRY] = ITEM_TYPE_BERRY_STATUS_RECOVERY,
    [ITEM_PECHA_BERRY] = ITEM_TYPE_BERRY_STATUS_RECOVERY,
    [ITEM_RAWST_BERRY] = ITEM_TYPE_BERRY_STATUS_RECOVERY,
    [ITEM_ASPEAR_BERRY] = ITEM_TYPE_BERRY_STATUS_RECOVERY,
    [ITEM_LEPPA_BERRY] = ITEM_TYPE_BERRY_PP_RECOVERY,
    [ITEM_ORAN_BERRY] = ITEM_TYPE_BERRY_HP_RECOVERY,
    [ITEM_PERSIM_BERRY] = ITEM_TYPE_BERRY_STATUS_RECOVERY,
    [ITEM_LUM_BERRY] = ITEM_TYPE_BERRY_STATUS_RECOVERY,
    [ITEM_SITRUS_BERRY] = ITEM_TYPE_BERRY_HP_RECOVERY,
    [ITEM_FIGY_BERRY] = ITEM_TYPE_BERRY_PINCH_HP_RECOVERY,
    [ITEM_WIKI_BERRY] = ITEM_TYPE_BERRY_PINCH_HP_RECOVERY,
    [ITEM_MAGO_BERRY] = ITEM_TYPE_BERRY_PINCH_HP_RECOVERY,
    [ITEM_AGUAV_BERRY] = ITEM_TYPE_BERRY_PINCH_HP_RECOVERY,
    [ITEM_IAPAPA_BERRY] = ITEM_TYPE_BERRY_PINCH_HP_RECOVERY,
    [ITEM_RAZZ_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_BLUK_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_NANAB_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_WEPEAR_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_PINAP_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_POMEG_BERRY] = ITEM_TYPE_BERRY_REDUCE_EV,
    [ITEM_KELPSY_BERRY] = ITEM_TYPE_BERRY_REDUCE_EV,
    [ITEM_QUALOT_BERRY] = ITEM_TYPE_BERRY_REDUCE_EV,
    [ITEM_HONDEW_BERRY] = ITEM_TYPE_BERRY_REDUCE_EV,
    [ITEM_GREPA_BERRY] = ITEM_TYPE_BERRY_REDUCE_EV,
    [ITEM_TAMATO_BERRY] = ITEM_TYPE_BERRY_REDUCE_EV,
    [ITEM_CORNN_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_MAGOST_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_RABUTA_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_NOMEL_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_SPELON_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_PAMTRE_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_WATMEL_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_DURIN_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_BELUE_BERRY] = ITEM_TYPE_BERRY_APRICORN,
    [ITEM_OCCA_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_PASSHO_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_WACAN_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_RINDO_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_YACHE_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_CHOPLE_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_KEBIA_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_SHUCA_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_COBA_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_PAYAPA_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_TANGA_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_CHARTI_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_KASIB_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_HABAN_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_COLBUR_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_BABIRI_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_CHILAN_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_ROSELI_BERRY] = ITEM_TYPE_BERRY_REDUCE_SUPER_EFFECTIVE_DAMAGE,
    [ITEM_LIECHI_BERRY] = ITEM_TYPE_BERRY_PINCH_STAT_RAISE,
    [ITEM_GANLON_BERRY] = ITEM_TYPE_BERRY_PINCH_STAT_RAISE,
    [ITEM_SALAC_BERRY] = ITEM_TYPE_BERRY_PINCH_STAT_RAISE,
    [ITEM_PETAYA_BERRY] = ITEM_TYPE_BERRY_PINCH_STAT_RAISE,
    [ITEM_APICOT_BERRY] = ITEM_TYPE_BERRY_PINCH_STAT_RAISE,
    [ITEM_LANSAT_BERRY] = ITEM_TYPE_BERRY_PINCH_STAT_RAISE,
    [ITEM_STARF_BERRY] = ITEM_TYPE_BERRY_PINCH_STAT_RAISE,
    [ITEM_ENIGMA_BERRY] = ITEM_TYPE_BERRY_SPECIAL,
    [ITEM_MICLE_BERRY] = ITEM_TYPE_UNKNOWN,
    [ITEM_CUSTAP_BERRY] = ITEM_TYPE_UNKNOWN,
    [ITEM_JABOCA_BERRY] = ITEM_TYPE_UNKNOWN,
    [ITEM_ROWAP_BERRY] = ITEM_TYPE_UNKNOWN,
    [ITEM_KEE_BERRY] = ITEM_TYPE_UNKNOWN,
    [ITEM_MARANGA_BERRY] = ITEM_TYPE_UNKNOWN,

    [ITEM_AMULET_COIN] = ITEM_TYPE_HELD_ITEM,
    [ITEM_CLEANSE_TAG] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SMOKE_BALL] = ITEM_TYPE_HELD_ITEM,

    [ITEM_LUCKY_EGG] = ITEM_TYPE_HELD_ITEM_TRAINING,
    [ITEM_SOOTHE_BELL] = ITEM_TYPE_HELD_ITEM_TRAINING,

    [ITEM_EVERSTONE] = ITEM_TYPE_HELD_ITEM_BREEDING,
    [ITEM_DESTINY_KNOT] = ITEM_TYPE_HELD_ITEM_BREEDING,

    [ITEM_MACHO_BRACE] = ITEM_TYPE_HELD_ITEM_EV_TRAINING,
    [ITEM_POWER_ANKLET] = ITEM_TYPE_HELD_ITEM_EV_TRAINING,
    [ITEM_POWER_BAND] = ITEM_TYPE_HELD_ITEM_EV_TRAINING,
    [ITEM_POWER_BELT] = ITEM_TYPE_HELD_ITEM_EV_TRAINING,
    [ITEM_POWER_BRACER] = ITEM_TYPE_HELD_ITEM_EV_TRAINING,
    [ITEM_POWER_LENS] = ITEM_TYPE_HELD_ITEM_EV_TRAINING,
    [ITEM_POWER_WEIGHT] = ITEM_TYPE_HELD_ITEM_EV_TRAINING,

    [ITEM_BLUE_SCARF] = ITEM_TYPE_HELD_ITEM_CONTEST,
    [ITEM_GREEN_SCARF] = ITEM_TYPE_HELD_ITEM_CONTEST,
    [ITEM_PINK_SCARF] = ITEM_TYPE_HELD_ITEM_CONTEST,
    [ITEM_RED_SCARF] = ITEM_TYPE_HELD_ITEM_CONTEST,
    [ITEM_YELLOW_SCARF] = ITEM_TYPE_HELD_ITEM_CONTEST,

    [ITEM_BRIGHT_POWDER] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_WHITE_HERB] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_MENTAL_HERB] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_POWER_HERB] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_QUICK_CLAW] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_CHOICE_BAND] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_CHOICE_SCARF] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_CHOICE_SPECS] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_LEFTOVERS] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_BLACK_SLUDGE] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_SHELL_BELL] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_FOCUS_BAND] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_FOCUS_SASH] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_SCOPE_LENS] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_WIDE_LENS] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_ZOOM_LENS] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_SILVER_POWDER] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_BLACK_GLASSES] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_DRAGON_FANG] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_MAGNET] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_BLACK_BELT] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_CHARCOAL] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_SHARP_BEAK] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_SPELL_TAG] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_MIRACLE_SEED] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_SOFT_SAND] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_NEVER_MELT_ICE] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_SILK_SCARF] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_POISON_BARB] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_TWISTED_SPOON] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_HARD_STONE] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_MYSTIC_WATER] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_METAL_COAT] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_KINGS_ROCK] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_RAZOR_CLAW] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_RAZOR_FANG] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_METRONOME] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_MUSCLE_BAND] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_WISE_GLASSES] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_EXPERT_BELT] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_LIGHT_CLAY] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_ICY_ROCK] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_SMOOTH_ROCK] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_HEAT_ROCK] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_DAMP_ROCK] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_GRIP_CLAW] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_BINDING_BAND] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_LIFE_ORB] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_TOXIC_ORB] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_FLAME_ORB] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_STICKY_BARB] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_IRON_BALL] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_LAGGING_TAIL] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_SHED_SHELL] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_BIG_ROOT] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_EVIOLITE] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_FLOAT_STONE] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_ROCKY_HELMET] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_AIR_BALLOON] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_RING_TARGET] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_RED_CARD] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_EJECT_BUTTON] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_ABSORB_BULB] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_CELL_BATTERY] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_LUMINOUS_MOSS] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_SNOWBALL] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_WEAKNESS_POLICY] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_ADRENALINE_ORB] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_ASSAULT_VEST] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_SAFETY_GOGGLES] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_PROTECTIVE_PADS] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_TERRAIN_EXTENDER] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_ELECTRIC_SEED] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_PSYCHIC_SEED] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_MISTY_SEED] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,
    [ITEM_GRASSY_SEED] = ITEM_TYPE_HELD_ITEM_COMPETITIVE,

    [ITEM_UP_GRADE] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_DUBIOUS_DISC] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_DRAGON_SCALE] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_OVAL_STONE] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_PROTECTOR] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_DEEP_SEA_SCALE] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_DEEP_SEA_TOOTH] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_ELECTIRIZER] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_MAGMARIZER] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_REAPER_CLOTH] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_PRISM_SCALE] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_WHIPPED_DREAM] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_SACHET] = ITEM_TYPE_HELD_ITEM_EVOLUTION,
    [ITEM_STRANGE_SOUVENIR] = ITEM_TYPE_HELD_ITEM_EVOLUTION,

    [ITEM_FULL_INCENSE] = ITEM_TYPE_HELD_ITEM_INCENSE,
    [ITEM_LAX_INCENSE] = ITEM_TYPE_HELD_ITEM_INCENSE,
    [ITEM_LUCK_INCENSE] = ITEM_TYPE_HELD_ITEM_INCENSE,
    [ITEM_ODD_INCENSE] = ITEM_TYPE_HELD_ITEM_INCENSE,
    [ITEM_PURE_INCENSE] = ITEM_TYPE_HELD_ITEM_INCENSE,
    [ITEM_ROCK_INCENSE] = ITEM_TYPE_HELD_ITEM_INCENSE,
    [ITEM_ROSE_INCENSE] = ITEM_TYPE_HELD_ITEM_INCENSE,
    [ITEM_SEA_INCENSE] = ITEM_TYPE_HELD_ITEM_INCENSE,
    [ITEM_WAVE_INCENSE] = ITEM_TYPE_HELD_ITEM_INCENSE,

    [ITEM_BUG_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_DARK_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_DRAGON_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_ELECTRIC_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_FAIRY_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_FIGHTING_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_FIRE_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_FLYING_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_GHOST_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_GRASS_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_GROUND_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_ICE_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_NORMAL_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_POISON_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_PSYCHIC_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_ROCK_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_STEEL_GEM] = ITEM_TYPE_HELD_ITEM_GEM,
    [ITEM_WATER_GEM] = ITEM_TYPE_HELD_ITEM_GEM,

    [ITEM_LIGHT_BALL] = ITEM_TYPE_HELD_ITEM_SPECIES,
    [ITEM_STICK] = ITEM_TYPE_HELD_ITEM_SPECIES,
    [ITEM_THICK_CLUB] = ITEM_TYPE_HELD_ITEM_SPECIES,
    [ITEM_QUICK_POWDER] = ITEM_TYPE_HELD_ITEM_SPECIES,
    [ITEM_METAL_POWDER] = ITEM_TYPE_HELD_ITEM_SPECIES,
    [ITEM_LUCKY_PUNCH] = ITEM_TYPE_HELD_ITEM_SPECIES,
    [ITEM_SOUL_DEW] = ITEM_TYPE_HELD_ITEM_SPECIES,
    [ITEM_ADAMANT_ORB] = ITEM_TYPE_HELD_ITEM_SPECIES,
    [ITEM_LUSTROUS_ORB] = ITEM_TYPE_HELD_ITEM_SPECIES,
    [ITEM_GRISEOUS_ORB] = ITEM_TYPE_HELD_ITEM_SPECIES,

    [ITEM_BURN_DRIVE] = ITEM_TYPE_HELD_ITEM_DRIVE,
    [ITEM_CHILL_DRIVE] = ITEM_TYPE_HELD_ITEM_DRIVE,
    [ITEM_DOUSE_DRIVE] = ITEM_TYPE_HELD_ITEM_DRIVE,
    [ITEM_SHOCK_DRIVE] = ITEM_TYPE_HELD_ITEM_DRIVE,

    [ITEM_BUG_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_DARK_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_DRAGON_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_ELECTRIC_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_FAIRY_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_FIGHTING_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_FIRE_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_FLYING_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_GHOST_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_GRASS_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_GROUND_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_ICE_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_POISON_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_PSYCHIC_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_ROCK_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_STEEL_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,
    [ITEM_WATER_MEMORY] = ITEM_TYPE_HELD_ITEM_MEMORY,

    [ITEM_DRACO_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_DREAD_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_EARTH_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_FIST_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_FLAME_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_ICICLE_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_INSECT_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_IRON_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_MEADOW_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_MIND_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_PIXIE_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_SKY_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_SPLASH_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_SPOOKY_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_STONE_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_TOXIC_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,
    [ITEM_ZAP_PLATE] = ITEM_TYPE_HELD_ITEM_PLATE,

    [ITEM_ABOMASITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_ABSOLITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_AERODACTYLITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_AGGRONITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_ALAKAZITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_ALTARIANITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_AMPHAROSITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_AUDINITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_BANETTITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_BEEDRILLITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_BLASTOISINITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_BLAZIKENITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_CAMERUPTITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_CHARIZARDITE_X] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_CHARIZARDITE_Y] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_DIANCITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_GALLADITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_GARCHOMPITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_GARDEVOIRITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_GENGARITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_GLALITITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_GYARADOSITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_HERACRONITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_HOUNDOOMINITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_KANGASKHANITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_LATIASITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_LATIOSITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_LOPUNNITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_LUCARIONITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_MANECTITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_MAWILITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_MEDICHAMITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_METAGROSSITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_MEWTWONITE_X] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_MEWTWONITE_Y] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_PIDGEOTITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_PINSIRITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_SABLENITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_SALAMENCITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_SCEPTILITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_SCIZORITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_SHARPEDONITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_SLOWBRONITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_STEELIXITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_SWAMPERTITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_TYRANITARITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,
    [ITEM_VENUSAURITE] = ITEM_TYPE_HELD_ITEM_MEGA_STONE,

    [ITEM_TM01] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM02] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM03] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM04] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM05] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM06] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM07] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM08] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM09] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM10] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM11] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM12] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM13] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM14] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM15] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM16] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM17] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM18] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM19] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM20] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM21] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM22] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM23] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM24] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM25] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM26] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM27] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM28] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM29] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM30] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM31] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM32] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM33] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM34] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM35] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM36] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM37] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM38] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM39] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM40] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM41] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM42] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM43] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM44] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM45] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM46] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM47] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM48] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM49] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM50] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM51] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM52] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM53] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM54] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM55] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM56] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM57] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM58] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM59] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM60] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM61] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM62] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM63] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM64] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM65] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM66] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM67] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM68] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM69] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM70] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM71] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM72] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM73] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM74] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM75] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM76] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM77] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM78] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM79] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM80] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM81] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM82] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM83] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM84] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM85] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM86] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM87] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM88] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM89] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM90] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM91] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM92] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM93] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM94] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM95] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM96] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM97] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM98] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM99] = ITEM_TYPE_TECHNICAL_MACHINE,
    [ITEM_TM100] = ITEM_TYPE_TECHNICAL_MACHINE,

    [ITEM_HM01] = ITEM_TYPE_HIDDEN_MACHINE,
    [ITEM_HM02] = ITEM_TYPE_HIDDEN_MACHINE,
    [ITEM_HM03] = ITEM_TYPE_HIDDEN_MACHINE,
    [ITEM_HM04] = ITEM_TYPE_HIDDEN_MACHINE,
    [ITEM_HM05] = ITEM_TYPE_HIDDEN_MACHINE,
    [ITEM_HM06] = ITEM_TYPE_HIDDEN_MACHINE,
    [ITEM_HM07] = ITEM_TYPE_HIDDEN_MACHINE,
    [ITEM_HM08] = ITEM_TYPE_HIDDEN_MACHINE,

    [ITEM_EXP_SHARE] = ITEM_TYPE_KEY_ITEM_UTILITY,
    [ITEM_ITEMFINDER] = ITEM_TYPE_KEY_ITEM_UTILITY,
    [ITEM_WAILMER_PAIL] = ITEM_TYPE_KEY_ITEM_UTILITY,

    [ITEM_OLD_ROD] = ITEM_TYPE_KEY_ITEM_FISHING_ROD,
    [ITEM_GOOD_ROD] = ITEM_TYPE_KEY_ITEM_FISHING_ROD,
    [ITEM_SUPER_ROD] = ITEM_TYPE_KEY_ITEM_FISHING_ROD,

    [ITEM_ACRO_BIKE] = ITEM_TYPE_KEY_ITEM_BIKE,
    [ITEM_MACH_BIKE] = ITEM_TYPE_KEY_ITEM_BIKE,

    [ITEM_COIN_CASE] = ITEM_TYPE_KEY_ITEM_CONTAINER,
    [ITEM_POKEBLOCK_CASE] = ITEM_TYPE_KEY_ITEM_CONTAINER,
    [ITEM_POWDER_JAR] = ITEM_TYPE_KEY_ITEM_CONTAINER,
    [ITEM_SOOT_SACK] = ITEM_TYPE_KEY_ITEM_CONTAINER,

    [ITEM_GRACIDEA] = ITEM_TYPE_KEY_ITEM_FORM_CHANGE,
    [ITEM_PINK_NECTAR] = ITEM_TYPE_KEY_ITEM_FORM_CHANGE,
    [ITEM_PURPLE_NECTAR] = ITEM_TYPE_KEY_ITEM_FORM_CHANGE,
    [ITEM_RED_NECTAR] = ITEM_TYPE_KEY_ITEM_FORM_CHANGE,
    [ITEM_YELLOW_NECTAR] = ITEM_TYPE_KEY_ITEM_FORM_CHANGE,

    [ITEM_DEVON_GOODS] = ITEM_TYPE_KEY_ITEM_TRADE,
    [ITEM_LETTER] = ITEM_TYPE_KEY_ITEM_TRADE,
    [ITEM_METEORITE] = ITEM_TYPE_KEY_ITEM_TRADE,
    [ITEM_SCANNER] = ITEM_TYPE_KEY_ITEM_TRADE,

    [ITEM_BLUE_ORB] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_RED_ORB] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_GO_GOGGLES] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_BASEMENT_KEY] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_SECRET_KEY] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_DEVON_SCOPE] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_CONTEST_PASS] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_MAGMA_EMBLEM] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_ROOM_1_KEY] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_ROOM_2_KEY] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_ROOM_4_KEY] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_ROOM_6_KEY] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_SS_TICKET] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_AURORA_TICKET] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_EON_TICKET] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_MYSTIC_TICKET] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_OLD_SEA_MAP] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_STORAGE_KEY] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_MEGA_BRACELET] = ITEM_TYPE_KEY_ITEM_PASSIVE,
    [ITEM_SHINY_CHARM] = ITEM_TYPE_KEY_ITEM_PASSIVE,

    [ITEM_BERRY_POUCH] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_BICYCLE] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_BIKE_VOUCHER] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_CARD_KEY] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_FAME_CHECKER] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_GOLD_TEETH] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_LIFT_KEY] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_OAKS_PARCEL] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_POKE_FLUTE] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_RAINBOW_PASS] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_RUBY] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_SAPPHIRE] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_SILPH_SCOPE] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_TEA] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_TEACHY_TV] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_TM_CASE] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_TOWN_MAP] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_TRI_PASS] = ITEM_TYPE_KEY_ITEM_FRLG,
    [ITEM_VS_SEEKER] = ITEM_TYPE_KEY_ITEM_FRLG,
};

static void AddBagSortSubMenu(void)
{
    switch (gBagPositionStruct.pocket + 1)
    {
        case POCKET_KEY_ITEMS:
            gBagMenu->contextMenuItemsPtr = sBagMenuSortKeyItems;
            memcpy(&gBagMenu->contextMenuItemsBuffer, &sBagMenuSortKeyItems, NELEMS(sBagMenuSortKeyItems));
            gBagMenu->contextMenuNumItems = NELEMS(sBagMenuSortKeyItems);
            break;
        case POCKET_POKE_BALLS:
            gBagMenu->contextMenuItemsPtr = sBagMenuSortPokeBalls;
            memcpy(&gBagMenu->contextMenuItemsBuffer, &sBagMenuSortPokeBalls, NELEMS(sBagMenuSortPokeBalls));
            gBagMenu->contextMenuNumItems = NELEMS(sBagMenuSortPokeBalls);
            break;
        case POCKET_BERRIES:
            gBagMenu->contextMenuItemsPtr = sBagMenuSortBerries;
            memcpy(&gBagMenu->contextMenuItemsBuffer, &sBagMenuSortBerries, NELEMS(sBagMenuSortBerries));
            gBagMenu->contextMenuNumItems = NELEMS(sBagMenuSortBerries);
            break;
        case POCKET_TM_HM:
            gBagMenu->contextMenuItemsPtr = sBagMenuSortTMs;
            memcpy(&gBagMenu->contextMenuItemsBuffer, &sBagMenuSortTMs, NELEMS(sBagMenuSortTMs));
            gBagMenu->contextMenuNumItems = NELEMS(sBagMenuSortTMs);
            break;
        default:
            gBagMenu->contextMenuItemsPtr = sBagMenuSortItems;
            memcpy(&gBagMenu->contextMenuItemsBuffer, &sBagMenuSortItems, NELEMS(sBagMenuSortItems));
            gBagMenu->contextMenuNumItems = NELEMS(sBagMenuSortItems);
            break;
    }
    
    StringExpandPlaceholders(gStringVar4, sText_SortItemsHow);
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
    
    if (gBagMenu->contextMenuNumItems == 2)
        sub_81ACAF8(BagMenu_AddWindow(1));
    else if (gBagMenu->contextMenuNumItems == 4)
        sub_81ACB54(BagMenu_AddWindow(2), 2, 2);
    else
        sub_81ACB54(BagMenu_AddWindow(3), 2, 3);
}

static void Task_LoadBagSortOptions(u8 taskId)
{
    AddBagSortSubMenu();
    gTasks[taskId].func = Task_HandleOutOfBattleItemMenuInput;
}

#define tSortType data[2]
static void ItemMenu_SortByName(u8 taskId)
{
    gTasks[taskId].tSortType = SORT_ALPHABETICALLY;
    StringCopy(gStringVar1, sSortTypeStrings[SORT_ALPHABETICALLY]);
    gTasks[taskId].func = SortBagItems;
}
static void ItemMenu_SortByType(u8 taskId)
{
    gTasks[taskId].tSortType = SORT_BY_TYPE;
    StringCopy(gStringVar1, sSortTypeStrings[SORT_BY_TYPE]);
    gTasks[taskId].func = SortBagItems;
}
static void ItemMenu_SortByQuantity(u8 taskId)
{
    gTasks[taskId].tSortType = SORT_BY_QUANTITY; //greatest->least
    StringCopy(gStringVar1, sSortTypeStrings[SORT_BY_QUANTITY]);
    gTasks[taskId].func = SortBagItems;
}
static void ItemMenu_SortByNumber(u8 taskId)
{
    gTasks[taskId].tSortType = SORT_BY_NUMBER; //by itemID
    StringCopy(gStringVar1, sSortTypeStrings[SORT_BY_NUMBER]);
    gTasks[taskId].func = SortBagItems;
}

static void SortBagItems(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    BagMenu_RemoveSomeWindow();
    //sItemDescriptionPocket = 0; //Sorting Items
    StringCopy(gStringVar1, sSortTypeStrings[tSortType]);
    StringExpandPlaceholders(gStringVar4, sText_ItemsSorted);
    DisplayItemMessage(taskId, 1, gStringVar4, Task_SortFinish);
}

static void Task_SortFinish(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];


    if (gMain.newKeys & (A_BUTTON | B_BUTTON))
    {
        //BagPrintTextOnWindow(ShowBagWindow(6, 3), 2, gStringVar4, 0, 2, 1, 0, 0, 1);
        SortItemsInBag(gBagPositionStruct.pocket, tSortType);
        BagMenu_RemoveBagItemMessageindow(4);
        DestroyListMenuTask(data[0], scrollPos, cursorPos);
        SetInitialScrollAndCursorPositions(gBagPositionStruct.pocket);
        LoadBagItemListBuffers(gBagPositionStruct.pocket);
        data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
        ScheduleBgCopyTilemapToVram(0);
        set_callback3_to_bag(taskId);
    }
}

static void SortItemsInBag(u8 pocket, u8 type)
{
    struct ItemSlot* itemMem;
    u16 itemAmount;
    s8 (*func)(struct ItemSlot*, struct ItemSlot*);

    switch (pocket)
    {
        case ITEMS_POCKET:
            itemMem = gSaveBlock1Ptr->bagPocket_Items;
            itemAmount = BAG_ITEMS_COUNT;
            break;
        case MEDICINE_POCKET:
            itemMem = gSaveBlock1Ptr->bagPocket_Medicine;
            itemAmount = BAG_MEDICINE_COUNT;
            break;
        case BALLS_POCKET:
            itemMem = gSaveBlock1Ptr->bagPocket_PokeBalls;
            itemAmount = BAG_POKEBALLS_COUNT;
            break;
        case COMPETITIVE_POCKET:
            itemMem = gSaveBlock1Ptr->bagPocket_Competitive;
            itemAmount = BAG_COMPETITIVE_COUNT;
            break;
        case BERRIES_POCKET:
            itemMem = gSaveBlock1Ptr->bagPocket_Berries;
            itemAmount = BAG_BERRIES_COUNT;
            break;
        case TRAINING_POCKET:
            itemMem = gSaveBlock1Ptr->bagPocket_Training;
            itemAmount = BAG_TRAINING_COUNT;
            break;
        case TMHM_POCKET:
            itemMem = gSaveBlock1Ptr->bagPocket_TMHM;
            itemAmount = BAG_TMHM_COUNT;
            break;
        case KEYITEMS_POCKET:
            itemMem = gSaveBlock1Ptr->bagPocket_KeyItems;
            itemAmount = BAG_KEYITEMS_COUNT;
            break;
        default:
            return;
    }

    switch (type)
    {
        case SORT_ALPHABETICALLY:
            MergeSort(itemMem, 0, itemAmount - 1, CompareItemsAlphabetically);
            break;
        case SORT_BY_QUANTITY:
            MergeSort(itemMem, 0, itemAmount - 1, CompareItemsByMost);
            break;
        case SORT_BY_NUMBER:
            MergeSort(itemMem, 0, itemAmount - 1, CompareItemsById);
            break;
        default:
            MergeSort(itemMem, 0, itemAmount - 1, CompareItemsByType);
            break;
    }
}

static void MergeSort(struct ItemSlot* array, u32 low, u32 high, s8 (*comparator)(struct ItemSlot*, struct ItemSlot*))
{
    u32 mid;
    
    if (high <= low)
        return;

    mid = low + (high - low) / 2;
    MergeSort(array, low, mid, comparator); //Sort left half.
    MergeSort(array, mid + 1, high, comparator); //Sort right half.
    Merge(array, low, mid, high, comparator); //Merge results.
}

static void Merge(struct ItemSlot* array, u32 low, u32 mid, u32 high, s8 (*comparator)(struct ItemSlot*, struct ItemSlot*))
{
    u32 i = low;
    u32 j = mid + 1;
    u32 k;
    struct ItemSlot aux[high + 1];

    for (k = low; k <= high; ++k)
        aux[k] = array[k];

    for (k = low; k <= high; ++k)
    { //Merge back to a[low..high]
        if (i > mid)
            array[k] = aux[j++];
        else if (j > high)
            array[k] = aux[i++];
        else if (comparator(&aux[j], &aux[i]) < 0)
            array[k] = aux[j++];
        else
            array[k] = aux[i++];
    }
}

static s8 CompareItemsAlphabetically(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2)
{
    u16 item1 = itemSlot1->itemId;
    u16 item2 = itemSlot2->itemId;
    int i;
    const u8 *name1;
    const u8 *name2;

    if (item1 == ITEM_NONE)
        return 1;
    else if (item2 == ITEM_NONE)
        return -1;

    // Sort TMs & HMs by their move name
    if (ItemId_GetPocket(item1) == POCKET_TM_HM)
        name1 = gMoveNames[ItemIdToBattleMoveId(item1)];
    else        
        name1 = ItemId_GetName(item1);

    if (ItemId_GetPocket(item2) == POCKET_TM_HM)
        name2 = gMoveNames[ItemIdToBattleMoveId(item2)]; 
    else
        name2 = ItemId_GetName(item2);

    for (i = 0; ; ++i)
    {
        if (name1[i] == EOS && name2[i] != EOS)
            return -1;
        else if (name1[i] != EOS && name2[i] == EOS)
            return 1;
        else if (name1[i] == EOS && name2[i] == EOS)
            return 0;

        if (name1[i] < name2[i])
            return -1;
        else if (name1[i] > name2[i])
            return 1;
    }

    return 0; //Will never be reached
}

static s8 CompareItemsByMost(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2)
{
    u16 quantity1 = GetBagItemQuantity(&itemSlot1->quantity);
    u16 quantity2 = GetBagItemQuantity(&itemSlot2->quantity);

    if (itemSlot1->itemId == ITEM_NONE)
        return 1;
    else if (itemSlot2->itemId == ITEM_NONE)
        return -1;

    if (quantity1 < quantity2)
        return 1;
    else if (quantity1 > quantity2)
        return -1;

    return CompareItemsAlphabetically(itemSlot1, itemSlot2); //Items have same quantity (and maybe same id or type) so sort alphabetically
}

static s8 CompareItemsById(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2)
{
    if (itemSlot1->itemId == ITEM_NONE)
        return 1;
    else if (itemSlot2->itemId == ITEM_NONE)
        return -1;

    if (itemSlot2->itemId < itemSlot1->itemId)
        return 1;
    else if (itemSlot2->itemId > itemSlot1->itemId)
        return -1;

    return CompareItemsByMost(itemSlot1, itemSlot2); //Items with the same ID are sorted by stack amount
}

static s8 CompareItemsByType(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2)
{
    //Null items go last
    u8 type1 = (itemSlot1->itemId == ITEM_NONE) ? 0xFF : sItemsByType[itemSlot1->itemId];
    u8 type2 = (itemSlot2->itemId == ITEM_NONE) ? 0xFF : sItemsByType[itemSlot2->itemId];

    if (type1 < type2)
        return -1;
    else if (type1 > type2)
        return 1;

    return CompareItemsById(itemSlot1, itemSlot2); //Items are of same type so sort by id
}

// Register Select/L/R
static void ResetRegisteredItem(u16 item)
{
    if (gSaveBlock1Ptr->registeredItemSelect == item)
        gSaveBlock1Ptr->registeredItemSelect = ITEM_NONE;
    else if (gSaveBlock1Ptr->registeredItemL == item)
        gSaveBlock1Ptr->registeredItemL = ITEM_NONE;
    else if (gSaveBlock1Ptr->registeredItemR == item)
        gSaveBlock1Ptr->registeredItemR = ITEM_NONE;
}

static void ItemMenu_FinishRegister(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
        
    DestroyListMenuTask(data[0], scrollPos, cursorPos);
    LoadBagItemListBuffers(gBagPositionStruct.pocket);
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
    ScheduleBgCopyTilemapToVram(0);
    ItemMenu_Cancel(taskId);
}

static void ItemMenu_Register(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    int listPosition;
    
    BagMenu_RemoveSomeWindow();
    sRegisterSubMenu = TRUE;
    listPosition = ListMenu_ProcessInput(data[0]);
    ListMenuGetScrollAndRow(data[0], scrollPos, cursorPos);
    BagDestroyPocketScrollArrowPair();
    BagMenu_PrintCursor_(data[0], 2);
    data[1] = listPosition;
    data[2] = BagGetQuantityByPocketPosition(gBagPositionStruct.pocket + 1, listPosition);
    gSpecialVar_ItemId = BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, listPosition);
    gUnknown_08614054[gBagPositionStruct.location](taskId);
}

static void ItemMenu_RegisterSelect(u8 taskId)
{
    if (gSaveBlock1Ptr->registeredItemSelect == gSpecialVar_ItemId)
        gSaveBlock1Ptr->registeredItemSelect = 0;
    else
        gSaveBlock1Ptr->registeredItemSelect = gSpecialVar_ItemId;
    
    gTasks[taskId].func = ItemMenu_FinishRegister;
}

static void ItemMenu_RegisterL(u8 taskId)
{
    if (gSaveBlock1Ptr->registeredItemL == gSpecialVar_ItemId)
        gSaveBlock1Ptr->registeredItemL = ITEM_NONE;
    else
        gSaveBlock1Ptr->registeredItemL = gSpecialVar_ItemId;
    
    gTasks[taskId].func = ItemMenu_FinishRegister;
}

static void ItemMenu_RegisterR(u8 taskId)
{
    if (gSaveBlock1Ptr->registeredItemR == gSpecialVar_ItemId)
        gSaveBlock1Ptr->registeredItemR = ITEM_NONE;
    else
        gSaveBlock1Ptr->registeredItemR = gSpecialVar_ItemId;
    
    gTasks[taskId].func = ItemMenu_FinishRegister;
}

static void ItemMenu_Deselect(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    int listPosition = ListMenu_ProcessInput(data[0]);

    ResetRegisteredItem(BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, listPosition));
    gTasks[taskId].func = ItemMenu_FinishRegister;
}

#define tUsingRegisteredKeyItem data[3]
bool8 UseRegisteredKeyItemOnField(u8 button)
{
    u8 taskId;
    u16 registeredItem;

    if (InUnionRoom() == TRUE || InBattlePyramid() || InBattlePike() || InMultiPartnerRoom() == TRUE)
        return FALSE;
    
    HideMapNamePopUpWindow();
    ChangeBgY_ScreenOff(0, 0, 0);
    
    switch (button)
    {
    case 0:
        registeredItem = gSaveBlock1Ptr->registeredItemSelect;
        break;
    case 1:
        registeredItem = gSaveBlock1Ptr->registeredItemL;
        break;
    case 2:
        registeredItem = gSaveBlock1Ptr->registeredItemR;
        break;
    default:
        return FALSE;
    }
    
    if (registeredItem != ITEM_NONE)
    {
        if (CheckBagHasItem(registeredItem, 1) == TRUE)
        {
            ScriptContext2_Enable();
            FreezeObjectEvents();
            PlayerFreeze();
            sub_808BCF4();
            gSpecialVar_ItemId = registeredItem;
            taskId = CreateTask(ItemId_GetFieldFunc(registeredItem), 8);
            gTasks[taskId].tUsingRegisteredKeyItem = TRUE;
            return TRUE;
        }
        else
        {
            switch (button)
            {
            case 0:
                gSaveBlock1Ptr->registeredItemSelect = ITEM_NONE;
                break;
            case 1:
                gSaveBlock1Ptr->registeredItemL = ITEM_NONE;
                break;
            case 2:
                gSaveBlock1Ptr->registeredItemR = ITEM_NONE;
                break;
            }
        }
    }
    
    ScriptContext1_SetupScript(EventScript_SelectWithoutRegisteredItem);
    return TRUE;
}

#undef tUsingRegisteredKeyItem
