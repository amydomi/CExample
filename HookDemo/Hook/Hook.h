// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� HOOK_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// HOOK_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef HOOK_EXPORTS
#define HOOK_API extern "C" __declspec(dllexport)
#else
#define HOOK_API extern "C" __declspec(dllimport)
#endif

HMODULE g_hModule;
HHOOK g_hHook;

HOOK_API BOOL InstallHook();
HOOK_API BOOL UnInstallHook();
