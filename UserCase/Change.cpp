// Change.cpp : 实现文件
//

#include "stdafx.h"
#include "UserCase.h"
#include "Change.h"
#include "afxdialogex.h"


// CChange 对话框

IMPLEMENT_DYNAMIC(CChange, CDialogEx)

CChange::CChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChange::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CChange::~CChange()
{
}

void CChange::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_type);
}


BEGIN_MESSAGE_MAP(CChange, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CChange::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CChange, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IChange 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {CDD48358-0FE2-4789-BD56-465D8BF29C3F}
static const IID IID_IChange =
{ 0xCDD48358, 0xFE2, 0x4789, { 0xBD, 0x56, 0x46, 0x5D, 0x8B, 0xF2, 0x9C, 0x3F } };

BEGIN_INTERFACE_MAP(CChange, CDialogEx)
	INTERFACE_PART(CChange, IID_IChange, Dispatch)
END_INTERFACE_MAP()


// CChange 消息处理程序


BOOL CChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_type.AddString(_T("关联"));
	m_type.AddString(_T("继承"));
	m_type.AddString(_T("包含"));
	m_type.AddString(_T("扩展"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CChange::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_type.GetLBText(m_type.GetCurSel(), m_relation);
}
