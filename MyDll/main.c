#include <Windows.h>

// ����MyDll��Ŀ���ɵ�lib�ļ�
#pragma comment(lib, "..\\Debug\\MyDll.lib")

// ��������
void Test();

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Test();	// ����MyDll.dll�еĺ���
	return 0;
}