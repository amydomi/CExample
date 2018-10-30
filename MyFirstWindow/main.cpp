#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
ATOM MyRegisterClass(HINSTANCE hInstance, LPCTSTR className);
BOOL InitInstance(HINSTANCE hInstance, LPCTSTR className, int nCmdShow);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPTSTR szCmdLine, int nCmdShow)
{
	
	MSG msg;
	LPCTSTR className = TEXT("MyFirstWindow");
	
	// 注册窗口类
	if (!MyRegisterClass(hInstance, className)) {
		MessageBox(NULL, TEXT("Window Registeration Failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return GetLastError();
	}

	// 创建并显示窗口
	if (!InitInstance(hInstance, className, nCmdShow)) {
		MessageBox(NULL, TEXT("Window Createation Failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return GetLastError();
	}

	// 消息循环
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

//
//  函数: MyRegisterClass(HINSTANCE, LPCTSTR)
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPCTSTR className)
{
	WNDCLASSEX wc;
	
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = className;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	
	return RegisterClassEx(&wc);
}

//
//  函数: InitInstance(HINSTANCE, LPCTSTR, int)
//
//  目标: 创建并显示窗口。
//
BOOL InitInstance(HINSTANCE hInstance, LPCTSTR className, int nCmdShow)
{
	HWND hWnd = CreateWindowEx(NULL, className, TEXT("My First Window"),
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600, NULL, NULL, hInstance, NULL);

	if (hWnd == 0) {
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

//
//  函数: WindowProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口消息。
//
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return FALSE;
}