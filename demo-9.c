#include <Windows.h>
#include <tchar.h>

ATOM MyRegisterClass(HINSTANCE, LPCTSTR);
BOOL InitInstance(HINSTANCE, LPCTSTR);
DWORD SyStemError();

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCmdLine, int iCmdShow)
{
	MSG msg;
	LPCTSTR szClassName = _T("MyApp");
	
	if (!MyRegisterClass(hInstance, szClassName)) {
		return SyStemError();
	}

	if (!InitInstance(hInstance, szClassName)) {
		return SyStemError();
	}

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

DWORD SyStemError()
{
	LPVOID lpMsgBuf;
	DWORD dwMessageId = GetLastError();
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwMessageId,
		MAKELANGID(LANG_SYSTEM_DEFAULT, LANG_USER_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	MessageBox(NULL, (LPTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONERROR);
	LocalFree(lpMsgBuf);

	return dwMessageId;
}

ATOM MyRegisterClass(HINSTANCE hInstance, LPCTSTR szClassName)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = szClassName;
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	return RegisterClassEx(&wc);
}
BOOL InitInstance(HINSTANCE hInstance, LPCTSTR szClassName)
{
	HWND hWnd = CreateWindow(szClassName, _T("My Application"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, hInstance, 0);

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return FALSE;
}
