/*
* This file is part of dllRifle.
*
* dllRifle is free software : you can redistribute itand /or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* dllRifle is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with dllRifle.If not, see < https://www.gnu.org/licenses/>.
*/

#ifndef _PROCESS_H
#define _PROCESS_H

#include "windows.h"
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h>

namespace Core { class Process {}; }

class Process {
public:
    void __stdcall DrGetProcessList(
        _In_ HWND processListBoxHandle
        );

    BOOL __stdcall DrGetProcessModules(
        _In_ HANDLE processHandle,
        _In_ HWND logBoxHandle,
        _In_ char* dllPath
        );
};

#endif