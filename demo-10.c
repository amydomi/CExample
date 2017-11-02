#include <Windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// 打开记事本窗口
	HINSTANCE hd = ShellExecute(NULL, TEXT("open"), TEXT("C:\\Windows\\notepad.exe"), NULL, TEXT("D:\\"), SW_SHOW);

	// 
	HWND hWnd = NULL;
	do {
		Sleep(300);
		// 获取父窗口
		hWnd = FindWindow(NULL, TEXT("无标题 - 记事本"));
	} while (NULL == hWnd);

	// 获取子窗口
	HWND childWnd = FindWindowEx(hWnd, NULL, TEXT("Edit"), NULL);

	// 发送字符消息
	SendMessage(childWnd, WM_CHAR, 'H', 0);
	SendMessage(childWnd, WM_CHAR, 'E', 0);
	SendMessage(childWnd, WM_CHAR, 'L', 0);
	SendMessage(childWnd, WM_CHAR, 'L', 0);
	SendMessage(childWnd, WM_CHAR, 'O', 0);

	// 发送鼠标右键消息
	do {
		Sleep(3000); // 循环3秒一次执行一次右键
		
		// 获取当前鼠标的位置
		POINT point;
		GetCursorPos(&point);

		// 获取窗口至屏幕的距离
		RECT rect;
		GetWindowRect(childWnd, &rect);

		SendMessage(childWnd, WM_RBUTTONDOWN, 0, MAKELPARAM(point.x - rect.left, point.y - rect.top));
		SendMessage(childWnd, WM_RBUTTONUP, 0, MAKELPARAM(point.x - rect.left, point.y - rect.top));
	} while (TRUE);
	
	return 0;
}