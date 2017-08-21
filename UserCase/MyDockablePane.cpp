// MyDockablePane.cpp : 实现文件
//

#include "stdafx.h"
#include "UserCase.h"
#include "MyDockablePane.h"


// CMyDockablePane

IMPLEMENT_DYNAMIC(CMyDockablePane, CDockablePane)

CMyDockablePane::CMyDockablePane()
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();
}

CMyDockablePane::~CMyDockablePane()
{
}

void CMyDockablePane::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDockablePane::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CMyDockablePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CMyDockablePane, CDockablePane)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IMyDockablePane 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {937EE013-9925-44C6-AD51-1EC6AC937D0C}
static const IID IID_IMyDockablePane =
{ 0x937EE013, 0x9925, 0x44C6, { 0xAD, 0x51, 0x1E, 0xC6, 0xAC, 0x93, 0x7D, 0xC } };

BEGIN_INTERFACE_MAP(CMyDockablePane, CDockablePane)
	INTERFACE_PART(CMyDockablePane, IID_IMyDockablePane, Dispatch)
END_INTERFACE_MAP()


// CMyDockablePane 消息处理程序




int CMyDockablePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rect;
	rect.SetRectEmpty();
	if (!m_innerDlg.Create(IDD_DIALOG1, this))
	{
		TRACE0("error");
		return -1;
	}
	m_innerDlg.ShowWindow(SW_SHOW);
	return 0;
}


void CMyDockablePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	m_innerDlg.SetWindowPos(this, -1, -1, cx, cy, SWP_NOMOVE);
	m_innerDlg.ShowWindow(SW_SHOW);
}
