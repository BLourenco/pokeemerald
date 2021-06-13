#include "global.h"
#include "option_menu.h"
#include "main.h"
#include "menu.h"
#include "scanline_effect.h"
#include "palette.h"
#include "sprite.h"
#include "sound.h"
#include "task.h"
#include "malloc.h"
#include "bg.h"
#include "gpu_regs.h"
#include "window.h"
#include "text.h"
#include "text_window.h"
#include "international_string_util.h"
#include "strings.h"
#include "gba/m4a_internal.h"
#include "constants/rgb.h"

#define Y_DIFF 16 // Difference in pixels between items.

#define MENU_ITEMS_ON_SCREEN 7
#define MENU_OPTIONS_X_POSITION 104
#define MENU_OPTIONS_WIDTH 198

// Menu items page 1
enum
{
    MENUITEM_TEXTSPEED,
    MENUITEM_BUTTONMODE,
    MENUITEM_BATTLEANIMATIONS,
    MENUITEM_BATTLESTYLE,
    MENUITEM_HP_BAR,
    MENUITEM_EXP_BAR,
    MENUITEM_SPEAKERS,
    MENUITEM_MUSIC,
    MENUITEM_SFX,
    MENUITEM_FRAMETYPE,
    MENUITEM_ITEM_HEADERS,
    MENUITEM_AUTO_RUN,
    MENUITEM_AUTO_FIELD_MOVES,
    MENUITEM_MATCH_CALL_FILTER,
    MENUITEM_UNIT_SYSTEM,
    MENUITEM_CLOCK_FORMAT,
    MENUITEM_CANCEL,
    MENUITEM_COUNT,
};

// Window Ids
enum
{
    WIN_TEXT_OPTION,
    WIN_OPTIONS
};

struct OptionMenu
{
    u8 sel[MENUITEM_COUNT];
    int menuCursor; // Cursor position in the full list of options
    int visibleCursor; // Cursor position on screen
};

// this file's functions
static void Task_OptionMenuFadeIn(u8 taskId);
static void Task_OptionMenuProcessInput(u8 taskId);
static void Task_OptionMenuSave(u8 taskId);
static void Task_OptionMenuFadeOut(u8 taskId);
static void HighlightOptionMenuItem(u8 index);
static void TextSpeed_DrawChoices(int selection, int y, u8 textSpeed);
static void BattleAnimations_DrawChoices(int selection, int y, u8 textSpeed);
static void BattleStyle_DrawChoices(int selection, int y, u8 textSpeed);
static void HpExpBar_DrawChoices(int selection, int y, u8 textSpeed);
static void UnitSystem_DrawChoices(int selection, int y, u8 textSpeed);
static void Speakers_DrawChoices(int selection, int y, u8 textSpeed);
static void FrameType_DrawChoices(int selection, int y, u8 textSpeed);
static void ButtonMode_DrawChoices(int selection, int y, u8 textSpeed);
static void Music_DrawChoices(int selection, int y, u8 textSpeed);
static void SFX_DrawChoices(int selection, int y, u8 textSpeed);
static void ItemHeaders_DrawChoices(int selection, int y, u8 textSpeed);
static void AutoRun_DrawChoices(int selection, int y, u8 textSpeed);
static void AutoFieldMove_DrawChoices(int selection, int y, u8 textSpeed);
static void MatchCallFilter_DrawChoices(int selection, int y, u8 textSpeed);
static void ClockFormat_DrawChoices(int selection, int y, u8 textSpeed);
static int FrameType_ProcessInput(int selection);
static int FourOptions_ProcessInput(int selection);
static int ThreeOptions_ProcessInput(int selection);
static int TwoOptions_ProcessInput(int selection);
static int BattleStyle_ProcessInput(int selection);
static int ElevenOptions_ProcessInput(int selection);
static int Music_ProcessInput(int selection);
static int SFX_ProcessInput(int selection);
static void DrawTextOption(void);
static void DrawOptionMenuTexts(void);
static void DrawBgWindowFrames(void);

