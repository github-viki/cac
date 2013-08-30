
// mpwDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mpw.h"
#include "mpwDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmpwDlg 对话框




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


// CmpwDlg 消息处理程序

BOOL CmpwDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmpwDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmpwDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmpwDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmpwDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	NET_API_STATUS nStatus;
	CString oldPWD;
	CString newPWD;
	CString newConPWD;
	
	GetDlgItem(IDC_EDIT1)->GetWindowTextA(oldPWD);
	GetDlgItem(IDC_EDIT2)->GetWindowTextA(newPWD);
	GetDlgItem(IDC_EDIT3)->GetWindowTextA(newConPWD);
	if (oldPWD.IsEmpty()||newConPWD.IsEmpty()||newPWD.IsEmpty())
	{
		GetDlgItem(IDC_MESS)->SetWindowText("输入有空");
		return ;
	}
	if (newConPWD.Compare(newPWD))
	{
		GetDlgItem(IDC_MESS)->SetWindowText("新密码不一致");
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
		GetDlgItem(IDC_MESS)->SetWindowText("修改成功");
		Sleep(1500);
	}
	else
	{
		
		switch(ERRNO)
		{
		case ERROR_ACCESS_DENIED:
			  {
				GetDlgItem(IDC_MESS)->SetWindowText("无权限");
				return ;
			  }
		case ERROR_INVALID_PASSWORD:
			{
				GetDlgItem(IDC_MESS)->SetWindowText("无效密码");
				return ;
			}
		case NERR_PasswordTooShort:
			{
				GetDlgItem(IDC_MESS)->SetWindowText("密码过短");
				return ;
			}
		
		case NERR_UserNotFound:
			{
				GetDlgItem(IDC_MESS)->SetWindowText("无效用户");
				return ;
			}
		case NERR_InvalidComputer:
			{
				GetDlgItem(IDC_MESS)->SetWindowText("invalidcomputer");
				return ;
			}
		default:
			{
			
			GetDlgItem(IDC_MESS)->SetWindowText("旧密码错误");
			return ;
			}
		}
	}
	CDialogEx::OnOK();
}
