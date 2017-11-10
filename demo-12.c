#include <Windows.h>
#include <tchar.h>
#include <WinError.h>

LPVOID GetErorMessage(DWORD);

// ����Visual Studio���Եļ���(Watch)���ڼ��� $err,hr�鿴������Ϣ
// Windows����ĺ궨���� WinError.h ��
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
	LPVOID lpMsgBuf;	// �����ַ���ָ�룬��ҪתΪPTSTR����ʾ
	DWORD dw; // ������
	
	// ��дһ������ĵ��ã�ʹ��GetLastError() ��ȡ������
	GetDlgItemInt(NULL, 0, FALSE, FALSE);

	dw = GetLastError(); // ����޴���GetLastError = 0 = ERROR_SUCCESS
	lpMsgBuf = GetErorMessage(dw);
	MessageBox(NULL, (PTSTR)lpMsgBuf, _T("����"), MB_OK | MB_ICONERROR);
	return dw;
	return 0;
}

// ���ݴ����ţ����ش�����Ϣ�ַ������׵�ַ
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