struct
{
    void (*drawChoices)(int selection, int y, u8 textSpeed);
    int (*processInput)(int selection);
} static const sItemFunctions[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]            = {TextSpeed_DrawChoices, FourOptions_ProcessInput},
    [MENUITEM_BATTLEANIMATIONS]     = {BattleAnimations_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_BATTLESTYLE]          = {BattleStyle_DrawChoices, BattleStyle_ProcessInput},
    [MENUITEM_SPEAKERS]             = {Speakers_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_BUTTONMODE]           = {ButtonMode_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_FRAMETYPE]            = {FrameType_DrawChoices, FrameType_ProcessInput},
    [MENUITEM_HP_BAR]               = {HpExpBar_DrawChoices, ElevenOptions_ProcessInput},
    [MENUITEM_EXP_BAR]              = {HpExpBar_DrawChoices, ElevenOptions_ProcessInput},
    [MENUITEM_UNIT_SYSTEM]          = {UnitSystem_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_MUSIC]                = {Music_DrawChoices, Music_ProcessInput},
    [MENUITEM_SFX]                  = {SFX_DrawChoices, SFX_ProcessInput},
    [MENUITEM_ITEM_HEADERS]         = {ItemHeaders_DrawChoices, ThreeOptions_ProcessInput},
    [MENUITEM_AUTO_RUN]             = {AutoRun_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_AUTO_FIELD_MOVES]     = {AutoFieldMove_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_MATCH_CALL_FILTER]    = {MatchCallFilter_DrawChoices, ThreeOptions_ProcessInput},
    [MENUITEM_CLOCK_FORMAT]         = {ClockFormat_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_CANCEL]               = {NULL, NULL},
};

// EWRAM vars
EWRAM_DATA static struct OptionMenu *sOptions = NULL;

// const rom data
static const u16 sOptionMenuText_Pal[] = INCBIN_U16("graphics/misc/option_menu_text.gbapal");
// note: this is only used in the Japanese release
static const u8 sEqualSignGfx[] = INCBIN_U8("graphics/misc/option_menu_equals_sign.4bpp");

static const u8 *const sOptionMenuItemsNames[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]            = gText_TextSpeed,
    [MENUITEM_BATTLEANIMATIONS]     = gText_BattleAnimations,
    [MENUITEM_BATTLESTYLE]          = gText_BattleStyle,
    [MENUITEM_SPEAKERS]             = gText_Speakers,
    [MENUITEM_BUTTONMODE]           = gText_ButtonMode,
    [MENUITEM_FRAMETYPE]            = gText_Frame,
    [MENUITEM_HP_BAR]               = gText_HpBar,
    [MENUITEM_EXP_BAR]              = gText_ExpBar,
    [MENUITEM_UNIT_SYSTEM]          = gText_UnitSystem,
    [MENUITEM_MUSIC]                = gText_Music,
    [MENUITEM_SFX]                  = gText_SFX,
    [MENUITEM_ITEM_HEADERS]         = gText_ItemHeaders,
    [MENUITEM_AUTO_RUN]             = gText_AutoRun,
    [MENUITEM_AUTO_FIELD_MOVES]     = gText_AutoFieldMoves,
    [MENUITEM_MATCH_CALL_FILTER]    = gText_MatchCallFilter,
    [MENUITEM_CLOCK_FORMAT]         = gText_ClockFormat,
    [MENUITEM_CANCEL]               = gText_OptionMenuCancel,
};


static const u8 *const sTextSpeedStrings[] = {gText_TextSpeedSlow, gText_TextSpeedMid, gText_TextSpeedFast, gText_TextSpeedInstant};

static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 26,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 5,
        .width = 26,
        .height = 14,
        .paletteNum = 1,
        .baseBlock = 0x36
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
   {
       .bg = 1,
       .charBaseIndex = 1,
       .mapBaseIndex = 30,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
       .baseTile = 0
   },
   {
       .bg = 0,
       .charBaseIndex = 1,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
       .baseTile = 0
   }
};

static const u16 sOptionMenuBg_Pal[] = {RGB(17, 18, 31)};

// code
static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void DrawChoices(u32 id, int y, u8 textSpeed)
{
    if (sItemFunctions[id].drawChoices != NULL)
        sItemFunctions[id].drawChoices(sOptions->sel[id], y, textSpeed);
}

