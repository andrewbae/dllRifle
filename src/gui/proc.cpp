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

#include "proc.h"

Application* ap = new Application;
Injection* injection = new Injection;
Process* process = new Process;
Log* log = new Log;
Dll* dll = new Dll;

char dllPath[MAX_PATH];

HWND \
processSelectorDialogHandle,
processComboBoxHandle,
dllComboBoxHandle,
dllDialogHandle,
processDialogHandle,
logBoxHandle,
injectButtonHandle,
processListBoxHandle;
RECT rect;

LRESULT __stdcall WindowProcedure(
    _In_ HWND mainHandle,
    _In_ UINT message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
)
{
    OPENFILENAMEA* ofn;
    PAINTSTRUCT ps;
    HDC hdc = nullptr;

    TCHAR v1[16];
    UINT v0;

    memset(&ofn, 0x00, sizeof(ofn));

    switch (message) {
    case WM_CREATE: {
        SetRect(&rect, 30, 130, 450, 30);
        processComboBoxHandle = CreateWindowW(
            TEXT("edit"), nullptr, WS_CHILD | WS_BORDER | WS_VISIBLE | ES_LEFT | WS_TABSTOP,
            rect.left, rect.top, rect.right, rect.bottom,
            mainHandle, nullptr, ap->instanceHandle, nullptr);

        SetRect(&rect, 490, 130, 100, 30);
        processDialogHandle = CreateWindowA(
            "button", "Select", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
            rect.left, rect.top, rect.right, rect.bottom,
            mainHandle, (HMENU)IDC_OPEN_PROCESS_DIALOG, ap->instanceHandle, nullptr);

        SetRect(&rect, 30, 200, 450, 30);
        dllComboBoxHandle = CreateWindowW(
            TEXT("edit"), nullptr, WS_CHILD | WS_BORDER | WS_VISIBLE | ES_LEFT | WS_TABSTOP,
            rect.left, rect.top, rect.right, rect.bottom,
            mainHandle, nullptr, ap->instanceHandle, nullptr);

        SetRect(&rect, 490, 200, 100, 30);
        dllDialogHandle = CreateWindowA(
            "button", "Select", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
            rect.left, rect.top, rect.right, rect.bottom,
            mainHandle, (HMENU)IDC_OPEN_DLL_DIALOG, ap->instanceHandle, nullptr);

        SetRect(&rect, 30, 250, 560, 150);

        logBoxHandle = CreateWindowA(
            "edit", nullptr,
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_READONLY |
            ES_AUTOHSCROLL | ES_AUTOVSCROLL,
            rect.left, rect.top, rect.right, rect.bottom,
            mainHandle,
            0,
            ap->instanceHandle, nullptr);
        SetRect(&rect, 30, 420, 275, 35);
        injectButtonHandle = CreateWindowA(
            "button", "Advenced options", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
            rect.left, rect.top, rect.right, rect.bottom,
            mainHandle, (HMENU)IDC_ADVENCED_CLICK_EVENT, ap->instanceHandle, nullptr);

        SetRect(&rect, 315, 420, 275, 35);
        injectButtonHandle = CreateWindowA(
            "button", "Inject", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
            rect.left, rect.top, rect.right, rect.bottom,
            mainHandle, (HMENU)IDC_INJECT_CLICK_EVENT, ap->instanceHandle, nullptr);

        break;
    }
    case WM_PAINT: {
        HFONT hFont;
        hdc = BeginPaint(mainHandle, &ps);

        SetRect(&rect, 30, 30, 50, 40);
        hFont = CreateFont(50, 0, 0, 0, FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, 0, 0, \
            DEFAULT_QUALITY, VARIABLE_PITCH, TEXT("Segoe UI"));
        if (hFont != nullptr) {
            SelectObject(hdc, hFont);
            DrawText(hdc, TEXT("dllRifle"), -1, &rect, DT_NOCLIP);
        }

        SetRect(&rect, 30, 90, 50, 40);
        hFont = CreateFont(33, 0, 0, 0, FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, 0, 0, \
            DEFAULT_QUALITY, VARIABLE_PITCH, TEXT("Segoe UI"));
        if (hFont != nullptr) {
            SelectObject(hdc, hFont);
            DrawText(hdc, TEXT("Victim process"), -1, &rect, DT_NOCLIP);
        }
        SetRect(&rect, 30, 165, 50, 40);
        hFont = CreateFont(33, 0, 0, 0, FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, 0, 0, \
            DEFAULT_QUALITY, VARIABLE_PITCH, TEXT("Segoe UI"));
        if (hFont != nullptr) {
            SelectObject(hdc, hFont);
            DrawText(hdc, TEXT("Payload Dll"), -1, &rect, DT_NOCLIP);
        }

        DeleteObject(hFont);
        EndPaint(mainHandle, &ps);
        break;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case IDC_OPEN_DLL_DIALOG: {
            ofn = dll->DrOpenDllSelector();
            if (ofn == nullptr) {
                return EXIT_FAILURE;
            }
            memcpy(dllPath, ofn->lpstrFile, MAX_PATH);
            log->DrLogOutputW(logBoxHandle, TEXT("[DLL] "));
            wchar_t wDllPath[MAX_PATH];
            int nLen = MultiByteToWideChar(CP_ACP, 0, dllPath, sizeof(dllPath), nullptr, 0);
            MultiByteToWideChar(CP_ACP, 0, dllPath, sizeof(dllPath), wDllPath, nLen);

            log->DrLogOutputW(logBoxHandle, wDllPath);
            log->DrLogOutputW(logBoxHandle, TEXT("\r\n"));
            SetWindowTextA(dllComboBoxHandle, dllPath);
            return EXIT_SUCCESS;
            break;
        }
        case IDC_OPEN_PROCESS_DIALOG: {
            processSelectorDialogHandle = CreateWindowExA(
                0,
                ap->classNameSelectProcess,
                "Select process",
                WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
                CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
                mainHandle, 0, ap->instanceHandle, nullptr);
            ap->DrSetWindowPositionToCenter(processSelectorDialogHandle);
            ShowWindow(processSelectorDialogHandle, SW_SHOW);
            break;
        }
        case IDC_ADVENCED_CLICK_EVENT: {
            MessageBoxA(mainHandle, "This function has not been implemented yet.", "Shit!", MB_OK | MB_ICONSTOP);
            break;
        }
        case IDC_INJECT_CLICK_EVENT: {
            injection->DrGetPrivilege();

            injection->pid = ap->victimProcessId;
            injection->dllPath = dllPath;
            injection->logBoxHandle = logBoxHandle;
            if (!(injection->DrNativeInjection()))
            {
                if (!(process->DrGetProcessModules(injection->processHandle, logBoxHandle, dllPath))) {
                    log->DrLogOutputW(logBoxHandle, TEXT("[!]  DLL injected successfuly!"));
                }
                else {
                    log->DrLogOutputW(logBoxHandle, TEXT("[!] DLL not injected! it's looks like Does not written on memory area"));
                }
            }
            CloseHandle(injection->processHandle);
            break;
        }
        }
        break;
    }
    case WM_CLOSE: {
        if (MessageBoxA(mainHandle, "Are you sure close the program?", "No way!", MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK) {
            DestroyWindow(mainHandle);
        }
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
    }
    default: {
        return DefWindowProcA(mainHandle, message, wParam, lParam);
    }
           return 0;
    }
}



