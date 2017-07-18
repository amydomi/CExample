#include <Windows.h>
#include "resource.h"

// ������������ڴ���ؼ����� manifest
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

INT_PTR CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

// WinMain��ں���
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

// Dialog��Ϣ�������
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
			if(IDOK == MessageBox(hwndDlg, L"�Ƿ�رմ��ڣ�", L"��Ϣ", MB_OKCANCEL | MB_ICONQUESTION)) {
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
