#include <Windows.h>

void SendText();
void getTimeString(LPWSTR str, INT length);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	SendText();
	return 0;
}

// ��ȡ��ǰ����ʱ���ַ���
void getTimeString(LPWSTR str, INT length)
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	ZeroMemory(str, length);
	wsprintf(str, L"��ǰ���ڣ�%d-%02d-%02d  %02d:%02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
}

// ��ָ���Ĵ��ڷ����ı���Ϣ
void SendText()
{
	// ��ȡQQ���촰�ھ�� ����Ϊ�����Լ���QQ
	HWND hWnd = FindWindow(NULL, L"���Լ���QQ");

	if (NULL == hWnd) {
		MessageBox(NULL, L"���QQ����Ի���", L"��Ϣ", MB_OK | MB_ICONERROR);
		return;
	}

	// ϲ����������ڷ�����Ϣ
	while (true)
	{
		Sleep(3000);

		WCHAR str[100];
		WCHAR time[30];
		getTimeString(time, 30);

		wsprintf(str, L"��ã�QQ������ %s", time);


		for (INT i = 0; i < lstrlen(str); i++) {
			SendMessage(hWnd, WM_CHAR, (WPARAM)str[i], NULL);
		}

		SendMessage(hWnd, WM_KEYDOWN, VK_RETURN, NULL);
		SendMessage(hWnd, WM_CHAR, 0x13, NULL);
		SendMessage(hWnd, WM_KEYUP, VK_RETURN, NULL);
	}

}