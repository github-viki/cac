
// mpwDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mpw.h"
#include "mpwDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmpwDlg �Ի���




CmpwDlg::CmpwDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmpwDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmpwDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmpwDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CmpwDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CmpwDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CmpwDlg ��Ϣ�������

BOOL CmpwDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmpwDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmpwDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmpwDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmpwDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NET_API_STATUS nStatus;
	CString oldPWD;
	CString newPWD;
	CString newConPWD;
	
	GetDlgItem(IDC_EDIT1)->GetWindowTextA(oldPWD);
	GetDlgItem(IDC_EDIT2)->GetWindowTextA(newPWD);
	GetDlgItem(IDC_EDIT3)->GetWindowTextA(newConPWD);
	if (oldPWD.IsEmpty()||newConPWD.IsEmpty()||newPWD.IsEmpty())
	{
		GetDlgItem(IDC_MESS)->SetWindowText("�����п�");
		return ;
	}
	if (newConPWD.Compare(newPWD))
	{
		GetDlgItem(IDC_MESS)->SetWindowText("�����벻һ��");
		return ;
	}
	CHAR oldpwd[32]={'0'};
	CHAR newpwd[32]={'0'};
	WCHAR oldPWD_W[64]={L'0'};
	WCHAR newPWD_W[64]={L'0'};
	strcpy(oldpwd,oldPWD.GetBuffer(oldPWD.GetLength()));
	strcpy(newpwd,newPWD.GetBuffer(newPWD.GetLength()));
	MultiByteToWideChar(CP_ACP,0,oldpwd,-1,oldPWD_W,64);
		MultiByteToWideChar(CP_ACP,0,newpwd,-1,newPWD_W,64);
	
	nStatus=NetUserChangePassword(NULL,NULL,oldPWD_W,newPWD_W);
	DWORD ERRNO=GetLastError();
	if(NERR_Success==nStatus)
	{
		GetDlgItem(IDC_MESS)->SetWindowText("�޸ĳɹ�");
		Sleep(1500);
	}
	else
	{
		
		switch(ERRNO)
		{
		case ERROR_ACCESS_DENIED:
			  {
				GetDlgItem(IDC_MESS)->SetWindowText("��Ȩ��");
				return ;
			  }
		case ERROR_INVALID_PASSWORD:
			{
				GetDlgItem(IDC_MESS)->SetWindowText("��Ч����");
				return ;
			}
		case NERR_PasswordTooShort:
			{
				GetDlgItem(IDC_MESS)->SetWindowText("�������");
				return ;
			}
		
		case NERR_UserNotFound:
			{
				GetDlgItem(IDC_MESS)->SetWindowText("��Ч�û�");
				return ;
			}
		case NERR_InvalidComputer:
			{
				GetDlgItem(IDC_MESS)->SetWindowText("invalidcomputer");
				return ;
			}
		default:
			{
			
			GetDlgItem(IDC_MESS)->SetWindowText("���������");
			return ;
			}
		}
	}
	CDialogEx::OnOK();
}