void CB2_InitOptionMenu(void)
{
    u32 i, taskId;
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void*)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sOptionMenuBgTemplates, ARRAY_COUNT(sOptionMenuBgTemplates));
        ResetBgPositions();
        InitWindows(sOptionMenuWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_DARKEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;
    case 4:
        LoadPalette(sOptionMenuBg_Pal, 0, sizeof(sOptionMenuBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, 0x70, 0x20);
        gMain.state++;
        break;
    case 5:
        LoadPalette(sOptionMenuText_Pal, 16, sizeof(sOptionMenuText_Pal));
        gMain.state++;
        break;
    case 6:
        PutWindowTilemap(0);
        DrawTextOption();
        gMain.state++;
        break;
    case 7:
        gMain.state++;
        break;
    case 8:
        PutWindowTilemap(1);
        DrawOptionMenuTexts();
        gMain.state++;
    case 9:
        DrawBgWindowFrames();
        gMain.state++;
        break;
    case 10:
        taskId = CreateTask(Task_OptionMenuFadeIn, 0);

        sOptions = AllocZeroed(sizeof(*sOptions));
        sOptions->sel[MENUITEM_TEXTSPEED] = gSaveBlock2Ptr->optionsTextSpeed;
        sOptions->sel[MENUITEM_BATTLEANIMATIONS] = gSaveBlock2Ptr->optionsBattleAnimations;
        sOptions->sel[MENUITEM_BATTLESTYLE] = gSaveBlock2Ptr->optionsBattleStyle;
        sOptions->sel[MENUITEM_SPEAKERS] = gSaveBlock2Ptr->optionsSpeakers;
        sOptions->sel[MENUITEM_BUTTONMODE] = gSaveBlock2Ptr->optionsButtonMode;
        sOptions->sel[MENUITEM_FRAMETYPE] = gSaveBlock2Ptr->optionsWindowFrameType;
        sOptions->sel[MENUITEM_HP_BAR] = gSaveBlock2Ptr->optionsHpBarSpeed;
        sOptions->sel[MENUITEM_EXP_BAR] = gSaveBlock2Ptr->optionsExpBarSpeed;
        sOptions->sel[MENUITEM_UNIT_SYSTEM] = gSaveBlock2Ptr->optionsUnitSystem;
        sOptions->sel[MENUITEM_MUSIC] = gSaveBlock2Ptr->optionsMusic;
        sOptions->sel[MENUITEM_SFX] = gSaveBlock2Ptr->optionsSFX;
        sOptions->sel[MENUITEM_ITEM_HEADERS] = gSaveBlock2Ptr->optionsItemHeaders;
        sOptions->sel[MENUITEM_AUTO_RUN] = gSaveBlock2Ptr->optionsAutoRun;
        sOptions->sel[MENUITEM_AUTO_FIELD_MOVES] = gSaveBlock2Ptr->optionsAutoFieldMoves;
        sOptions->sel[MENUITEM_MATCH_CALL_FILTER] = gSaveBlock2Ptr->optionsPokeNavCallFilter;
        sOptions->sel[MENUITEM_CLOCK_FORMAT] = gSaveBlock2Ptr->optionsClockFormat;

        for (i = 0; i < 7; i++)
            DrawChoices(i, i * Y_DIFF, 0xFF);

        HighlightOptionMenuItem(sOptions->menuCursor);

        CopyWindowToVram(WIN_OPTIONS, 3);
        gMain.state++;
        break;
    case 11:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void Task_OptionMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_OptionMenuProcessInput;
}

static void ScrollMenu(int direction)
{
    int menuItem, pos;
    if (direction == 0) // scroll down
        menuItem = sOptions->menuCursor + 3, pos = 6;
    else
        menuItem = sOptions->menuCursor - 3, pos = 0;

    // Hide one
    ScrollWindow(WIN_OPTIONS, direction, Y_DIFF, PIXEL_FILL(0));
    // Show one
    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(1), 0, Y_DIFF * pos, 26 * 8, Y_DIFF);
    // Print
    DrawChoices(menuItem, pos * Y_DIFF, 0xFF);
    AddTextPrinterParameterized(WIN_OPTIONS, 1, sOptionMenuItemsNames[menuItem], 8, (pos * Y_DIFF) + 1, 0xFF, NULL);
    CopyWindowToVram(WIN_OPTIONS, 2);
}

