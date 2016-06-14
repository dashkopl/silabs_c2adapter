/******************************************************************************
 *
 * COPYRIGHT:
 *   Copyright (c) 2016      CreaLights Inc.      All rights reserved.
 *
 *   This is unpublished proprietary source code of CreaLights Inc.
 *   The copyright notice above does not evidence any actual or intended
 *   publication of such source code.
 *
 * DESCRIPTION:
 *   Thread: CLI related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"

#if CLI_SUPPORT

#define __CLI_INTERNAL
#include "cli_porting.h"


typedef char CMD_BUF_T[CLI_CMD_MAX_LEN+1];

#if CLI_CMD_HISTORY_SUPPORT
static UINT8     SEG_XDATA  vHistoryLatest;
static UINT8     SEG_XDATA  vHistoryCurrent;
static CMD_BUF_T SEG_XDATA  aHistoryBuf[CLI_CMD_HISTORY_MAX_ITEM];
#define cli_HistoryGetNext()    (vHistoryCurrent++,                                     \
                                 vHistoryCurrent &= (CLI_CMD_HISTORY_MAX_ITEM-1),       \
                                 aHistoryBuf[vHistoryCurrent])
#define cli_HistoryGetPrev()    (vHistoryCurrent--,                                     \
                                 vHistoryCurrent &= (CLI_CMD_HISTORY_MAX_ITEM-1),       \
                                 aHistoryBuf[vHistoryCurrent])
#define cli_HistoryAppend(_cmd) do {                                                    \
                                    if (!IsStrEmpty(_cmd))                              \
                                    {                                                   \
                                        strcpy(aHistoryBuf[vHistoryLatest++], (_cmd));  \
                                        vHistoryLatest &= (CLI_CMD_HISTORY_MAX_ITEM-1), \
                                        strcpy(aHistoryBuf[vHistoryLatest], "");        \
                                    }                                                   \
                                    vHistoryCurrent = vHistoryLatest;                   \
                                } while (0)
#define cli_HistoryInit()       do {                                                    \
                                	memset(aHistoryBuf, 0x0, sizeof(aHistoryBuf));      \
                                    vHistoryCurrent = vHistoryLatest = 0;               \
                                } while (0)
#endif

#if 1

char  SEG_XDATA * SEG_XDATA aCmdParam[CLI_CMD_MAX_PARAM];
UINT8 SEG_XDATA             vCmdParamCount;

static CMD_BUF_T SEG_XDATA  aCmdBuf;
static UINT8     SEG_XDATA  vCmdBufCount;

static struct
{
    void           (SEG_CODE *pExec)(void);
    char SEG_CODE  *pUsage;
} SEG_CODE aCmdTable[] = CLI_CMD_LIST;

static void cli_ShowHelp(void)
{
    UINT8   vLoop;

    VT_Printf("\n\rAvailable Commands :");

    for (vLoop = 0; vLoop < COUNT_OF(aCmdTable); vLoop++)
    {
        VT_Printf("\n\r %s", aCmdTable[vLoop].pUsage);
    }

  #if CLI_CONTINUOUS_CMD_SUPPORT
    VT_Printf("\n\r"
              "\n\rContinuous Execute Command:"
              "\n\r <command> <params> %s",
              CLI_CONTINUOUS_CMD_KEYWORD);
  #endif
}

static BOOL cli_ReadCmd(void)
{
  #define CLEAR_CMD_ON_SCREEN()                                     \
        do {                                                        \
            /* move cursor to the end of this command */            \
            while (vCmdBufCount < strlen(aCmdBuf))                  \
            {                                                       \
                VT_MoveRight(1);                                    \
                vCmdBufCount++;                                     \
            }                                                       \
                                                                    \
            /* clear command on screen */                           \
            while (vCmdBufCount > 0)                                \
            {                                                       \
                VT_Printf("\b \b");                                 \
                vCmdBufCount--;                                     \
            }                                                       \
        } while (0)

    int vKey;

    while ((vKey = VT_ReadKey(NO_PENDING)) != -1)
    {
        switch (vKey)
        {
            case VT_KEY_CR:     /* command received */
            case VT_KEY_LF:
                _trimAll(aCmdBuf);
          #if CLI_CMD_HISTORY_SUPPORT
                cli_HistoryAppend(aCmdBuf);
          #endif
                vCmdBufCount = 0;
                return TRUE;

          #if CLI_CMD_HISTORY_SUPPORT
            case VT_KEY_UP:
                CLEAR_CMD_ON_SCREEN();

                /* load from history */
                strcpy(aCmdBuf, cli_HistoryGetPrev());
                vCmdBufCount = strlen(aCmdBuf);

                /* display new command */
                VT_Printf("%s", aCmdBuf);
                break;

            case VT_KEY_DOWN:
                CLEAR_CMD_ON_SCREEN();

                /* load from history */
                strcpy(aCmdBuf, cli_HistoryGetNext());
                vCmdBufCount = strlen(aCmdBuf);

                /* display new command */
                VT_Printf("%s", aCmdBuf);
                break;
          #endif

          #if CLI_CMD_EDIT_SUPPORT
    		case VT_KEY_CTRL_Z:  /* clear current command */
                CLEAR_CMD_ON_SCREEN();
                vCmdBufCount = 0;
                break;

    		case VT_KEY_LEFT:
    			if (vCmdBufCount > 0)
    			{
    				VT_MoveLeft(1);
                    vCmdBufCount--;
    			}
    			break;

    		case VT_KEY_RIGHT:
    			if (vCmdBufCount < strlen(aCmdBuf))
    			{
    				VT_MoveRight(1);
                    vCmdBufCount++;
    			}
    			break;

    		case VT_KEY_HOME:
                VT_MoveLeft(vCmdBufCount);
                vCmdBufCount = 0;
                break;

    		case VT_KEY_END:
                VT_MoveRight(strlen(aCmdBuf) - vCmdBufCount);
                vCmdBufCount = strlen(aCmdBuf);
                break;

            case VT_KEY_DEL:
                if (vCmdBufCount < strlen(aCmdBuf))
                {
                    strcpy(aCmdBuf+vCmdBufCount, aCmdBuf+vCmdBufCount+1);
                    VT_SaveCursorPosition();
                    VT_Printf("%s ", aCmdBuf+vCmdBufCount);
                    VT_RestoreCursorPosition();
                }
                break;
          #endif

            case VT_KEY_BS:
                if (vCmdBufCount > 0)
                {
                    vCmdBufCount--;
                    strcpy(aCmdBuf+vCmdBufCount, aCmdBuf+vCmdBufCount+1);
                    VT_MoveLeft(1);
                    VT_SaveCursorPosition();
                    VT_Printf("%s ", aCmdBuf+vCmdBufCount);
                    VT_RestoreCursorPosition();
                }
                break;

            default:
                if ((vKey >= 0x20) && (vKey < 0x7F))
                {
                    /* visible character */

                    UINT8   i = strlen(aCmdBuf);

                    /* if command buffer not full, record it */
                    if (i <= CLI_CMD_MAX_LEN)
                    {
                        aCmdBuf[i+1] = '\0';
                        while (i>vCmdBufCount)
                        {
                            aCmdBuf[i] = aCmdBuf[i-1];
                            i--;
                        }
                        aCmdBuf[i] = vKey;
                        vCmdBufCount++;

                        VT_Printf("%bc", (UINT8)vKey);
                        VT_SaveCursorPosition();
                        VT_Printf("%s", aCmdBuf+vCmdBufCount);
                        VT_RestoreCursorPosition();
                    }
                }
                break;
        }
    }

    /* no command received yet */
    return FALSE;
}


