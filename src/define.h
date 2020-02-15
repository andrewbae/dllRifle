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

#ifndef _DEFINITION_H
#define _DEFINITION_H

#define PROC_SEARCH                 (WM_USER + 0x0000)
#define PROC_SEARCH_NAME            (WM_USER + 0x0001)
#define PROC_ID                     (WM_USER + 0x0002)

#define IDC_BASE                     (WM_USER + 0x00F0)
#define IDC_INJECT_CLICK_EVENT       (IDC_BASE + 0x0001)
#define IDC_ADVENCED_CLICK_EVENT     (IDC_BASE + 0x0002)
#define IDC_OPEN_DLL_DIALOG          (IDC_BASE + 0x0003)
#define IDC_OPEN_PROCESS_DIALOG      (IDC_BASE + 0x0004)
#define IDC_OPEN_PROCESS_CLICK_EVENT (IDC_BASE + 0x0005)
#define IDC_LISTBOX_CLICK_EVENT      (IDC_BASE + 0x0006)

#define IDC_INJECT_METHOD_NATIVE    (IDC_BASE + 0x0005)
#define IDC_INJECT_METHOD_THREAD    (IDC_BASE + 0x0005)
#define IDC_INJECT_METHOD_KERNEL    (IDC_BASE + 0x0005)

#endif
