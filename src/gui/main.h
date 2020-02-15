/*
 * This file is part of the dllRifle distribution (https://github.com/dev4ndr3w).
 * Copyright (c) 2020 Andrew Peterson.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _MAIN_H
#define _MAIN_H

#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <windowsx.h>
#include <commctrl.h>

#include "../core/process.h"
#include "../core/dll.h"
#include "../core/inject.h"
#include "../define.h"
#include "./log.h"
#include "./proc.h"
#include "./app.h"

#define CONTAINER (30)

HWND mainHandle;

INT __stdcall WinMain(
    _In_ HINSTANCE imageBaseAddress,
    _In_opt_ HINSTANCE prevImageBaseAddress,
    _In_ LPSTR cmdLine,
    _In_ INT cmdShow
    );

#endif