static void cli_ParseCmd(void)
{
    char SEG_XDATA *ptr;

    ptr = (char SEG_XDATA *)aCmdBuf;
    vCmdParamCount = 0;
    while (*ptr != '\0')
    {
        /* skip spaces */
        while (*ptr == ' ')
        {
            ptr++;
        }

        if (*ptr == '\0')
        {
            return;
        }

        aCmdParam[vCmdParamCount++] = ptr;
        while (*ptr != ' ')
        {
            if (*ptr == '\0')
            {
                return;
            }

            ptr++;
        }

        /* add end character to this parameter */
        *ptr++ = '\0';

        if (vCmdParamCount > CLI_CMD_MAX_PARAM)
        {
            break;
        }
    }

    return;
}

static void cli_ExecCmd(void)
{
    UINT8   vLoop;

    if (vCmdParamCount == 0)
    {
        /* empty command */
        return;
    }

    if (strcmp(aCmdParam[0], "?") == 0)
    {
        cli_ShowHelp();
    }
  #if CLI_COMMENT_SUPPORT
    else if (strncmp(aCmdParam[0], CLI_COMMENT_KEYWORD, 1) == 0)
    {
        /* comment, skip it */
    }
  #endif
    else
    {
        /* search & execute command */
        for (vLoop = 0; vLoop < COUNT_OF(aCmdTable); vLoop++)
        {
            if ((strncmp(aCmdParam[0], aCmdTable[vLoop].pUsage, strlen(aCmdParam[0])) == 0)
                && ((aCmdTable[vLoop].pUsage[strlen(aCmdParam[0])] == ' ')
                    || (aCmdTable[vLoop].pUsage[strlen(aCmdParam[0])] == '\0')))
            {
              #if CLI_CONTINUOUS_CMD_SUPPORT
                if ((vCmdParamCount > 1)
                    && IsStrEqual(aCmdParam[vCmdParamCount-1], CLI_CONTINUOUS_CMD_KEYWORD))
                {
                    VT_ClearScreen(0);

                    for (;;)
                    {
                        VT_ClearScreen(1);

                        aCmdTable[vLoop].pExec();

                        /* display status bar */
                        VT_Printf("\n\n\r             ");
                        VT_SetTextAttrib(VT_TEXT_INVERSE);
                        VT_Printf("----------    Press 'ESC' to Exit    ----------");
                        VT_SetTextAttrib(VT_TEXT_NORMAL);

                        if (VT_ReadKey(1000) == VT_KEY_ESC)
                        {
                            break;
                        }
                    }
                }
                else
              #endif
                {
                    aCmdTable[vLoop].pExec();
                }

                break;
            }
        }
        if (vLoop == COUNT_OF(aCmdTable))
        {
            VT_Printf("\n\rInvalid command!");
        }
    }

    /* reset command buffer & parameters */
    aCmdBuf[0] = '\0';
    vCmdBufCount = 0;
    vCmdParamCount = 0;
}

