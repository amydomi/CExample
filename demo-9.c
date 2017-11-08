#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	static TCHAR appName[] = _T("MyApp");

	WNDCLASSEX wndclass;
	HWND hWnd;
	MSG msg;

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = (WNDPROC)WindowProc;
	wndclass.lpszClassName = appName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wndclass)) {
		MessageBox(NULL, _T("Register window class fail."), _T("Message"), MB_OK | MB_ICONERROR);
		return 0;
	}

	hWnd = CreateWindow(appName, _T("My Application"), WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDc;
	PAINTSTRUCT ps;
	RECT rect;
	HFONT hFont;

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lstrcpy(lf.lfFaceName, _T("Tahoma"));
	lf.lfHeight = 80;

	switch (uMsg)
	{
	case WM_PAINT:
		hDc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		hFont = CreateFontIndirect(&lf);
		SelectObject(hDc, hFont);
		SetBkMode(hDc, TRANSPARENT);
		DrawText(hDc, _T("Hello World"), -1, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}
