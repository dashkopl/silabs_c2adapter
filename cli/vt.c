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
 *   Virtual Terminal, only support VT100 protocol.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if CLI_SUPPORT

#include "vt.h"

/******************************************************************************
 * FUNCTION NAME:
 *   VT_FlushRxFIFO
 * DESCRIPTION:
 *   Flush Rx FIFO.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2013.12.20        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_FlushRxFIFO(void)
{
    BOOL bIntState = DRV_INT_LockUartInterrupt();

    while (getchar(NO_PENDING) != -1)
    {}

    DRV_INT_UnlockUartInterrupt(bIntState);
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_MoveLeft
 * DESCRIPTION:
 *   Move Cursor backward by the specified number of columns without
 *    changing lines.
 *   If the cursor is already in the leftmost column,
 *    VT ignores this sequence.
 * PARAMETERS:
 *   columns : control cursor left-move n columns.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_MoveLeft(IN UINT8 count)
{
    if (count > 0)
    {
        printf("\x1B[%bdD", count);
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_MoveRight
 * DESCRIPTION:
 *   Move Cursor forward by the specified number of columns without
 *    changing lines.
 *   If the cursor is already in the rightmost column,
 *    VT ignores this sequence.
 * PARAMETERS:
 *   columns   : control cursor right-move n columns.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_MoveRight(IN UINT8 count)
{
    if (count > 0)
    {
        printf("\x1B[%bdC", count);
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_MoveUp
 * DESCRIPTION:
 *   Move Cursor up by the specified number of columns without changing lines.
 *   If the cursor is already in the top column, VT ignores this sequence.
 * PARAMETERS:
 *   columns : control cursor up-move n columns.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_MoveUp(IN UINT8 count)
{
    if (count > 0)
    {
        printf("\x1B[%bdA", count);
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_MoveDown
 * DESCRIPTION:
 *   Move Cursor up by the specified number of columns without changing lines.
 *   If the cursor is already in the top column, VT ignores this sequence.
 * PARAMETERS:
 *   columns : control cursor up-move n columns.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_MoveDown(IN UINT8 count)
{
    if (count > 0)
    {
        printf("\x1B[%bdB", count);
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_EraseLine
 * DESCRIPTION:
 *   Erase Text on the VT100 Line.
 * PARAMETERS:
 *   erase_mode =  0 : Erase from the cursor to the end of the line.
 *                 1 : Erase from the beginning of the line to the cursor.
 *                 2 : Clears the line but do not moves the cursor position.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_EraseLine(IN UINT8 erase_mode)
{
    printf("\x1B[%bdK", erase_mode);
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_EraseScreen
 * DESCRIPTION:
 *   Erase Text on the VT100 Line.
 * PARAMETERS:
 *   erase_mode =  0 : Erase from the cursor to the end of the screen.
 *                 1 : Erase from the beginning of the screen to the cursor.
 *                 2 : Clear screen, but do not moves the cursor position.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_EraseScreen(IN UINT8 erase_mode)
{
    printf("\x1B[%bdJ", erase_mode);
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_SetTextAttrib
 * DESCRIPTION:
 *   Set Text attributes.
 * PARAMETERS:
 *   attribute = '0'- NORNAL (Attributes off)
 *               '1'- HIGHT INTENSITY (Bold or increased intensity)
 *               '4'- Underscore
 *               '5'- BLINK
 *               '7'- INVERSE (Negative/reverse image)
 *               All other parameter values are ignored.
 *   Here is the table of attributes that are used with the SGR command:
 *     Parameter Attribute type
 *           0   Reset
 *           1   Bold
 *           2   Low intensity
 *           4   Underline
 *           5   Blinking
 *           6   Blinking
 *           7   Inverse
 *           8   Concealed
 *           10  Graphics off
 *           12  Graphics on
 *           21  End bold
 *           22  End low intensity
 *           24  End underline
 *           25  End blinking
 *           26  End blinking
 *           27  End inverse
 *           28  End concealed
 *           30  Black foreground
 *           31  Red foreground
 *           32  Green foreground
 *           33  Yellow foreground
 *           34  Blue foreground
 *           35  Magenta foreground
 *           36  Cyan foreground
 *           37  White foreground
 *           39  Default foreground
 *           40  Black background
 *           41  Red background
 *           42  Green background
 *           43  Yellow background
 *           44  Blue background
 *           45  Magenta background
 *           46  Cyan background
 *           47  White background
 *           49  Default background
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_SetTextAttrib(IN VT_TextAttrib attrib)
{
    printf("\x1B[%bdm", attrib);
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_CharacterSet
 * DESCRIPTION:
 *   Set VT100 character set.
 * PARAMETERS:
 *   set:  'A'- United Kingdom Set.
 *         'B'- ASCII character set.
 *         '0'- Special Graphics.
 *         '1'- Alternate Character ROM Standard Character Set.
 *         '2'- Alternate Character ROM Special Graphics.
 * RETURN:
 *   N/A
 * NOTES:
 *   The United Kingdom and ASCII sets conform to the "ISO international
 *    register of character sets to be used with escape sequences".
 *   The other sets are private character sets.
 *   Special graphics means that the graphic characters for the codes
 *    1378 to 1768 are replaced with other characters.
 *   The specified character set will be used until another SCS is received.
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_CharacterSet(IN UINT8 set)
{
    printf("\x1B(%bd", set);
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_SaveCursorPosition
 * DESCRIPTION:
 *   Save Cursor Position.
 * PARAMETERS:
 *   None
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_SaveCursorPosition(void)
{
    printf("\x1B\x37");
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_RestoreCursorPosition
 * DESCRIPTION:
 *   Restore Cursor Position.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_RestoreCursorPosition(void)
{
    printf("\x1B\x38");
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_SetCursorPosition
 * DESCRIPTION:
 *   Moves the cursor to the specified position.
 *   If you do not specify a position, the cursor moves to the home
 *    position ---- the upper-left corner of the screen (line 0, column 0).
 * PARAMETERS:
 *   column = Y
 *   row    = X
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_SetCursorPosition(IN UINT8 row, IN UINT8 column)
{
    printf("\x1B[%bd;%bdH", row, column);
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_GetCursorPosition
 * DESCRIPTION:
 *   Get the current cursor position, stored in row & column.
 *   If get success, return GT_TRUE, else return GT_FALSE.
 *   Return format: row = 18(the 18th row) , column = 20(the 20th column).
 *   Not return ascii.
 * PARAMETERS:
 *   column = Y
 *   row    = X
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
BOOL VT_GetCursorPosition(OUT UINT8 *row, OUT UINT8 *column)
{
    char    aRowBuf[10], aColumnBuf[10];
    int     vChar;
    UINT8   vLoop;
    BOOL    bResult = FALSE;
    BOOL    bIntState = DRV_INT_LockUartInterrupt();

    printf("\x1B[6n");

    /* Get 'ESC' response */
    if (getchar(PENDING) != '\x1B')
    {
        goto _exit;
    }

    /* Get '[' response */
    if (getchar(PENDING) != '[')
    {
        goto _exit;
    }

    /* Get row number */
    vLoop = 0;
    memset(aRowBuf, 0x0, sizeof(aRowBuf));
    while ((vChar = getchar(PENDING)) != ';')
    {
        if ((vChar >= '0') && (vChar <= '9'))
        {
            aRowBuf[vLoop++] = (char)vChar;
        }
        else
        {
            goto _exit;
        }
    }

    /* Get column number */
    vLoop = 0;
    memset(aColumnBuf, 0x0, sizeof(aColumnBuf));
    while ((vChar = getchar(PENDING)) != 'R')
    {
        if ((vChar >= '0') && (vChar <= '9'))
        {
            aColumnBuf[vLoop++] = (char)vChar;
        }
        else
        {
            goto _exit;
        }
    }

    *row    = (UINT8)strtol(aRowBuf,    NULL, 10);
    *column = (UINT8)strtol(aColumnBuf, NULL, 10);

    bResult = TRUE;
_exit:
    DRV_INT_UnlockUartInterrupt(bIntState);
    return bResult;
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_ClearScreen
 * DESCRIPTION:
 *   Clear screen.
 * PARAMETERS:
 *   clear_mode = 0 : Scroll Up to clear screen.
 *                1 : Do not Scroll Up to clear screen.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_ClearScreen(IN UINT8 clear_mode)
{
    switch (clear_mode)
    {
        case 0:
            VT_EraseScreen(2);
            VT_SetCursorPosition(0, 0);
            break;

        case 1:
            VT_EraseScreen(1);
            VT_SetCursorPosition(0, 0);

        default:
            break;
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   VT_Init
 * DESCRIPTION:
 *   VT Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2009.4.15        Panda.Xiong         Create/Update
 *****************************************************************************/
void VT_Init(void)
{
    /* flush Rx FIFO */
    VT_FlushRxFIFO();

    /* set screen to normal display */
    VT_SetTextAttrib(VT_TEXT_NORMAL);

    /* clear screen */
    VT_ClearScreen(0);
}

#endif

