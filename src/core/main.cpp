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
	Injection injection;
	OPENFILENAMEA ofn;
	HANDLE Token, hProcess;
	DWORD dwPid = (DWORD)0;
	char cDllPath[OFN_FILE_PATH_MAXIMUM];

	std::wcout << "[*] choice the process" << std::endl << std::endl;
	std::cin >> dwPid;

	memset(&ofn, 0x00, sizeof(ofn));
	memset(cDllPath, 0x00, sizeof(cDllPath));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.nMaxFile = sizeof(cDllPath);
	ofn.lpstrFile = cDllPath;
	ofn.lpstrFilter = "DLL\0*.dll\0";
	ofn.nFilterIndex = 1;
	ofn.nMaxFileTitle = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetOpenFileNameA(&ofn);
	std::wcout << "[*] chosen DLL: " << cDllPath << std::endl << std::endl;

	// preparing done

	injection.GetPrivilege();

	injection.dwPid = dwPid;
	injection.lpcvDllPath = cDllPath;
	if (injection.native() == EXIT_SUCCESS) {
		std::cout << "[*] DLL injected successfuly!" << std::endl;
	}

	getchar();
	CloseHandle(injection.hProcess);
}
