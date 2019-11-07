// Hook.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "Hook.h"

//
// ��ȡDLL������
// bRefΪTRUE�ᵼ��DLL���ü�����1��FALSE����ı����ü�����ͨ����FALSE  
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
// ���ӹ��̺���
//
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (HC_ACTION == code && wParam == WM_KEYUP) {
		
		PKBDLLHOOKSTRUCT pKbhs = (PKBDLLHOOKSTRUCT)lParam;

		// �ػ�F12����
		if (pKbhs->vkCode == VK_F12) {
			MessageBox(NULL, L"F12", L"F12", 0);
		}
	}
	return CallNextHookEx(g_hHook, code, wParam, lParam);
}

//
// ��װ����
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
// ж�ع���
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