static void ScrollAll(int direction) // to bottom or top
{
    int i, menuItem, pos;

    // Clear moved items
    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(1), 0, 0, 26 * 8, Y_DIFF * MENU_ITEMS_ON_SCREEN);

    // Print new texts
    for (i = 0; i < MENU_ITEMS_ON_SCREEN; i++)
    {
        if (direction == 0) // From top to bottom
        {
            menuItem = MENUITEM_COUNT - 1 - i;
            pos = MENU_ITEMS_ON_SCREEN - 1 - i;
        }
        else // From bottom to top
        {
            menuItem = i;
            pos = i;
        }

        DrawChoices(menuItem, pos * Y_DIFF, 0xFF);
        AddTextPrinterParameterized(WIN_OPTIONS, 1, sOptionMenuItemsNames[menuItem], 8, (pos * Y_DIFF) + 1, 0xFF, NULL);
    }
    CopyWindowToVram(WIN_OPTIONS, 2);
}

static void Task_OptionMenuProcessInput(u8 taskId)
{
    int i, scrollCount = 0, itemsToRedraw;
    if (JOY_NEW(A_BUTTON))
    {
        if (sOptions->menuCursor == MENUITEM_CANCEL)
            gTasks[taskId].func = Task_OptionMenuSave;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        gTasks[taskId].func = Task_OptionMenuSave;
    }
    else if (JOY_NEW(DPAD_UP))
    {
        if (sOptions->visibleCursor == 3) // don't advance visible cursor until scrolled to the bottom
        {
            if (--sOptions->menuCursor == sOptions->visibleCursor - 1)
                sOptions->visibleCursor--;
            else
                ScrollMenu(1);
        }
        else
        {
            if (--sOptions->menuCursor < 0) // Scroll all the way to the bottom.
            {
                sOptions->visibleCursor = sOptions->menuCursor = 3;
                ScrollAll(0);
                sOptions->visibleCursor = 6;
                sOptions->menuCursor = MENUITEM_COUNT - 1;
            }
            else
            {
                sOptions->visibleCursor--;
            }
        }
        HighlightOptionMenuItem(sOptions->visibleCursor);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        if (sOptions->visibleCursor == 3) // don't advance visible cursor until scrolled to the bottom
        {
            if (++sOptions->menuCursor == MENUITEM_COUNT - 3)
                sOptions->visibleCursor++;
            else
                ScrollMenu(0);
        }
        else
        {
            if (++sOptions->menuCursor >= MENUITEM_COUNT) // Scroll all the way to the tom.
            {
                sOptions->visibleCursor = 3;
                sOptions->menuCursor = MENUITEM_COUNT - 4;
                ScrollAll(1);
                sOptions->visibleCursor = sOptions->menuCursor = 0;
            }
            else
            {
                sOptions->visibleCursor++;
            }
        }
        HighlightOptionMenuItem(sOptions->visibleCursor);
    }
    else if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        int cursor = sOptions->menuCursor;
        u8 previousOption = sOptions->sel[cursor];
        if (sItemFunctions[cursor].processInput != NULL)
            sOptions->sel[cursor] = sItemFunctions[cursor].processInput(previousOption);

        if (previousOption != sOptions->sel[cursor])
            DrawChoices(cursor, sOptions->visibleCursor * Y_DIFF, 0);
    }
}

static void Task_OptionMenuSave(u8 taskId)
{
    gSaveBlock2Ptr->optionsTextSpeed = sOptions->sel[MENUITEM_TEXTSPEED];
    gSaveBlock2Ptr->optionsBattleAnimations = sOptions->sel[MENUITEM_BATTLEANIMATIONS];
    gSaveBlock2Ptr->optionsBattleStyle = sOptions->sel[MENUITEM_BATTLESTYLE];
    gSaveBlock2Ptr->optionsSpeakers = sOptions->sel[MENUITEM_SPEAKERS];
    gSaveBlock2Ptr->optionsButtonMode = sOptions->sel[MENUITEM_BUTTONMODE];
    gSaveBlock2Ptr->optionsWindowFrameType = sOptions->sel[MENUITEM_FRAMETYPE];
    gSaveBlock2Ptr->optionsHpBarSpeed = sOptions->sel[MENUITEM_HP_BAR];
    gSaveBlock2Ptr->optionsExpBarSpeed = sOptions->sel[MENUITEM_EXP_BAR];
    gSaveBlock2Ptr->optionsUnitSystem = sOptions->sel[MENUITEM_UNIT_SYSTEM];
    gSaveBlock2Ptr->optionsItemHeaders = sOptions->sel[MENUITEM_ITEM_HEADERS];
    gSaveBlock2Ptr->optionsMusic = sOptions->sel[MENUITEM_MUSIC];
    gSaveBlock2Ptr->optionsSFX = sOptions->sel[MENUITEM_SFX];
    gSaveBlock2Ptr->optionsAutoRun = sOptions->sel[MENUITEM_AUTO_RUN];
    gSaveBlock2Ptr->optionsAutoFieldMoves = sOptions->sel[MENUITEM_AUTO_FIELD_MOVES];
    gSaveBlock2Ptr->optionsPokeNavCallFilter = sOptions->sel[MENUITEM_MATCH_CALL_FILTER];
    gSaveBlock2Ptr->optionsClockFormat = sOptions->sel[MENUITEM_CLOCK_FORMAT];

    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    gTasks[taskId].func = Task_OptionMenuFadeOut;
}

