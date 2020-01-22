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

#include "dll.h"

OPENFILENAMEA __stdcall dllRifle::Dll::OpenDllSelectDialog()
{
    OPENFILENAMEA ofn;
    char cDllPath[MAX_PATH];

    memset(&ofn, 0x00, sizeof(ofn));
    memset(&cDllPath, 0x00, sizeof(cDllPath));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFile = cDllPath;
    ofn.lpstrFilter = "DLL\0*.dll\0";
    ofn.nFilterIndex = 1;
    ofn.nMaxFileTitle = 0;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn) == 1) {
        return ofn;
    }
    else {
        MessageBox(nullptr, L"Failed to GetOpenFileNameA", L"shit!", MB_OK);
    }
}
