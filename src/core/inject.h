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

#ifndef _INJECT_H
#define _INJECT_H

#ifndef _MSC_VER
#pragma comment(lib, "uuid.lib")
#endif

#include "windows.h"
#include <iostream>

#define OFN_FILE_PATH_MAXIMUM (256)

namespace DllRifle {
    namespace Core {
        class Injection {
        public:
            HANDLE hProcess;
            DWORD dwPid;
            LPCVOID lpcvDllPath;

            BOOL __stdcall GetPrivilege();
            BOOL __stdcall GetProcessList();
            BOOL __stdcall native();
        };
    }
}
#endif
