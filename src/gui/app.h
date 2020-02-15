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


#ifndef _APP_H
#define _APP_H

#include "proc.h"
#include <windows.h>

namespace Ui { class Application {}; };

class Application {
private:
    WNDCLASSA windowClass;
    RECT rect;
public:
    const LPCSTR classNameMain = "DLLRIFLE_MAIN";
    const LPCSTR classNameSelectProcess = "DLLRIFLE_PROCESS_SELECTOR";
    const LPCSTR classNameBackgroundWhite = "BACKGROUND_WHITE";

    DWORD victimProcessId;
    HWND mainHandle;
    HINSTANCE instanceHandle;
    HWND __stdcall DrInitializeAppSystem(
        _In_ HINSTANCE imageBaseAddress,
        _In_ LPCSTR applicationTitle,
        _In_ int cmdShow
    );
    void __stdcall DrSetWindowPositionToCenter(
        _In_ HWND windowHandle
    );
};

#endif