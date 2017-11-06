#include <Windows.h>
#include <tchar.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	// ��������ָ��
	typedef void (* TestFn)();
	typedef int (* AddFn)(int, int);

	// ����ָ�����
	TestFn Test;
	AddFn add;

	int a = 10, b = 20;
	TCHAR bufResult[50];

	// ����DLL�ļ�������ʹ�� LoadLibrary, LoadLibraryEx, LoadPackagedLibrary, or GetModuleHandle ����DLL�ļ�
	HMODULE handle = LoadLibrary(_T("MyDll.dll"));

	if (handle == NULL) {
		MessageBox(NULL, _T("DLL����ʧ�ܣ�"), _T("��Ϣ"), MB_OK | MB_ICONERROR);
		return -1;
	}

	// ��ȡ������ַ
	Test = (TestFn)GetProcAddress(handle, "Test");
	add = (AddFn)GetProcAddress(handle, "add");

	// ������ַ��ȡʧ�ܣ�����NULL
	if (NULL == Test || NULL == add) {
		MessageBox(NULL, _T("����ִ��ʧ�ܣ�"), _T("��Ϣ"), MB_OK | MB_ICONERROR);
		return -1;
	}

	// ִ�к���
	Test();
	wsprintf(bufResult, _T("%d + %d = %d"), a, b, add(a, b));
	MessageBox(NULL, bufResult, _T("������"), MB_OK);

	return 0;
}