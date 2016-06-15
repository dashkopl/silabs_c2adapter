:: ############################################################################
::
:: COPYRIGHT:
::   Copyright (c) 2016    PANDA(yaxi1984@gmail.com)    All rights reserved.
::
::   This program is free software; you can redistribute it and/or
::   modify it under the terms of the GNU General Public License as
::   published by the Free Software Foundation; either version 2 of
::   the License, or (at your option) any later version.
::
::   This program is distributed in the hope that it will be useful,
::   but WITHOUT ANY WARRANTY; without even the implied warranty of
::   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
::   GNU General Public License for more details.
::
::   You should have received a copy of the GNU General Public License
::   along with this program; if not, write to the Free Software
::   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
::   MA 02111-1307 USA
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
set /p="Generating mempage header file ... " <nul
python %PROJECT_DIR%\tools\mempage_converter.py                             ^
    --input=%PROJECT_DIR%\doc\design\%PROJECT_NAME%_Memmap.xls              ^
    --output=%PROJECT_DIR%\porting\~cfg_mempage_def.h
echo Done.
set /p="Generating memmap header file  ... " <nul
python %PROJECT_DIR%\tools\memmap_converter.py                              ^
    --input=%PROJECT_DIR%\doc\design\%PROJECT_NAME%_Memmap.xls              ^
    --output=%PROJECT_DIR%\porting\~cfg_memmap_def.h
echo Done.
set /p="Generating memcfg binary file  ... " <nul
python %PROJECT_DIR%\tools\memcfg_converter.py                              ^
    --input=%PROJECT_DIR%\doc\design\%PROJECT_NAME%_Memmap.xls              ^
    --output=%IMG_DIR%\%PROJECT_NAME%.cfg
echo Done.
set /p="Generating hardware info file  ... " <nul
python %PROJECT_DIR%\tools\hw_converter.py                                  ^
    --input=%PROJECT_DIR%\porting\cfg_hw_def.h                              ^
    --output=%PROJECT_DIR%\porting\~cfg_hw_def.h
echo Done.

echo **************************************************************************