#endif


#if 1

static OS_TCB   vTCB_Cli;

/******************************************************************************
 * FUNCTION NAME:
 *   Thread_CLI_Entry
 * DESCRIPTION:
 *   CLI Thread Entry.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   OS_HANDLE
 * NOTES:
 *   N/A
 * HISTORY:
 *   2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
OS_HANDLE Thread_CLI_Entry(void)
{
    PT_BEGIN(&vTCB_Cli);

    for (;;)
    {
        if (cli_ReadCmd())
        {
            /* parse command */
            cli_ParseCmd();

            /* execute command */
            cli_ExecCmd();

            /* display command prompt */
            CLI_DISPLAY_CMD_PROMPT();
        }

        OS_SLEEP_MS(&vTCB_Cli, 5);
    }

    PT_END(&vTCB_Cli);
}


/******************************************************************************
 * FUNCTION NAME:
 *   Thread_CLI_Init
 * DESCRIPTION:
 *   N/A
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
void Thread_CLI_Init(void)
{
    PT_INIT(&vTCB_Cli);

    /* reset command buffer & parameters */
    aCmdBuf[0] = '\0';
    vCmdBufCount = 0;
    vCmdParamCount = 0;

    /* init VT */
    VT_Init();

  #if CLI_CMD_HISTORY_SUPPORT
    cli_HistoryInit();
  #endif

  #if CLI_BANNER_SUPPORT
    /* display banner */
    CLI_DISPLAY_BANNER();
  #endif

    /* display command prompt */
    CLI_DISPLAY_CMD_PROMPT();
}

#endif

#endif

