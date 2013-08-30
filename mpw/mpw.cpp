
// mpw.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "mpw.h"
#include "mpwDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmpwApp

BEGIN_MESSAGE_MAP(CmpwApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CmpwApp ����

CmpwApp::CmpwApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CmpwApp ����

CmpwApp theApp;


// CmpwApp ��ʼ��

BOOL CmpwApp::InitInstance()
{
	/************************************************************************/
	/* ����skinmagicƤ����Դ                                                */
	/************************************************************************/
	VERIFY(InitSkinMagicLib(AfxGetInstanceHandle(),NULL, NULL, NULL));
	//����Դ�м���Ƥ���ļ���Ҳ�����ô��롰LoadSkinFile("corona.smf")��ֱ�Ӵ��ļ��м���
	VERIFY(LoadSkinFromResource(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_SKINMAGIC), _T("Skinmagic")));
	//����ĺ����ĵڶ�������IDR_SKINMAGIC1���Լ���ӵ������е���Դ�����滹���ᵽ��
	//���öԻ���Ĭ��Ƥ��
	VERIFY(SetDialogSkin("Dialog"));

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CmpwDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

