#include <Windows.h>
#include <tchar.h>

#include "resource.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

typedef struct {
	int id;			// �ؼ�ID
	int value;		// �ؼ�ֵ
} RadioButton;

INT_PTR CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hWnd, IDC_GENDER_MALE, IDC_GENDER_WOMAN, IDC_GENDER_MALE);
		CheckRadioButton(hWnd, IDC_LIVE_01, IDC_LIVE_03, IDC_LIVE_01);
		break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BUTTON1) {

			// �Ա�
			RadioButton genders[] = {
				{ IDC_GENDER_MALE, 1 },
				{ IDC_GENDER_WOMAN, 2 }
			};

			// ����
			RadioButton lives[] = {
				{ IDC_LIVE_01, 1 },
				{ IDC_LIVE_02, 2 },
				{ IDC_LIVE_03, 3 }
			};

			// ���
			TCHAR result[255] = { 0 },
				  szGender[4] = { 0 },
				  szLive[6] = { 0 };
			int iGender = 0, iLive = 0;

			// ��ȡѡ�е��Ա�
			for (int i = 0; i < 2; ++i) {
				if (BST_CHECKED == IsDlgButtonChecked(hWnd, genders[i].id)) {
					GetDlgItemText(hWnd, genders[i].id, szGender, 4);
					iGender = genders[i].value;
					break;
				}
			}

			// ��ȡѡ�ֵ�����
			for (int i = 0; i < 3; ++i) {
				if (BST_CHECKED == IsDlgButtonChecked(hWnd, lives[i].id)) {
					GetDlgItemText(hWnd, lives[i].id, szLive, 4);
					iLive = lives[i].value;
					break;
				}
			}

			// �����ʾ
			wsprintf(result, _T("�Ա�%s(%d)\n���ۣ�%s(%d)"), szGender, iGender, szLive, iLive);
			MessageBox(hWnd, result, _T("��Ϣ"), MB_OK);
			break;
		}
		else {
			return FALSE;
		}
	}
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PTSTR cmdLine, int cmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
	return 0;
}