static void Task_OptionMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        FREE_AND_SET_NULL(sOptions);
        SetMainCallback2(gMain.savedCallback);
    }
}

static void HighlightOptionMenuItem(u8 index)
{
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(Y_DIFF, DISPLAY_WIDTH - 16));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(index * Y_DIFF + 40, index * Y_DIFF + 56));
}

// Process Input functions
static int XOptions_ProcessInput(int x, int selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (++selection > (x - 1))
            selection = 0;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (--selection < 0)
            selection = (x - 1);
    }

    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(1), MENU_OPTIONS_X_POSITION, sOptions->visibleCursor * Y_DIFF, 26 * 8 - MENU_OPTIONS_X_POSITION, Y_DIFF);
    CopyWindowToVram(WIN_OPTIONS, 2);
    return selection;
}

static int ThreeOptions_ProcessInput(int selection)
{
    return XOptions_ProcessInput(3, selection);
}

static int FourOptions_ProcessInput(int selection)
{
    return XOptions_ProcessInput(4, selection);
}

static int ElevenOptions_ProcessInput(int selection)
{
    return XOptions_ProcessInput(11, selection);
}

static int TwoOptions_ProcessInput(int selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
        selection ^= 1;

    return selection;
}

static int BattleStyle_ProcessInput(int selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
        selection ^= 1;

    return selection;
}

static int Music_ProcessInput(int selection)
{
    selection = TwoOptions_ProcessInput(selection);
    if (selection == 0)
    {
        PlayBGM(0);
        gDisableMusic = TRUE;
    }
    else
    {
        gDisableMusic = FALSE;
        PlayNewMapMusic(GetCurrentMapMusic());
    }

    return selection;
}

static int SFX_ProcessInput(int selection)
{
    selection = TwoOptions_ProcessInput(selection);
    if (selection == 0)
    {
        gDisableSFX = TRUE;
    }
    else
    {
        gDisableSFX = FALSE;
    }

    return selection;
}

static int FrameType_ProcessInput(int selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < WINDOW_FRAMES_COUNT - 1)
            selection++;
        else
            selection = 0;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, 0x70, 0x20);
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = WINDOW_FRAMES_COUNT - 1;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, 0x70, 0x20);
    }
    return selection;
}

static int GetMiddleX(const u8 *txt1, const u8 *txt2, const u8 *txt3)
{
    int xMid;
    int widthLeft = GetStringWidth(1, txt1, 0);
    int widthMid = GetStringWidth(1, txt2, 0);
    int widthRight = GetStringWidth(1, txt3, 0);

    widthMid -= (MENU_OPTIONS_WIDTH - MENU_OPTIONS_X_POSITION);
    xMid = (widthLeft - widthMid - widthRight) / 2 + MENU_OPTIONS_X_POSITION;
    return xMid;
}

// Draw Choices functions
static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, u8 style, u8 textSpeed)
{
    u8 dst[32]; // Needed to increase this from 16 to 32 to get the whole choice to appear
    u32 i;

    for (i = 0; *text != EOS && i <= 35; i++)
        dst[i] = *(text++);

    if (style != 0)
    {
        dst[2] = 4;
        dst[5] = 5;
    }

    dst[i] = EOS;
    AddTextPrinterParameterized(WIN_OPTIONS, 1, dst, x, y + 1, textSpeed, NULL);
}

