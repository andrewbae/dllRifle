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

#ifndef _PROC_H
#define _PROC_H

#include <windows.h>
#include "../core/dll.h"
#include "../core/inject.h"
#include "../define.h"
#include "./log.h"
#include "./app.h"
#include "../core/process.h"

namespace Ui { class Procedure {}; } 

LRESULT __stdcall WindowProcedure(
    _In_ HWND hWnd,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
);
LRESULT __stdcall DrProcessSelectorDialogProcedure(
    _In_ HWND processSelectorDialogHandle,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
);

#endif
