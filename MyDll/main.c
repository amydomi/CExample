#include <Windows.h>

// 引入MyDll项目生成的lib文件
#pragma comment(lib, "..\\Debug\\MyDll.lib")

// 声明函数
void Test();

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Test();	// 调用MyDll.dll中的函数
	return 0;
}