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

#include "main.h"

INT __stdcall WinMain(
    _In_ HINSTANCE imageBaseAddress,
    _In_opt_ HINSTANCE prevImageBaseAddress,
    _In_ LPSTR cmdLine,
    _In_ INT cmdShow
)
{
    Application *ap = new Application;
    ap->instanceHandle = imageBaseAddress;

    mainHandle = ap->DrInitializeAppSystem(ap->instanceHandle, "DllRifle by dev4ndr3w", cmdShow);
    if (!(mainHandle)) { MessageBoxA(nullptr, "Cannot create the window", "Unexpected error!", MB_OK | MB_ICONSTOP); return EXIT_FAILURE; }
    MSG message;

    while (GetMessage(&message, 0, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return 0;
}

