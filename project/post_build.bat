:: ############################################################################
:: 
::  COPYRIGHT:
::    Copyright (c) 2016      CreaLights Inc.      All rights reserved.
::
::    This is unpublished proprietary source code of CreaLights Inc.
::    The copyright notice above does not evidence any actual or intended
::    publication of such source code.
::
::  DESCRIPTION:
::    Post-build related.
::  HISTORY:
::    2016.01.22          Panda.Xiong              Create
:: 
:: ############################################################################

:: close echo
@echo off

set PROJECT_DIR=%1
set PROJECT_NAME=%2

:: set command search path
path %COMPILER_BASE%\bin

set OBJ_DIR=%PROJECT_DIR%\build\obj
set IMG_DIR=%PROJECT_DIR%\build\image

:: ============================================================================
::  Porting Part
:: ============================================================================
set CFG_BASE=0x3800

:: ============================================================================
::  Common Part
:: ============================================================================

echo **************************************************************************

:: create image directory
if not exist %IMG_DIR% (
    mkdir %IMG_DIR%
)

:: create *.map file
set /p="Creating %PROJECT_NAME%.map   ... " <nul
cp %OBJ_DIR%\%PROJECT_NAME%.map %IMG_DIR%\%PROJECT_NAME%.map
echo Done.

:: create *.lss file
set /p="Creating %PROJECT_NAME%.lss   ... " <nul
cp %OBJ_DIR%\%PROJECT_NAME%.cod %IMG_DIR%\%PROJECT_NAME%.lss
echo Done.

:: create *.hex file
set /p="Creating %PROJECT_NAME%.hex   ... " <nul
cp %OBJ_DIR%\%PROJECT_NAME%.hex %IMG_DIR%\%PROJECT_NAME%.hex
echo Done.

:: create *.bin file
set /p="Creating %PROJECT_NAME%.bin   ... " <nul
hex2bin %IMG_DIR%\%PROJECT_NAME%.hex %IMG_DIR%\%PROJECT_NAME%.bin
echo Done.

:: create *.sig file
set /p="Creating %PROJECT_NAME%.sig   ... " <nul
sign --mcu=c8051fxxx                                                        ^
     --input=%IMG_DIR%\%PROJECT_NAME%.bin                                   ^
     --output=%IMG_DIR%\%PROJECT_NAME%.sig
echo Done.

:: create *.fw file
set /p="Creating %PROJECT_NAME%.fw    ... " <nul
cp %IMG_DIR%\%PROJECT_NAME%.sig %IMG_DIR%\%PROJECT_NAME%.fw
echo Done.

:: create *.flash file
set /p="Creating %PROJECT_NAME%.flash ... " <nul
binmerge --input1=%IMG_DIR%\%PROJECT_NAME%.fw                               ^
         --input2=%IMG_DIR%\%PROJECT_NAME%.cfg                              ^
         --output=%IMG_DIR%\%PROJECT_NAME%.flash                            ^
         --pad1-to=%CFG_BASE%                                               ^
         --pad-val=0xFF
echo Done.

echo **************************************************************************
