// 将此文件放入MyDll的DLL项目中

#include <Windows.h>

// C++ 导出函数给C语言使用，需要前面加上 extern "C"
extern "C" _declspec(dllexport) void Test()
{
	MessageBox(NULL, TEXT("Hello world"), TEXT("message"), MB_OK | MB_ICONINFORMATION);
}