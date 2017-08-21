// EditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UserCase.h"
#include "EditDlg.h"
#include "afxdialogex.h"


// CEditDlg 对话框

IMPLEMENT_DYNAMIC(CEditDlg, CDialogEx)

CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditDlg::IDD, pParent)
	, m_Actor(_T(""))
	, m_Usercase(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();
	/*m_type.AddString(_T("关联"));
	m_type.AddString(_T("继承"));
	m_type.AddString(_T("包含"));
	m_type.AddString(_T("扩展"));*/
}

CEditDlg::~CEditDlg()
{
}

void CEditDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Actor);
	DDV_MaxChars(pDX, m_Actor, 20);
	DDX_Text(pDX, IDC_EDIT2, m_Usercase);
	DDV_MaxChars(pDX, m_Usercase, 20);
	DDX_Control(pDX, IDC_COMBO1, m_type);
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CEditDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CEditDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IEditDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {9DE6E76C-B46F-44C7-9E9E-221BF05D08FE}
static const IID IID_IEditDlg =
{ 0x9DE6E76C, 0xB46F, 0x44C7, { 0x9E, 0x9E, 0x22, 0x1B, 0xF0, 0x5D, 0x8, 0xFE } };

BEGIN_INTERFACE_MAP(CEditDlg, CDialogEx)
	INTERFACE_PART(CEditDlg, IID_IEditDlg, Dispatch)
END_INTERFACE_MAP()


// CEditDlg 消息处理程序


BOOL CEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_type.AddString(_T("关联"));
	m_type.AddString(_T("继承"));
	m_type.AddString(_T("包含"));
	m_type.AddString(_T("扩展"));
	//m_type.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CEditDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_type.GetLBText(m_type.GetCurSel(), m_relation);
}