LRESULT __stdcall DrProcessSelectorDialogProcedure(
    HWND processSelectorDialogHandle,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    WCHAR str[64];
    memset(str, 0x00, sizeof(str));
    switch (message) {
    case WM_CREATE: {
        SetRect(&rect, 30, 30, 400, 360);
        processListBoxHandle = CreateWindowW(
            TEXT("listbox"), nullptr,
            WS_VISIBLE | WS_CHILD | LBS_STANDARD | WS_VSCROLL | ES_AUTOVSCROLL,
            rect.left, rect.top, rect.right, rect.bottom,
            processSelectorDialogHandle, (HMENU)IDC_LISTBOX_CLICK_EVENT, ap->instanceHandle, nullptr);

        SetRect(&rect, 30, 395, 400, 30);
        CreateWindowW(
            TEXT("button"), TEXT("Open"),
            WS_VISIBLE | WS_CHILD,
            rect.left, rect.top, rect.right, rect.bottom,
            processSelectorDialogHandle, (HMENU)IDC_OPEN_PROCESS_CLICK_EVENT, ap->instanceHandle, nullptr);

        process->DrGetProcessList(processListBoxHandle);
        break;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case IDC_LISTBOX_CLICK_EVENT: {
            switch (HIWORD(wParam)) {
            case LBN_DBLCLK:
                int index = SendMessage((HWND)lParam, LB_GETCARETINDEX, 0, 0);
                SendMessage((HWND)lParam, LB_GETTEXT, (LPARAM)index, (WPARAM)str);

                log->DrLogOutputW(logBoxHandle, TEXT("[PROCESS] "));
                log->DrLogOutputW(logBoxHandle, str);
                log->DrLogOutputW(logBoxHandle, TEXT("\r\n"));
                SetWindowTextW(processComboBoxHandle, str);
                ap->victimProcessId = SendMessage((HWND)lParam, LB_GETITEMDATA, (WPARAM)index, 0);
                DestroyWindow(processSelectorDialogHandle);
                break; 
            } break;
        }
        case IDC_OPEN_PROCESS_CLICK_EVENT: {
            int index = SendMessage((HWND)processListBoxHandle, LB_GETCARETINDEX, 0, 0);
            SendMessage((HWND)processListBoxHandle, LB_GETTEXT, (LPARAM)index, (WPARAM)str);

            log->DrLogOutputW(logBoxHandle, TEXT("[PROCESS] "));
            log->DrLogOutputW(logBoxHandle, str);
            log->DrLogOutputW(logBoxHandle, TEXT("\r\n"));
            SetWindowTextW(processComboBoxHandle, str);
            ap->victimProcessId = SendMessage((HWND)processListBoxHandle, LB_GETITEMDATA, (WPARAM)index, 0);
            DestroyWindow(processSelectorDialogHandle);
            break;
        } break;
        } break;
    }
    default: {
        if (message == WM_CLOSE || message == WM_DESTROY) { DestroyWindow(processSelectorDialogHandle); }
        return DefWindowProcA(processSelectorDialogHandle, message, wParam, lParam);
    }
    return 0;
    }
}

