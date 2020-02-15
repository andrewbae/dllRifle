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
#include "../gui/log.h"

BOOL __stdcall Injection::DrGetPrivilege()
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

BOOL __stdcall Injection::DrNativeInjection()
{
	Log *log = new Log;
	HANDLE threadHandle;
	LPVOID loadLibraryAddress;
	LPVOID dllPathVirtualAddress;
	
	log->DrLogOutputW(logBoxHandle, TEXT("===== BEGIN INJECTION SEQUENCE =====\r\n"));	
	log->DrLogOutputW(logBoxHandle, TEXT("[INFO] injetion method: native(default)\r\n"));

	log->DrLogOutputW(logBoxHandle, TEXT("[INFO] Open process handle..."));
	processHandle = OpenProcess(
		PROCESS_ALL_ACCESS |
		PROCESS_CREATE_THREAD |
		PROCESS_CREATE_PROCESS |
		PROCESS_VM_WRITE |
		PROCESS_VM_READ |
		PROCESS_QUERY_INFORMATION |
		PROCESS_VM_OPERATION
		, (BOOL)0, pid);

	if (processHandle == (void*)0x00) {
		log->DrLogOutputW(logBoxHandle, TEXT("Failed!\r\n[ERROR] Failed to open the chosen process\r\n"));
		return EXIT_FAILURE;
	}log->DrLogOutputW(logBoxHandle, TEXT("Success!\r\n[INFO] processHandle -> "));
	log->DrLogOutputAddressA(logBoxHandle, processHandle);
	Sleep(1000);
	log->DrLogOutputW(logBoxHandle, TEXT("\r\n\r\n[INFO] Get LoadLibraryA address from kernel32.dll..."));
	loadLibraryAddress = GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryA");
	if (loadLibraryAddress == (void*)0x00) {
		log->DrLogOutputW(logBoxHandle, TEXT("Failed!\r\n Failed to get LoadLibraryA function address on kernel32.dll\r\n"));
		return EXIT_FAILURE;
	}log->DrLogOutputW(logBoxHandle, TEXT("Success!\r\n[INFO] loadLibraryAddress -> ")); 
	log->DrLogOutputAddressA(logBoxHandle, loadLibraryAddress);

	Sleep(1000);
	log->DrLogOutputW(logBoxHandle, TEXT("\r\n\r\n[INFO] VirtualAllocEx..."));
	dllPathVirtualAddress = VirtualAllocEx(processHandle, nullptr, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (dllPathVirtualAddress == (void*)0x00) {
		log->DrLogOutputW(logBoxHandle, TEXT("Failed!\r\n Failed to allocate virtual memory area inside chosen process\r\n"));
		return EXIT_FAILURE;
	}log->DrLogOutputW(logBoxHandle, TEXT("Success!\r\n[INFO] dllPathVirtualAddress -> "));
	log->DrLogOutputAddressA(logBoxHandle, dllPathVirtualAddress);

	Sleep(1000);
	log->DrLogOutputW(logBoxHandle, TEXT("\r\n\r\n[INFO] WriteProcessMemory..."));
	if (WriteProcessMemory(processHandle, dllPathVirtualAddress, dllPath, MAX_PATH, nullptr) == 0) {
		log->DrLogOutputW(logBoxHandle, TEXT("Failed!\r\n Failed write dllPath to dllPathVirtualAddress\n"));
		return EXIT_FAILURE;
	}log->DrLogOutputW(logBoxHandle, TEXT("Success!\r\n"));

	Sleep(1000);

	log->DrLogOutputW(logBoxHandle, TEXT("\r\n\r\n[INFO] CreateRemoteThread..."));
	threadHandle = CreateRemoteThread(processHandle, nullptr, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddress, dllPathVirtualAddress, 0, 0);
	if (threadHandle == (void*)0x00) {
		log->DrLogOutputW(logBoxHandle, TEXT("Failed!\r\n Failed create thread on chosen process\n"));
		return EXIT_FAILURE;
	}log->DrLogOutputW(logBoxHandle, TEXT("Success!\r\n [INFO] threadHandle -> "));
	log->DrLogOutputAddressA(logBoxHandle, threadHandle);
	log->DrLogOutputA(logBoxHandle, "\r\n");
	VirtualFree(loadLibraryAddress, 0, MEM_RELEASE);
	VirtualFree(dllPathVirtualAddress, 0, MEM_RELEASE);
	CloseHandle(threadHandle);

	return EXIT_SUCCESS;
}
