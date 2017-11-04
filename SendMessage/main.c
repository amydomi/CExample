#include "main.h"

//
//  ����: WinMain()
//
//  Ŀ��: ����ں�����
//
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	InitCommonControls(); // ʹ��XP����UI
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, (DLGPROC)DialogProc);
	return 0;
}

//
//  ����: DialogProc()
//
//  Ŀ��: ��Ϣ��������
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
		// ��ʼ��
		stopButton = GetDlgItem(hwndDlg, IDC_STOP);
		EnableWindow(stopButton, FALSE);
		ZeroMemory(szContent, 1024);
		lstrcat(szContent, _T("������QQ������Ϣ��"));
		SetDlgItemText(hwndDlg, IDC_EDIT_VIEW, szContent);
		break;
	case WM_COMMAND:
		// ��ȡ��ť���
		startButton = GetDlgItem(hwndDlg, IDC_START);
		stopButton = GetDlgItem(hwndDlg, IDC_STOP);
		switch (LOWORD(wParam))
		{
		case IDC_START:
			if (!flag) {
				ZeroMemory(szContent, 1024);
				GetDlgItemText(hwndDlg, IDC_EDIT_VIEW, szContent, 1024);
				flag = TRUE;
				EnableWindow(startButton, FALSE);	// ���ð�ť
				EnableWindow(stopButton, TRUE);	// ���ð�ť
				hThread = CreateThread(NULL, 0, Start, NULL, 0, NULL); // ʹ���µ��̷߳�����Ϣ����ֹ���濨��
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
//  ����: Start()
//
//  Ŀ��: ���̴߳�������
//
DWORD WINAPI Start(LPVOID lpParamter)
{
	//ö�����д���
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

	// �ж���QQ��Ϣ���ڣ�������ʾ��ǰ̨�Ŷ��䷢����Ϣ
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

