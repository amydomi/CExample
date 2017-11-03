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

// 获取当前日期时间字符串
void getTimeString(LPWSTR str, INT length)
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	ZeroMemory(str, length);
	wsprintf(str, L"当前日期：%d-%02d-%02d  %02d:%02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
}

// 向指定的窗口发送文本消息
void SendText()
{
	// 获取QQ聊天窗口句柄 标题为：我自己的QQ
	HWND hWnd = FindWindow(NULL, L"我自己的QQ");

	if (NULL == hWnd) {
		MessageBox(NULL, L"请打开QQ聊天对话框。", L"消息", MB_OK | MB_ICONERROR);
		return;
	}

	// 喜欢向这个窗口发送消息
	while (true)
	{
		Sleep(3000);

		WCHAR str[100];
		WCHAR time[30];
		getTimeString(time, 30);

		wsprintf(str, L"你好，QQ先生！ %s", time);


		for (INT i = 0; i < lstrlen(str); i++) {
			SendMessage(hWnd, WM_CHAR, (WPARAM)str[i], NULL);
		}

		SendMessage(hWnd, WM_KEYDOWN, VK_RETURN, NULL);
		SendMessage(hWnd, WM_CHAR, 0x13, NULL);
		SendMessage(hWnd, WM_KEYUP, VK_RETURN, NULL);
	}

}