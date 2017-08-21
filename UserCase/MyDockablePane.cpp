// MyDockablePane.cpp : ʵ���ļ�
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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDockablePane::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CMyDockablePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CMyDockablePane, CDockablePane)
END_DISPATCH_MAP()

// ע��: ������� IID_IMyDockablePane ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {937EE013-9925-44C6-AD51-1EC6AC937D0C}
static const IID IID_IMyDockablePane =
{ 0x937EE013, 0x9925, 0x44C6, { 0xAD, 0x51, 0x1E, 0xC6, 0xAC, 0x93, 0x7D, 0xC } };

BEGIN_INTERFACE_MAP(CMyDockablePane, CDockablePane)
	INTERFACE_PART(CMyDockablePane, IID_IMyDockablePane, Dispatch)
END_INTERFACE_MAP()


// CMyDockablePane ��Ϣ�������




int CMyDockablePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
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

	// TODO:  �ڴ˴������Ϣ����������
	m_innerDlg.SetWindowPos(this, -1, -1, cx, cy, SWP_NOMOVE);
	m_innerDlg.ShowWindow(SW_SHOW);
}
