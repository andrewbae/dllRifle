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

BOOL __stdcall Process::GetProcessList(WCHAR *wcpExeFile)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32W pe32;
    memset(&pe32, 0x00, sizeof(pe32));
    pe32.dwSize = sizeof(pe32);
    WCHAR wcExeFile[MAX_PATH];
    
    std::wcout << "----- BEGIN PROCESS LIST -----" << std::endl;
    std::wcout.clear();
    std::cin.clear();


    if (wcpExeFile == 0x00) {
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        Process32FirstW(hProcessSnap, &pe32);
        while (Process32NextW(hProcessSnap, &pe32) != 0x00)
        {
            std::wcout << pe32.szExeFile;
            std::wcout << "(" << pe32.th32ProcessID << ")" << std::endl;
        }
    }
    else {
        memcpy(wcExeFile, wcpExeFile, (MAX_PATH * 2) - 10);
        memset((wcExeFile + wcslen(wcExeFile)), 0x00, ((MAX_PATH * 2) - wcslen(wcExeFile) - 10));

        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        Process32FirstW(hProcessSnap, &pe32);
        while (Process32NextW(hProcessSnap, &pe32) != 0x00)
        {
            if (CompareStringW(LOCALE_ALL, NORM_IGNORECASE, pe32.szExeFile, wcslen(pe32.szExeFile), wcExeFile, wcslen(wcExeFile)) == CSTR_EQUAL) {
                std::wcout << pe32.szExeFile;
                std::wcout << "(" << pe32.th32ProcessID << ")" << std::endl;
            }
        }
    }
    std::wcout << "----- END PROCESS LIST -----" << std::endl << std::endl;
    return EXIT_SUCCESS;
}

BOOL __stdcall Process::GetProcessModules(HANDLE hProcess, char *cpDllPath)
{
    HMODULE hProcessModules[1024];
    DWORD dwNeeded;
    char cModuleName[MAX_PATH], cDllPath[MAX_PATH];
 
    memcpy(cDllPath, cpDllPath, MAX_PATH);
    memset((cDllPath + strlen(cDllPath)), 0x00, MAX_PATH - strlen(cDllPath));

    std::wcout << "----- BEGIN PROCESS MODULES LIST -----" << std::endl;
    if (*cModuleName == 0x00) {
        EnumProcessModules(hProcess, hProcessModules, sizeof(hProcessModules), &dwNeeded);
        for (unsigned int v0 = 0; v0 < (dwNeeded / sizeof(HMODULE)); v0++) {
            if (GetModuleFileNameExA(hProcess, hProcessModules[v0], cModuleName, sizeof(cModuleName) / sizeof(char))) {
               std::cout << "0x" << hProcessModules[v0] << " -> " << cModuleName << std::endl;
            }
            memset(cModuleName, 0x00, sizeof(cModuleName));
        }
    }
    else {
        EnumProcessModules(hProcess, hProcessModules, sizeof(hProcessModules), &dwNeeded);
        for (unsigned int v0 = 0; v0 < (dwNeeded / sizeof(HMODULE)); v0++) {
            if (GetModuleFileNameExA(hProcess, hProcessModules[v0], cModuleName, sizeof(cModuleName) / sizeof(TCHAR))
            && CompareStringA(LOCALE_ALL, NORM_IGNORECASE, cModuleName, strlen(cModuleName), cDllPath, strlen(cDllPath)) == CSTR_EQUAL) {
                std::wcout << "0x" << hProcessModules[v0] << " -> " << cModuleName << std::endl;
                std::wcout << "----- END PROCESS MODULES LIST -----" << std::endl;
                return EXIT_SUCCESS;
            }
            memset(cModuleName, 0x00, sizeof(cModuleName));
        }
        std::wcout << "----- END PROCESS MODULES LIST -----" << std::endl;
        return EXIT_FAILURE;
    }
    std::wcout << "----- END PROCESS MODULES LIST -----" << std::endl;
    return EXIT_SUCCESS;
}


