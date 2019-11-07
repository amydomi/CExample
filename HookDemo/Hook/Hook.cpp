// Hook.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Hook.h"

//
// 
//
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (HC_ACTION == code && wParam == WM_KEYUP) {
		PKBDLLHOOKSTRUCT pKbhs = (PKBDLLHOOKSTRUCT)lParam;
		if (pKbhs->vkCode == VK_F12) {
			MessageBox(NULL, L"F12", L"F12", 0);
		}
	}
	return CallNextHookEx(g_hHook, code, wParam, lParam);
}
HOOK_API BOOL InstallHook()
{
	g_hModule = GetModuleHandle(L"Hook.dll");
	if (g_hHook) {
		return FALSE;
	}
	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, g_hModule, 0);
	return TRUE;
}

HOOK_API BOOL UnInstallHook()
{
	if (!g_hHook) {
		return FALSE;
	}
	UnhookWindowsHookEx(g_hHook);
	g_hHook = NULL;
	return TRUE;
}