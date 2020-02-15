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
#include "../gui/log.h"
#include <string>
#include <sstream>
#include <WtsApi32.h>

void __stdcall Process::DrGetProcessList(HWND processListBoxHandle)
{
    HANDLE processHandleSnap;
    PROCESSENTRY32W pe32;

    memset(&pe32, 0x00, sizeof(pe32));

    pe32.dwSize = sizeof(PROCESSENTRY32W);

    processHandleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    Process32FirstW(processHandleSnap, &pe32);
    
    char pid[8];
    int processNameLength;
    for (UINT v0 = 0; Process32NextW(processHandleSnap, &pe32) != 0x00; v0++) {
        memset(&processNameLength, 0x00, sizeof(int));
        // type conversion HEX -> DEC
        _ultoa_s(pe32.th32ProcessID, pid, 8, 10);
        memcpy((void*)(pe32.szExeFile + lstrlenW(pe32.szExeFile)), "(", 1);

        processNameLength = lstrlenW(pe32.szExeFile);
        for (int v1 = 0; v1 < strlen(pid); v1++) {
            memcpy((void*)(pe32.szExeFile + processNameLength + v1), (pid + v1), 1);
        }

        memcpy((void*)(pe32.szExeFile + lstrlenW(pe32.szExeFile)), ")", 1);

        // Send Strings to list box
        int index = SendMessageW(processListBoxHandle, LB_ADDSTRING, 0, (LPARAM)pe32.szExeFile);
        SendMessageA(processListBoxHandle, LB_SETITEMDATA, index, pe32.th32ProcessID);
    }
    SetFocus(processListBoxHandle);
    //}
    /*
    else {
        memcpy(wcExeFile, wcpExeFile, (MAX_PATH * 2) - 10);
        memset((wcExeFile + wcslen(wcExeFile)), 0x00, ((MAX_PATH * 2) - wcslen(wcExeFile) - 10));

        processHandleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        Process32FirstW(processHandleSnap, &pe32rotation);
        while (Process32NextW(processHandleSnap, &pe32rotation) != 0x00)
        {
            if (CompareStringW(LOCALE_ALL, NORM_IGNORECASE, pe32rotation.szExeFile, wcslen(pe32rotation.szExeFile), wcExeFile, wcslen(wcExeFile)) == CSTR_EQUAL) {
                std::wcout << pe32rotation.szExeFile;
                std::wcout << "(" << pe32rotation.th32ProcessID << ")" << std::endl;
            }
        }
    }
    */
    CloseHandle(processHandleSnap);
}

BOOL __stdcall Process::DrGetProcessModules(HANDLE processHandle, HWND logBoxHandle, char* dllPath)
{
    Log log;
    HMODULE processHandleModules[1024];
    DWORD needed = 0;
    char cModuleName[MAX_PATH], dp[MAX_PATH];

    memcpy(dp, dllPath, MAX_PATH);
    memset((dp+ strlen(dp)), 0x00, MAX_PATH - strlen(dp));
    memset(&needed, 0x00, sizeof(DWORD));
    memset(&processHandleModules, 0x00, sizeof(HMODULE)*1024);
        
        EnumProcessModules(processHandle, processHandleModules, sizeof(processHandleModules), &needed);
        for (unsigned int v0 = 0; v0 < (needed / sizeof(HMODULE)); v0++) {
            if (GetModuleFileNameExA(processHandle, processHandleModules[v0], cModuleName, sizeof(cModuleName) / sizeof(TCHAR))
                && CompareStringA(LOCALE_ALL, NORM_IGNORECASE, cModuleName, strlen(cModuleName),dp, strlen(dp)) == CSTR_EQUAL) {
                /*
                
                std::wcout << "0x" << processHandleModules[v0] << " -> " << cModuleName << std::endl;
                log.OutputAddressA(logBoxHandle, *(processHandleModules + v0));
                log.OutputA(logBoxHandle, dllPath);
                log.OutputA(logBoxHandle, "\r\n");
                */
                return EXIT_SUCCESS;
            }
            memset(cModuleName, 0x00, sizeof(cModuleName));
        }
        //return EXIT_FAILURE;
    //}
    return EXIT_SUCCESS;
}


