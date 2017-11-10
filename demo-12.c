#include <Windows.h>
#include <tchar.h>
#include <WinError.h>

LPVOID GetErorMessage(DWORD);

// 可在Visual Studio调试的监视(Watch)窗口加入 $err,hr查看错误信息
// Windows错误的宏定义在 WinError.h 中
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
	LPVOID lpMsgBuf;	// 错误字符串指针，需要转为PTSTR来显示
	DWORD dw; // 错误编号
	
	// 编写一条错误的调用，使用GetLastError() 获取错误编号
	GetDlgItemInt(NULL, 0, FALSE, FALSE);

	dw = GetLastError(); // 如果无错误，GetLastError = 0 = ERROR_SUCCESS
	lpMsgBuf = GetErorMessage(dw);
	MessageBox(NULL, (PTSTR)lpMsgBuf, _T("错误"), MB_OK | MB_ICONERROR);
	return dw;
	return 0;
}

// 传递错误编号，返回错误信息字符串的首地址
LPVOID GetErorMessage(DWORD dw)
{
	LPVOID hLocal;
	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
		(LPTSTR)&hLocal,
		0,
		NULL
	);
	return hLocal;
}