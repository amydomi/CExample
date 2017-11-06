#include <Windows.h>
#include <tchar.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	// 声明函数指针
	typedef void (* TestFn)();
	typedef int (* AddFn)(int, int);

	// 函数指针变量
	TestFn Test;
	AddFn add;

	int a = 10, b = 20;
	TCHAR bufResult[50];

	// 加载DLL文件，可以使用 LoadLibrary, LoadLibraryEx, LoadPackagedLibrary, or GetModuleHandle 加载DLL文件
	HMODULE handle = LoadLibrary(_T("MyDll.dll"));

	if (handle == NULL) {
		MessageBox(NULL, _T("DLL载入失败！"), _T("消息"), MB_OK | MB_ICONERROR);
		return -1;
	}

	// 获取函数地址
	Test = (TestFn)GetProcAddress(handle, "Test");
	add = (AddFn)GetProcAddress(handle, "add");

	// 函数地址获取失败，返回NULL
	if (NULL == Test || NULL == add) {
		MessageBox(NULL, _T("函数执行失败！"), _T("消息"), MB_OK | MB_ICONERROR);
		return -1;
	}

	// 执行函数
	Test();
	wsprintf(bufResult, _T("%d + %d = %d"), a, b, add(a, b));
	MessageBox(NULL, bufResult, _T("计算结果"), MB_OK);

	return 0;
}