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

#include "main.h"

int main()
{
    dllRifle::Dll dll;
    Injection injection;
    Process process;

    OPENFILENAMEA ofn;
    HANDLE Token;
    DWORD dwPid = (DWORD)0;
    WCHAR wcExeFile[MAX_PATH], wcConsoleTitle[16] = TEXT("dllRifle");
    
    char cDllPath[MAX_PATH];
    unsigned short uInput;
 
    memset(&ofn, 0x00, sizeof(ofn));
    memset(&wcExeFile, 0x00, MAX_PATH*2);

    SetConsoleTitle(wcConsoleTitle);

    while (dwPid == 0) {
        std::wcout.clear();
        std::cin.clear();

        std::wcout << "0: Process list" << std::endl \
            << "1: Search process with name (EX: shit.exe)" << std::endl \
            << "2: Enter PID" << std::endl, uInput = 0;

        std::wcout << "> ", std::cin >> uInput;

        switch (uInput) {
        case PROC_SEARCH: {
            process.GetProcessList(0);
            break;
        }
        case PROC_SEARCH_NAME: {
            std::wcout << "processName> ", std::wcin >> wcExeFile;
            process.GetProcessList(wcExeFile);
            break;
        }
        case PROC_ID: {
            std::wcout << "pid> ", std::cin >> dwPid;
            break;
        }
        default: {
            std::wcout << "Unknown command" << std::endl;
            break;
        }
        }
    }
    
    dll.OpenDllSelectDialog();
    memcpy(&cDllPath, ofn.lpstrFile, MAX_PATH);
    std::wcout << "[*] chosen DLL: " << cDllPath << std::endl << std::endl;

    // preparing done
    injection.GetPrivilege();

    injection.dwPid = dwPid;
    injection.lpcvDllPath = cDllPath;
    if (injection.native() == EXIT_SUCCESS) { 
        if (process.GetProcessModules(injection.hProcess, cDllPath) == EXIT_SUCCESS) {
            std::wcout << "[*] DLL injected successfuly!" << std::endl;
        }
        else {
            std::wcout << "[!] DLL not injected! it's looks like Does not written on memory area" << std::endl;
        }
    }
    else {
        std::wcout << "[!] DLL not injected!" << std::endl;
    }
    system("pause");
    CloseHandle(injection.hProcess);
}