static void HpExpBar_DrawChoices(int selection, int y, u8 textSpeed)
{
    if (selection == 0)
    {
        DrawOptionMenuChoice(gText_HpExpBarSpeedDefault, MENU_OPTIONS_X_POSITION, y, 1, textSpeed);
    }
    else if (selection == 10)
    {
        DrawOptionMenuChoice(gText_TextSpeedInstant, MENU_OPTIONS_X_POSITION, y, 1, textSpeed);
    }
    else
    {
        u8 textPlus[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}+1{0x77}{0x77}{0x77}{0x77}{0x77}"); // 0x77 is to clear INSTANT text
        textPlus[7] = CHAR_0 + selection;
        DrawOptionMenuChoice(textPlus, MENU_OPTIONS_X_POSITION, y, 1, textSpeed);
    }
}

static void MatchCallFilter_DrawChoices(int selection, int y, u8 textSpeed)
{
    switch (selection)
    {
        default:
        case OPTIONS_MATCH_CALL_FILTER_ALLOW_ALL:
            DrawOptionMenuChoice(gText_MatchCallFilterAllowAll, MENU_OPTIONS_X_POSITION, y, 1, textSpeed);
            break;
        case OPTIONS_MATCH_CALL_FILTER_ALLOW_SCRIPTED_AND_REMATCH_NOTIF:
            DrawOptionMenuChoice(gText_MatchCallFilterAllowScriptedAndRematchNotifs, MENU_OPTIONS_X_POSITION, y, 1, textSpeed);
            break;
        case OPTIONS_MATCH_CALL_FILTER_ALLOW_SCRIPTED_ONLY:
            DrawOptionMenuChoice(gText_MatchCallFilterAllowScriptedOnly, MENU_OPTIONS_X_POSITION, y, 1, textSpeed);
            break;
    }
}

static void BattleAnimations_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0};

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_BattleAnimationsOff, MENU_OPTIONS_X_POSITION, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_BattleAnimationsOn, GetStringRightAlignXOffset(1, gText_BattleAnimationsOn, MENU_OPTIONS_WIDTH), y, styles[1], textSpeed);
}

static void BattleStyle_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0, 0};

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_BattleStyleShift, MENU_OPTIONS_X_POSITION, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_BattleStyleSet, GetStringRightAlignXOffset(1, gText_BattleStyleSet, MENU_OPTIONS_WIDTH), y, styles[1], textSpeed);
}

static void UnitSystem_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0, 0};

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_UnitSystemMetric, MENU_OPTIONS_X_POSITION, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_UnitSystemImperial, GetStringRightAlignXOffset(1, gText_UnitSystemImperial, MENU_OPTIONS_WIDTH), y, styles[1], textSpeed);
}

static void FourOptions_DrawChoices(const u8 *const *const strings, int selection, int y, u8 textSpeed)
{
    static const u8 choiceOrders[][3] =
    {
        {0, 1, 2},
        {0, 1, 2},
        {1, 2, 3},
        {1, 2, 3},
    };
    
    u8 styles[4] = {0};
    int xMid;
    const u8 *order = choiceOrders[selection];

    styles[selection] = 1;
    xMid = GetMiddleX(strings[order[0]], strings[order[1]], strings[order[2]]);

    DrawOptionMenuChoice(strings[order[0]], MENU_OPTIONS_X_POSITION, y, styles[order[0]], textSpeed);
    DrawOptionMenuChoice(strings[order[1]], xMid, y, styles[order[1]], textSpeed);
    DrawOptionMenuChoice(strings[order[2]], GetStringRightAlignXOffset(1, strings[order[2]], MENU_OPTIONS_WIDTH), y, styles[order[2]], textSpeed);
}

static void TextSpeed_DrawChoices(int selection, int y, u8 textSpeed)
{
    FourOptions_DrawChoices(sTextSpeedStrings, selection, y, textSpeed);
}


static void Speakers_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0, 0};

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_SpeakersMono, MENU_OPTIONS_X_POSITION, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_SpeakersStereo, GetStringRightAlignXOffset(1, gText_SpeakersStereo, MENU_OPTIONS_WIDTH), y, styles[1], textSpeed);
}

