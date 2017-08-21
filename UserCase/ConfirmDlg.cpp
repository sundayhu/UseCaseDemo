// ConfirmDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UserCase.h"
#include "ConfirmDlg.h"
#include "afxdialogex.h"


// CConfirmDlg 对话框

IMPLEMENT_DYNAMIC(CConfirmDlg, CDialogEx)

CConfirmDlg::CConfirmDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfirmDlg::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CConfirmDlg::~CConfirmDlg()
{
}

void CConfirmDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfirmDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CConfirmDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IConfirmDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {24ACB983-321D-43D9-A77D-DF7294114CE1}
static const IID IID_IConfirmDlg =
{ 0x24ACB983, 0x321D, 0x43D9, { 0xA7, 0x7D, 0xDF, 0x72, 0x94, 0x11, 0x4C, 0xE1 } };

BEGIN_INTERFACE_MAP(CConfirmDlg, CDialogEx)
	INTERFACE_PART(CConfirmDlg, IID_IConfirmDlg, Dispatch)
END_INTERFACE_MAP()


// CConfirmDlg 消息处理程序
