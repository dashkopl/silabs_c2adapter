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
::    Pre-build related.
::  HISTORY:
::    2016.01.22          Panda.Xiong              Create
:: 
:: ############################################################################

:: close echo
@echo off

set PROJECT_DIR=%1
set PROJECT_NAME=%2

:: set command search path
path %COMPILER_BASE%\bin;%COMPILER_BASE%\python

set OBJ_DIR=%PROJECT_DIR%\build\obj
set IMG_DIR=%PROJECT_DIR%\build\image

echo **************************************************************************

:: remove image directory
if exist %IMG_DIR% (
    rm -rf %IMG_DIR%
)

:: create image directory
mkdir %IMG_DIR%

:: generating necessary files
set /p="Generating hardware info file  ... " <nul
python %PROJECT_DIR%\tools\hw_converter.py                                  ^
    --input=%PROJECT_DIR%\porting\cfg_hw_def.h                              ^
    --output=%PROJECT_DIR%\porting\~cfg_hw_def.h
echo Done.

echo **************************************************************************
