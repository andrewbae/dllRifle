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

#ifndef _LOG_H
#define _LOG_H

#include <windows.h>

namespace Ui { class Log {}; }

class Log {
public:
    void __stdcall DrLogOutputA(
        _In_ HWND logBoxHandle,
        _In_ LPCSTR string
    );
    void __stdcall DrLogOutputW(
        _In_ HWND logBoxHandle,
        _In_ LPCWSTR string
    );
    void __stdcall DrLogOutputAddressA(
        _In_ HWND logBoxHandle,
        _In_ LPCVOID address
    );
};

#endif