#include <Windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// �򿪼��±�����
	HINSTANCE hd = ShellExecute(NULL, TEXT("open"), TEXT("C:\\Windows\\notepad.exe"), NULL, TEXT("D:\\"), SW_SHOW);

	// 
	HWND hWnd = NULL;
	do {
		Sleep(300);
		// ��ȡ������
		hWnd = FindWindow(NULL, TEXT("�ޱ��� - ���±�"));
	} while (NULL == hWnd);

	// ��ȡ�Ӵ���
	HWND childWnd = FindWindowEx(hWnd, NULL, TEXT("Edit"), NULL);

	// �����ַ���Ϣ
	SendMessage(childWnd, WM_CHAR, 'H', 0);
	SendMessage(childWnd, WM_CHAR, 'E', 0);
	SendMessage(childWnd, WM_CHAR, 'L', 0);
	SendMessage(childWnd, WM_CHAR, 'L', 0);
	SendMessage(childWnd, WM_CHAR, 'O', 0);

	// ��������Ҽ���Ϣ
	do {
		Sleep(3000); // ѭ��3��һ��ִ��һ���Ҽ�
		
		// ��ȡ��ǰ����λ��
		POINT point;
		GetCursorPos(&point);

		// ��ȡ��������Ļ�ľ���
		RECT rect;
		GetWindowRect(childWnd, &rect);

		SendMessage(childWnd, WM_RBUTTONDOWN, 0, MAKELPARAM(point.x - rect.left, point.y - rect.top));
		SendMessage(childWnd, WM_RBUTTONUP, 0, MAKELPARAM(point.x - rect.left, point.y - rect.top));
	} while (TRUE);
	
	return 0;
}