#include "main.h"

//
//  函数: WinMain()
//
//  目的: 主入口函数。
//
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	InitCommonControls(); // 使用XP风格的UI
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, (DLGPROC)DialogProc);
	return 0;
}

//
//  函数: DialogProc()
//
//  目的: 消息处理函数。
//
INT_PTR CALLBACK DialogProc(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	BOOL fResult = TRUE;
	HWND startButton, stopButton;
	switch (uMsg)
	{
	case WM_INITDIALOG:
		// 初始化
		stopButton = GetDlgItem(hwndDlg, IDC_STOP);
		EnableWindow(stopButton, FALSE);
		ZeroMemory(szContent, 1024);
		lstrcat(szContent, _T("测试向QQ发送消息。"));
		SetDlgItemText(hwndDlg, IDC_EDIT_VIEW, szContent);
		break;
	case WM_COMMAND:
		// 获取按钮句柄
		startButton = GetDlgItem(hwndDlg, IDC_START);
		stopButton = GetDlgItem(hwndDlg, IDC_STOP);
		switch (LOWORD(wParam))
		{
		case IDC_START:
			if (!flag) {
				ZeroMemory(szContent, 1024);
				GetDlgItemText(hwndDlg, IDC_EDIT_VIEW, szContent, 1024);
				flag = TRUE;
				EnableWindow(startButton, FALSE);	// 禁用按钮
				EnableWindow(stopButton, TRUE);	// 启用按钮
				hThread = CreateThread(NULL, 0, Start, NULL, 0, NULL); // 使用新的线程发送消息，防止界面卡死
			}
			break;
		case IDC_STOP:
			if (flag) {
				flag = FALSE;
				EnableWindow(startButton, TRUE);
				EnableWindow(stopButton, FALSE);
				CloseHandle(hThread);
			}
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg, (INT_PTR)fResult);
		break;
	default:
		fResult = FALSE;
		break;
	}
	return (INT_PTR)fResult;
}

//
//  函数: Start()
//
//  目的: 多线程处理函数。
//
DWORD WINAPI Start(LPVOID lpParamter)
{
	//枚举所有窗口
	EnumWindows((WNDENUMPROC)EnumWindowsProc, 0);
	return 0;
}

BOOL CALLBACK EnumWindowsProc(
	HWND   hwnd,
	LPARAM lParam
)
{
	TCHAR szClass[256];
	ZeroMemory(szClass, 0);
	GetClassName(hwnd, szClass, 255);

	// 判断是QQ消息窗口，并且显示在前台才对其发送消息
	if (wcsstr(szClass, _T("TXGuiFoundation")) && IsWindowVisible(hwnd) && IsWindow(hwnd)) {
		while (flag) {
			for (int i = 0; i < lstrlen(szContent); ++i)
			{
				SendMessage(hwnd, WM_CHAR, (WPARAM)szContent[i], 0);
			}
			SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
			SendMessage(hwnd, WM_CHAR, 0x13, 0);
			SendMessage(hwnd, WM_KEYUP, VK_RETURN, 0);
			Sleep(3000);
		}
	}

	return TRUE;
}

