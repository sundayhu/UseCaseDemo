// ChangeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UserCase.h"
#include "ChangeDlg.h"
#include "afxdialogex.h"


// CChangeDlg 对话框

IMPLEMENT_DYNAMIC(CChangeDlg, CDialogEx)

CChangeDlg::CChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeDlg::IDD, pParent)
	, m_change(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CChangeDlg::~CChangeDlg()
{
}

void CChangeDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_change);
	DDV_MaxChars(pDX, m_change, 20);
}


BEGIN_MESSAGE_MAP(CChangeDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CChangeDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IChangeDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {3EE0BAE0-C572-4F09-9A8A-4A2AC8FB3405}
static const IID IID_IChangeDlg =
{ 0x3EE0BAE0, 0xC572, 0x4F09, { 0x9A, 0x8A, 0x4A, 0x2A, 0xC8, 0xFB, 0x34, 0x5 } };

BEGIN_INTERFACE_MAP(CChangeDlg, CDialogEx)
	INTERFACE_PART(CChangeDlg, IID_IChangeDlg, Dispatch)
END_INTERFACE_MAP()


// CChangeDlg 消息处理程序
