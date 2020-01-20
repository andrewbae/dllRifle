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

#include "process.h"

BOOL __stdcall Process::GetProcessList()
{
    HANDLE hProcessSnap;
    PROCESSENTRY32W pe32;
    memset(&pe32, 0x00, sizeof(pe32));
    pe32.dwSize = sizeof(pe32);

    std::wcout << "----- BEGIN PROCESS LIST -----" << std::endl;
    if (*wcExeFile == 0) {
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        Process32FirstW(hProcessSnap, &pe32);
        std::wcout << pe32.th32ProcessID;
        while (Process32NextW(hProcessSnap, &pe32) != 0x00)
        {
            std::wcout << pe32.szExeFile;
            std::wcout << "(" << pe32.th32ProcessID << ")" << std::endl;
        }
    }
    else {
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        Process32FirstW(hProcessSnap, &pe32);
        std::wcout << pe32.th32ProcessID;
        while (Process32NextW(hProcessSnap, &pe32) != 0x00)
        {
            if (CompareStringW(LOCALE_ALL, NORM_IGNORECASE, pe32.szExeFile, MAX_PATH, wcExeFile, MAX_PATH) == CSTR_EQUAL) {
                std::wcout << pe32.szExeFile;
                std::wcout << "(" << pe32.th32ProcessID << ")" << std::endl;
            }
        }
    }
    std::wcout << "----- END PROCESS LIST -----" << std::endl << std::endl;
    *wcExeFile = 0;
    return EXIT_SUCCESS;
}
