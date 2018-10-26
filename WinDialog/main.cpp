#include <Windows.h>
#include "resource.h"

// manifest 清单指明 ComCtl32.dll 控件的版本为6.0 （XP风格控件）
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

INT_PTR CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

// WinMain入口函数
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC)DialogProc);
	return 0;
}

// Dialog消息处理过程
INT_PTR CALLBACK DialogProc(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	BOOL fResult = TRUE;
	switch (uMsg)
	{
	case WM_COMMAND:
		if(ID_CLOSE == wParam) {
			if(IDOK == MessageBox(hwndDlg, L"是否关闭窗口？", L"消息", MB_OKCANCEL | MB_ICONQUESTION)) {
				EndDialog(hwndDlg, (INT_PTR)wParam);
			}
		}
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg, (INT_PTR)wParam);
		break;
	default:
		fResult = FALSE;
	}
	return (INT_PTR)fResult;
}
