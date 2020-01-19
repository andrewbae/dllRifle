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

#include "inject.h"

BOOL __stdcall Injection::GetPrivilege()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	memset(&tp, 0x00, sizeof(tp));

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		if (AdjustTokenPrivileges(hToken, 0, &tp, sizeof(tp), nullptr, nullptr) == 0) {
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

BOOL __stdcall Injection::native()
{
	HANDLE hThreadId;
	LPVOID lpLoadLibraryAddr;
	LPVOID lpDllPathVirtualAddr;

	std::cout << "[*] OpenProcess... ";
	hProcess = OpenProcess(
		PROCESS_ALL_ACCESS |
		PROCESS_CREATE_THREAD |
		PROCESS_CREATE_PROCESS |
		PROCESS_VM_WRITE |
		PROCESS_VM_READ |
		PROCESS_QUERY_INFORMATION |
		PROCESS_VM_OPERATION
		, (BOOL)0, dwPid);

	if (hProcess == (void*)0x00) {
		std::cout << std::endl << "[!] Failed to open the chosen process" << std::endl;
		std::cout << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}std::cout << "Success!" << std::endl << "[+] hProcess -> " << hProcess << std::endl << std::endl;

	std::cout << "[*] GetProcAddress... ";
	lpLoadLibraryAddr = GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryA");
	if (lpLoadLibraryAddr == (void*)0x00) {
		std::cout << "[!] Failed to get LoadLibraryA function address on kernel32.dll" << std::endl;
		std::cout << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}std::cout << "Success!" << std::endl << "[+] LoadLibraryAddr -> " << lpLoadLibraryAddr << std::endl << std::endl;

	std::cout << "[*] VirtualAllocEx... ";
	lpDllPathVirtualAddr = VirtualAllocEx(hProcess, nullptr, OFN_FILE_PATH_MAXIMUM, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (lpDllPathVirtualAddr == (void*)0x00) {
		std::cout << std::endl << "[!] Failed to allocate virtual memory area inside chosen process" << std::endl;
		std::cout << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}std::cout << "Success!" << std::endl << "[+] lpDllPathVirtualAddr -> " << lpDllPathVirtualAddr << std::endl << std::endl;

	std::cout << "[*] WriteProcessMemory... ";
	if (WriteProcessMemory(hProcess, lpDllPathVirtualAddr, lpcvDllPath, OFN_FILE_PATH_MAXIMUM, nullptr) == 0) {
		std::cout << "[!] Failed write lpDllPath to lpDllPathVirtualAddr" << std::endl;
		std::cout << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}std::cout << "Success!" << std::endl << std::endl;

	hThreadId = CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE)lpLoadLibraryAddr, lpDllPathVirtualAddr, 0, 0);

	if (hThreadId == (void*)0x00) {
		std::cout << "[!] Failed create thread on chosen process" << std::endl << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}std::cout << "[*] Thread ID: " << hThreadId << std::endl;
	VirtualFree(lpLoadLibraryAddr, 0, MEM_RELEASE);
	VirtualFree(lpDllPathVirtualAddr, 0, MEM_RELEASE);
	CloseHandle(hThreadId);

	return EXIT_SUCCESS;
}
