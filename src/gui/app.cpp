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


#include "app.h"

HWND __stdcall Application::DrInitializeAppSystem(
    _In_ HINSTANCE imageBaseAddress, 
    _In_ LPCSTR applicationTitle, 
    _In_ int cmdShow
)
{
    memset(&windowClass, 0x00, sizeof(WNDCLASSA));

    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.cbWndExtra = sizeof(PVOID);
    windowClass.hCursor = LoadCursor(0, IDC_ARROW);
    windowClass.hInstance = imageBaseAddress;
    windowClass.lpfnWndProc = (WNDPROC)WindowProcedure;
    windowClass.lpszClassName = classNameMain;

    if (!(RegisterClassA(&windowClass))) { return (HWND)0x00; }

    windowClass.lpfnWndProc = (WNDPROC)DrProcessSelectorDialogProcedure;
    windowClass.lpszClassName = classNameSelectProcess;

    if (!(RegisterClassA(&windowClass))) { return (HWND)0x00; }
    
    SetRect(&rect, 40, 115, 650, 540);
    mainHandle = CreateWindowExA(
        0, classNameMain,
        applicationTitle,
        WS_OVERLAPPED|WS_SYSMENU,
        rect.left, rect.top, rect.right, rect.bottom,
        0, 0, imageBaseAddress, 0);

    DrSetWindowPositionToCenter(mainHandle);
    
    if (!(mainHandle)) { return (HWND)0x00; }
    ShowWindow(mainHandle, SW_SHOW);
    return mainHandle;
}

void __stdcall Application::DrSetWindowPositionToCenter(
    HWND windowHandle
)
{
    RECT rect;
    GetWindowRect(windowHandle, &rect);
    SetWindowPos(
        windowHandle, 0,
        (GetSystemMetrics(SM_CXSCREEN) - rect.right) /2,
        (GetSystemMetrics(SM_CYSCREEN) - rect.bottom) / 2,
        0, 0,
        SWP_NOZORDER | SWP_NOSIZE 
        );
}

