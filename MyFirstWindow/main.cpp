#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
ATOM MyRegisterClass(HINSTANCE hInstance, LPCTSTR className);
BOOL InitInstance(HINSTANCE hInstance, LPCTSTR className, int nCmdShow);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPTSTR szCmdLine, int nCmdShow)
{
	
	MSG msg;
	LPCTSTR className = TEXT("MyFirstWindow");
	
	// ע�ᴰ����
	if (!MyRegisterClass(hInstance, className)) {
		MessageBox(NULL, TEXT("Window Registeration Failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return GetLastError();
	}

	// ��������ʾ����
	if (!InitInstance(hInstance, className, nCmdShow)) {
		MessageBox(NULL, TEXT("Window Createation Failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return GetLastError();
	}

	// ��Ϣѭ��
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

//
//  ����: MyRegisterClass(HINSTANCE, LPCTSTR)
//
//  Ŀ��: ע�ᴰ���ࡣ
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
//  ����: InitInstance(HINSTANCE, LPCTSTR, int)
//
//  Ŀ��: ��������ʾ���ڡ�
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
//  ����: WindowProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ������������Ϣ��
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