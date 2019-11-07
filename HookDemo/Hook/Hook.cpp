// Hook.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Hook.h"

//
// 获取DLL自身句柄
// bRef为TRUE会导致DLL引用计数加1，FALSE不会改变引用计数，通常用FALSE  
//
HMODULE GetCurrentModule(BOOL bRef/* = FALSE*/)
{
	HMODULE hModule = NULL;
	if (GetModuleHandleEx(bRef ? GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS : (GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
		| GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT), (PCTSTR)GetCurrentModule, &hModule))
	{
		return hModule;
	}
	return NULL;
}
//
// 钩子过程函数
//
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (HC_ACTION == code && wParam == WM_KEYUP) {
		
		PKBDLLHOOKSTRUCT pKbhs = (PKBDLLHOOKSTRUCT)lParam;

		// 截获F12按键
		if (pKbhs->vkCode == VK_F12) {
			MessageBox(NULL, L"F12", L"F12", 0);
		}
	}
	return CallNextHookEx(g_hHook, code, wParam, lParam);
}

//
// 安装钩子
//
HOOK_API BOOL InstallHook()
{
	// g_hModule = GetModuleHandle(L"Hook.dll");
	g_hModule = GetCurrentModule(FALSE);
	if (g_hHook) {
		return FALSE;
	}
	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, g_hModule, 0);
	return TRUE;
}

//
// 卸载钩子
//
HOOK_API BOOL UnInstallHook()
{
	if (!g_hHook) {
		return FALSE;
	}
	UnhookWindowsHookEx(g_hHook);
	g_hHook = NULL;
	return TRUE;
}