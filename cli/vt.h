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

#ifndef __VT_H
#define __VT_H


#if CLI_SUPPORT

/* key code definition */
#if 1

/* standard key ascii value */
#define VT_KEY_BS           (0x08)
#define VT_KEY_TAB          (0x09)
#define VT_KEY_LF           (0x0A)
#define VT_KEY_CR           (0x0D)
#define VT_KEY_ESC          (0x1B)

#define VT_KEY_CTRL_A       (0x01)
#define VT_KEY_CTRL_B       (0x02)
#define VT_KEY_CTRL_C       (0x03)
#define VT_KEY_CTRL_D       (0x04)
#define VT_KEY_CTRL_E       (0x05)
#define VT_KEY_CTRL_F       (0x06)
#define VT_KEY_CTRL_G       (0x07)
#define VT_KEY_CTRL_H       (0x08)
#define VT_KEY_CTRL_I       (0x09)
#define VT_KEY_CTRL_J       (0x0A)
#define VT_KEY_CTRL_K       (0x0B)
#define VT_KEY_CTRL_L       (0x0C)
#define VT_KEY_CTRL_M       (0x0D)
#define VT_KEY_CTRL_N       (0x0E)
#define VT_KEY_CTRL_O       (0x0F)
#define VT_KEY_CTRL_P       (0x10)
#define VT_KEY_CTRL_Q       (0x11)
#define VT_KEY_CTRL_R       (0x12)
#define VT_KEY_CTRL_S       (0x13)
#define VT_KEY_CTRL_T       (0x14)
#define VT_KEY_CTRL_U       (0x15)
#define VT_KEY_CTRL_V       (0x16)
#define VT_KEY_CTRL_W       (0x17)
#define VT_KEY_CTRL_X       (0x18)
#define VT_KEY_CTRL_Y       (0x19)
#define VT_KEY_CTRL_Z       (0x1A)


/* self-defined key,
 * only supported by "Tera Term" with updated "keyboard.cnf" file.
 */
#define VT_KEY_DEL          (0x7F)
#define VT_KEY_INSERT       (0x80)
#define VT_KEY_HOME         (0x81)
#define VT_KEY_END          (0x82)
#define VT_KEY_PAGEUP       (0x83)
#define VT_KEY_PAGEDOWN     (0x84)
#define VT_KEY_UP           (0x85)
#define VT_KEY_DOWN         (0x86)
#define VT_KEY_LEFT         (0x87)
#define VT_KEY_RIGHT        (0x88)
#define VT_KEY_F1           (0x89)
#define VT_KEY_F2           (0x8A)
#define VT_KEY_F3           (0x8B)
#define VT_KEY_F4           (0x8C)
#define VT_KEY_F5           (0x8D)
#define VT_KEY_F6           (0x8E)
#define VT_KEY_F7           (0x8F)
#define VT_KEY_F8           (0x90)
#define VT_KEY_F9           (0x91)
#define VT_KEY_F10          (0x92)
#define VT_KEY_F11          (0x93)
#define VT_KEY_F12          (0x94)

#endif


/* VT100 Text Attributes */
/* The table of attributes that are used with the SGR command */
typedef enum
{
    VT_TEXT_NORMAL             = 0,      /* NORNAL (Attributes off)          */
    VT_TEXT_HIGH_INTENSITY     = 1,      /* Bold or high intensity           */
    VT_TEXY_LOW_INTENSITY      = 2,      /* Low intensity                    */
    VT_TEXT_UNDERLINE          = 4,      /* Underline                        */
    VT_TEXT_BLINK              = 5,      /* Blinking                         */
    VT_TEXT_INVERSE            = 7,      /* INVERSE (Negative/reverse image) */
    VT_TEXT_CONCEALED          = 8,      /* Concealed                        */
    VT_TEXT_ASCII              = 10,     /* Graphics off                     */
    VT_TEXT_GRAPHICS           = 12,     /* Graphics on                      */

    VT_TEXT_END_HIGH_INTENSITY = 21,     /* End high intensity               */
    VT_TEXT_END_LOW_INTENSITY  = 22,     /* End low intensity                */
    VT_TEXT_END_UNDERLINE      = 24,     /* End underline                    */
    VT_TEXT_END_BLINK          = 25,     /* End blinking                     */
    VT_TEXT_END_INVERSE        = 27,     /* End inverse                      */
    VT_TEXT_END_CONCEALED      = 28,     /* End concealed                    */

    VT_TEXT_BLACK_FOREGROUND   = 30,     /* Black foreground                 */
    VT_TEXT_RED_FOREGROUND     = 31,     /* Red foreground                   */
    VT_TEXT_GREEN_FOREGROUND   = 32,     /* Green foreground                 */
    VT_TEXT_YELLOW_FOREGROUND  = 33,     /* Yellow foreground                */
    VT_TEXT_BLUE_FOREGROUND    = 34,     /* Blue foreground                  */
    VT_TEXT_MAGENTA_FOREGROUND = 35,     /* Magenta foreground               */
    VT_TEXT_CYAN_FOREGROUND    = 36,     /* Cyan foreground                  */
    VT_TEXT_WHITE_FOREGROUND   = 37,     /* White foreground                 */
    VT_TEXT_DEFAULT_FOREGROUND = 39,     /* Default foreground               */

    VT_TEXT_BLACK_BACKGROUND   = 40,     /* Black background                 */
    VT_TEXT_RED_BACKGROUND     = 41,     /* Red background                   */
    VT_TEXT_GREEN_BACKGROUND   = 42,     /* Green background                 */
    VT_TEXT_YELLOW_BACKGROUND  = 43,     /* Yellow background                */
    VT_TEXT_BLUE_BACKGROUND    = 44,     /* Blue background                  */
    VT_TEXT_MAGENTA_BACKGROUND = 45,     /* Magenta background               */
    VT_TEXT_CYAN_BACKGROUND    = 46,     /* Cyan background                  */
    VT_TEXT_WHITE_BACKGROUND   = 47,     /* White background                 */
    VT_TEXT_DEFAULT_BACKGROUND = 49      /* Default background               */
} VT_TextAttrib;


#define VT_Printf                   printf
#define VT_ReadKey(n)               getchar(n)

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
void VT_FlushRxFIFO(void);

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
void VT_MoveLeft(IN UINT8 columns);

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
void VT_MoveRight(IN UINT8 columns);

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
void VT_MoveUp(IN UINT8 columns);

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
void VT_MoveDown(IN UINT8 columns);

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
void VT_EraseLine(IN UINT8 erase_mode);

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
void VT_EraseScreen(IN UINT8 erase_mode);

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
void VT_SetTextAttrib(IN VT_TextAttrib attrib);

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
void VT_CharacterSet(IN UINT8 set);

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
void VT_SaveCursorPosition(void);

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
void VT_RestoreCursorPosition(void);

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
void VT_SetCursorPosition(IN UINT8 row, IN UINT8 column);

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
BOOL VT_GetCursorPosition(OUT UINT8 *row, OUT UINT8 *column);

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
void VT_ClearScreen(IN UINT8 clear_mode);

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
void VT_Init(void);

#endif


#endif /* __VT_H */

