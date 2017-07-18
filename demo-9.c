#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	WNDCLASSEX wcx;
	HWND hwnd;
	MSG msg;
	
	// 1.注册窗口
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WindowProc;	// 窗口处理过程
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = L"MyApp";
	wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wcx)) {
		MessageBox(NULL, L"Register window class failure.", L"Message", MB_OK | MB_ICONERROR);
		return GetLastError();
	}
	
	// 2.创建窗口
	hwnd = CreateWindow(
		L"MyApp",
		L"DEMO Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd) {
		MessageBox(NULL, L"Create window failure.", L"Message", MB_OK | MB_ICONERROR);
		return GetLastError();
	}
	
	// 3.显示窗口
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// 4.消息循环
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

// 窗口消息处理过程
LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch(uMsg) {
		case WM_CLOSE:
			if(IDOK == MessageBox(hwnd, L"是否确认退出程序？", L"消息", MB_OKCANCEL | MB_ICONQUESTION)) {
				PostQuitMessage(0);
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}