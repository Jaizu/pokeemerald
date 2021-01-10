#include "global.h"
#include "letter.h"
#include "palette.h"
#include "main.h"
#include "gpu_regs.h"
#include "scanline_effect.h"
#include "task.h"
#include "malloc.h"
#include "decompress.h"
#include "bg.h"
#include "window.h"
#include "string_util.h"
#include "text.h"
#include "overworld.h"
#include "menu.h"
#include "script.h"
#include "event_data.h"
#include "constants/rgb.h"
#include "data/letters.h"

EWRAM_DATA static struct LetterSavedData sSavedLetterData = {0};
EWRAM_DATA static u8 *sLetterTilemapPtr = NULL;

void Special_ShowLetter(void);
static void CB2_ShowLetter(void);
static void MainCB2(void);
static void Task_LetterFadeIn(u8);
static void Task_LetterWaitForKeyPress(u8);
static void Task_LetterFadeOut(u8);
static void DisplayLetterText(void);
static void InitLetterBg(void);
static void InitLetterWindow(void);
static void PrintLetterText(u8 *, u8, u8);

static const struct BgTemplate sLetterBgTemplates[2] =
{
    {
        .bg = 0,
        .charBaseIndex = 1,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 6,
        .screenSize = 1,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sLetterWinTemplates[2] =
{
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 2,
        .width = 28,
        .height = 16,
        .paletteNum = 15,
        .baseBlock = 1,
    },
    DUMMY_WIN_TEMPLATE,
};

void Special_ShowLetter(void)
{
    ShowLetter(gSpecialVar_0x8004, CB2_ReturnToFieldContinueScriptPlayMapMusic);
    ScriptContext2_Enable();
}

void ShowLetter(u8 letterId, void (*callback)(void))
{
    sSavedLetterData.letterId = letterId;
    sSavedLetterData.callback = callback;
    
    SetMainCallback2(CB2_ShowLetter);
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_ShowLetter(void)
{
    SetVBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG3CNT, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG2CNT, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG1CNT, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG0CNT, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG3HOFS, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG3VOFS, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG2HOFS, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG2VOFS, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG1HOFS, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG1VOFS, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG0HOFS, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BG0VOFS, DISPCNT_MODE_0);
    DmaFill16(3, 0, VRAM, VRAM_SIZE);
    DmaFill32(3, 0, OAM, OAM_SIZE);
    DmaFill16(3, 0, PLTT, PLTT_SIZE);
    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    LoadPalette(sLetters[sSavedLetterData.letterId].palette, 0, 0x20);
    sLetterTilemapPtr = malloc(0x1000);
    InitLetterBg();
    InitLetterWindow();
    ResetTempTileDataBuffers();
    DecompressAndCopyTileDataToVram(1, sLetters[sSavedLetterData.letterId].tiles, 0, 0, 0);
    while (FreeTempTileDataBuffersIfPossible())
        ;
    LZDecompressWram(sLetters[sSavedLetterData.letterId].tilemap, sLetterTilemapPtr);
    CopyBgTilemapBufferToVram(1);
    DisplayLetterText();
    BlendPalettes(-1, 16, 0);
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
    EnableInterrupts(1);
    SetVBlankCallback(VBlankCB);
    SetMainCallback2(MainCB2);
    CreateTask(Task_LetterFadeIn, 0);
}

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void Task_LetterFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_LetterWaitForKeyPress;
}

static void Task_LetterWaitForKeyPress(u8 taskId)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_LetterFadeOut;
    }
}

static void Task_LetterFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        Free(sLetterTilemapPtr);
        FreeAllWindowBuffers();
        DestroyTask(taskId);
        SetMainCallback2(sSavedLetterData.callback);
    }
}

static void DisplayLetterText(void)
{
    SetGpuReg(REG_OFFSET_BG1HOFS, DISPCNT_MODE_0);
    StringExpandPlaceholders(gStringVar4, sLetters[sSavedLetterData.letterId].string);
    PrintLetterText(gStringVar4, sLetters[sSavedLetterData.letterId].textX, sLetters[sSavedLetterData.letterId].textY);
    PutWindowTilemap(0);
    CopyWindowToVram(0, 3);
}

static void InitLetterBg(void)
{
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sLetterBgTemplates, 2);
    SetBgTilemapBuffer(1, sLetterTilemapPtr);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    ShowBg(1);
    SetGpuReg(REG_OFFSET_BLDCNT, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BLDALPHA, DISPCNT_MODE_0);
    SetGpuReg(REG_OFFSET_BLDY, DISPCNT_MODE_0);
}

static void InitLetterWindow(void)
{
    InitWindows(sLetterWinTemplates);
    DeactivateAllTextPrinters();
    LoadPalette(gUnknown_0860F074, 0xF0, 0x20);
    FillWindowPixelBuffer(0, PIXEL_FILL(0));
    PutWindowTilemap(0);
}

static void PrintLetterText(u8 *text, u8 x, u8 y)
{
    u8 color[3] = {0, 2, 3};

    AddTextPrinterParameterized4(0, 2, x, y, 0, 0, color, -1, text);
}
