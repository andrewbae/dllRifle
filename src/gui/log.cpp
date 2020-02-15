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

#include "./log.h"

void __stdcall Log::DrLogOutputA(HWND logBoxHandle, LPCSTR string)
{
    int idx = GetWindowTextLengthA(logBoxHandle);

    SendMessageA(logBoxHandle, EM_SETSEL, (WPARAM)idx, (LPARAM)idx);
    SendMessageA(logBoxHandle, EM_REPLACESEL, 0, (LPARAM)string);
}

void __stdcall Log::DrLogOutputW(HWND logBoxHandle, LPCWSTR string)
{
    int idx = GetWindowTextLengthW(logBoxHandle);

    SendMessageW(logBoxHandle, EM_SETSEL, (WPARAM)idx, (LPARAM)idx);
    SendMessageW(logBoxHandle, EM_REPLACESEL, 0, (LPARAM)string);
}

void __stdcall Log::DrLogOutputAddressA(HWND logBoxHandle, LPCVOID address)
{
    int idx;
    char string[32];
    
    memset(string, 0x00, sizeof(char)*32);

    idx = GetWindowTextLengthA(logBoxHandle);   
    SendMessageA(logBoxHandle, EM_SETSEL, (WPARAM)idx, (LPARAM)idx);
    SendMessageA(logBoxHandle, EM_REPLACESEL, 0, (LPARAM)"0x");

    _ultoa_s((unsigned long)address, string, 16, 16);

    idx = GetWindowTextLengthA(logBoxHandle);
    SendMessageA(logBoxHandle, EM_SETSEL, (WPARAM)idx, (LPARAM)idx);
    SendMessageA(logBoxHandle, EM_REPLACESEL, 0, (LPARAM)string);
}