static void FrameType_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 text[16];
    u32 n = selection + 1;
    u32 i;

    for (i = 0; gText_FrameTypeNumber[i] != EOS && i <= 5; i++)
        text[i] = gText_FrameTypeNumber[i];

    // Convert a number to decimal string
    if (n / 10 != 0)
    {
        text[i] = n / 10 + CHAR_0;
        i++;
        text[i] = n % 10 + CHAR_0;
        i++;
    }
    else
    {
        text[i] = n % 10 + CHAR_0;
        i++;
        text[i] = 0x77;
        i++;
    }

    text[i] = EOS;

    DrawOptionMenuChoice(gText_FrameType, MENU_OPTIONS_X_POSITION, y, 0, textSpeed);
    DrawOptionMenuChoice(text, 128, y, 1, textSpeed);
}

static void ButtonMode_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0, 0};

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_ButtonTypeNormal, MENU_OPTIONS_X_POSITION, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_ButtonTypeLEqualsA, GetStringRightAlignXOffset(1, gText_ButtonTypeLEqualsA, MENU_OPTIONS_WIDTH), y, styles[1], textSpeed);
}

static void Music_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0};

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_BattleAnimationsOff, MENU_OPTIONS_X_POSITION, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_BattleAnimationsOn, GetStringRightAlignXOffset(1, gText_BattleAnimationsOn, MENU_OPTIONS_WIDTH), y, styles[1], textSpeed);
}

static void SFX_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0};

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_BattleAnimationsOff, MENU_OPTIONS_X_POSITION, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_BattleAnimationsOn, GetStringRightAlignXOffset(1, gText_BattleAnimationsOn, MENU_OPTIONS_WIDTH), y, styles[1], textSpeed);
}

static void ItemHeaders_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[3] = {0, 0, 0};
    int xMid = GetMiddleX(gText_ItemHeadersNever, gText_ItemHeadersNewItems, gText_ItemHeadersAlways);

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_ItemHeadersNever, MENU_OPTIONS_X_POSITION, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_ItemHeadersNewItems, xMid, y, styles[1], textSpeed);
    DrawOptionMenuChoice(gText_ItemHeadersAlways, GetStringRightAlignXOffset(1, gText_ItemHeadersAlways, MENU_OPTIONS_WIDTH), y, styles[2], textSpeed);
}

static void AutoRun_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0};

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_BattleAnimationsOff, MENU_OPTIONS_X_POSITION, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_BattleAnimationsOn, GetStringRightAlignXOffset(1, gText_BattleAnimationsOn, MENU_OPTIONS_WIDTH), y, styles[1], textSpeed);
}

static void AutoFieldMove_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0};

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_BattleAnimationsOff, MENU_OPTIONS_X_POSITION, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_BattleAnimationsOn, GetStringRightAlignXOffset(1, gText_BattleAnimationsOn, MENU_OPTIONS_WIDTH), y, styles[1], textSpeed);
}

static void ClockFormat_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0};

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_ClockFormatAMPM, MENU_OPTIONS_X_POSITION, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_ClockFormat24Hr, GetStringRightAlignXOffset(1, gText_ClockFormat24Hr, MENU_OPTIONS_WIDTH), y, styles[1], textSpeed);
}

static void DrawTextOption(void)
{
    FillWindowPixelBuffer(WIN_TEXT_OPTION, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_TEXT_OPTION, 1, gText_Option, 8, 1, 0, NULL);
    CopyWindowToVram(WIN_TEXT_OPTION, 3);
}

static void DrawOptionMenuTexts(void)
{
    u32 i;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < 7; i++)
        AddTextPrinterParameterized(WIN_OPTIONS, 1, sOptionMenuItemsNames[i], 8, (i * Y_DIFF) + 1, 0, NULL);

    CopyWindowToVram(WIN_OPTIONS, 3);
}

#define TILE_TOP_CORNER_L 0x1A2
#define TILE_TOP_EDGE     0x1A3
#define TILE_TOP_CORNER_R 0x1A4
#define TILE_LEFT_EDGE    0x1A5
#define TILE_RIGHT_EDGE   0x1A7
#define TILE_BOT_CORNER_L 0x1A8
#define TILE_BOT_EDGE     0x1A9
#define TILE_BOT_CORNER_R 0x1AA

static void DrawBgWindowFrames(void)
{
    //                     bg, tile,              x, y, width, height, palNum
    // Draw title window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  0, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1,  3,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2,  3, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28,  3,  1,  1,  7);

    // Draw options list window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  4, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 19,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 19, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 19,  1,  1,  7);

    CopyBgTilemapBufferToVram(1);
}
