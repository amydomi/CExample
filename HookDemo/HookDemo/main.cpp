#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>

#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "resource.h"

#include "../Hook/Hook.h"
#ifdef _DEBUG
#pragma comment(lib, "../Debug/Hook.lib")
#else
#pragma comment(lib, "../Release/Hook.lib")
#endif

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	Button_Enable(GetDlgItem(hwnd, IDC_BUTTON_END), FALSE);
	return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BUTTON_START) {
		InstallHook();
		Button_Enable(GetDlgItem(hwnd, IDC_BUTTON_END), TRUE);
	}
	if (id == IDC_BUTTON_END) {
		UnInstallHook();
		Button_Enable(GetDlgItem(hwnd, IDC_BUTTON_START), TRUE);
	}
	Button_Enable(hwndCtl, FALSE);
}

void OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = TRUE;
	switch (uMsg)
	{
		HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
		HANDLE_MSG(hwnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
	default:
		bRet = FALSE;
		break;
	}
	return bRet;
}

int WINAPI _tWinMain(
	HINSTANCE hInst,
	HINSTANCE prevInst,
	PTCHAR szCmdLine,
	int nCmdShow)
{

	InitCommonControls();

	DialogBox(hInst, MAKEINTATOM(IDD_DIALOG1), NULL, DlgProc);

}