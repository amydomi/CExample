#include <Windows.h>
#include <tchar.h>

#include "system.h"

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
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_INFORMATION);
	wc.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
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
		WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX ^ WS_MAXIMIZEBOX | WS_VSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT, 820, 480,
		NULL, NULL, hInstance, 0);

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int cxChar, cxCaps, cyChar, cyClient;
	HDC hdc;
	int i, y, iVertPos, iPaintBegin, iPaintEnd;
	PAINTSTRUCT ps;
	TCHAR szBuffer[10];
	TEXTMETRIC tm;
	SCROLLINFO si;

	switch (uMsg) {
	case WM_CREATE:
		hdc = GetDC(hWnd);
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		ReleaseDC(hWnd, hdc);
		break;
	case WM_SIZE:
		cyClient = HIWORD(lParam);
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_PAGE | SIF_RANGE;
		si.nMin = 0;
		si.nMax = NUMLINES - 1;
		si.nPage = cyClient / cyChar;
		SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(30, 255, 0));
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		GetScrollInfo(hWnd, SB_VERT, &si);
		iVertPos = si.nPos;

		iPaintBegin = max(0, iVertPos + ps.rcPaint.top / cyChar);
		iPaintEnd = min(NUMLINES - 1, iVertPos + ps.rcPaint.bottom / cyChar);
		
		for (i = iPaintBegin; i <= iPaintEnd; i++) {

			y = cyChar * (i - iVertPos);

			
			TextOut(hdc, 0, y, sysmetrics[i].szLabel,
				lstrlen(sysmetrics[i].szLabel));

			
			TextOut(hdc, 30 * cxCaps, y, sysmetrics[i].szDesc,
				lstrlen(sysmetrics[i].szDesc));
			SetTextAlign(hdc, TA_RIGHT | TA_TOP);

			TextOut(hdc, 30 * cxCaps + 60 * cxChar, y, szBuffer,
				wsprintf(szBuffer, TEXT("%5d"),
				GetSystemMetrics(sysmetrics[i].Index)));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_VSCROLL:
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		GetScrollInfo(hWnd, SB_VERT, &si);
		iVertPos = si.nPos;
		switch (LOWORD(wParam)) {
		case SB_TOP:
			si.nPos = si.nMin;
			break;
		case SB_BOTTOM:
			si.nPos = si.nMax;
			break;
		case SB_LINEUP:
			si.nPos -= 1;
			break;
		case SB_LINEDOWN:
			si.nPos += 1;
			break;
		case SB_PAGEUP:
			si.nPos -= si.nPage;
			break;
		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;
		case SB_PAGEDOWN:
			si.nPos += si.nPage;
			break;
		}
		si.fMask = SIF_POS;
		SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
		GetScrollInfo(hWnd, SB_VERT, &si);
		if (si.nPage != iVertPos) {
			ScrollWindow(hWnd, 0, cyChar * (iVertPos - si.nPos), NULL, NULL);
			UpdateWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return FALSE;
}