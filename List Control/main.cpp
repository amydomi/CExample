#include "stdAfx.h"

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
void InitColumn(HWND);
void AddList(HWND);
void ClearList(HWND);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0L);
	return 0;
}

INT_PTR CALLBACK DlgProc(HWND dlgWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL fResult = TRUE;
	switch (uMsg)
	{
	case WM_INITDIALOG:
		InitColumn(dlgWnd);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_ADD:
			AddList(dlgWnd);
			break;
		case IDC_CLEAR_ALL:
			ClearList(dlgWnd);
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(dlgWnd, fResult);
		break;
	default:
		fResult = FALSE;
		break;
	}
	return (INT_PTR)fResult;
}

// �������
void AddList(HWND dlgWnd)
{
	LVITEM lvi;
	HWND hListView = GetDlgItem(dlgWnd, IDC_LIST1);
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 0;
	lvi.iItem = 0;
	lvi.pszText = _T("����");
	ListView_InsertItem(hListView, &lvi);

	lvi.iSubItem = 1;
	lvi.iItem = 0;
	lvi.pszText = _T("��");
	ListView_SetItem(hListView, &lvi);

	lvi.iSubItem = 2;
	lvi.iItem = 0;
	lvi.pszText = _T("25��");
	ListView_SetItem(hListView, &lvi);

	lvi.iSubItem = 3;
	lvi.iItem = 0;
	lvi.pszText = _T("���衢���衢��ɽ����Ӿ��");
	ListView_SetItem(hListView, &lvi);

}

// �������
void ClearList(HWND dlgWnd)
{
	if (IDYES == MessageBox(dlgWnd, _T("�Ƿ�ȷ�����ȫ�����ݣ�"), _T("��Ϣ"), MB_YESNO | MB_ICONQUESTION))
	{
		HWND hListView = GetDlgItem(dlgWnd, IDC_LIST1);
		ListView_DeleteAllItems(hListView);
	}
}

// ��ʼ��List Control
void InitColumn(HWND dlgWnd)
{
	HWND hListView;
	LVCOLUMN lvc;
	hListView = GetDlgItem(dlgWnd, IDC_LIST1);

	// ����ѡ����
	ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// ���ñ�ͷ
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;

	lvc.cx = 100;
	lvc.iSubItem = 0;
	lvc.pszText = _T("����");
	ListView_InsertColumn(hListView, 0, &lvc);

	lvc.cx = 80;
	lvc.iSubItem = 1;
	lvc.pszText = _T("�Ա�");
	ListView_InsertColumn(hListView, 1, &lvc);

	lvc.cx = 80;
	lvc.iSubItem = 2;
	lvc.pszText = _T("����");
	ListView_InsertColumn(hListView, 2, &lvc);

	lvc.cx = 200;
	lvc.iSubItem = 3;
	lvc.pszText = _T("����");
	ListView_InsertColumn(hListView, 3, &lvc);
}