#pragma once
#include "stdafx.h"

INT_PTR CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK EnumWindowsProc(HWND, LPARAM);
DWORD WINAPI Start(LPVOID);

BOOL flag = FALSE;
TCHAR szContent[1024];
HANDLE hThread;