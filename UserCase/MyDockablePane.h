#pragma once
#include "InnerDlg.h"
#include "Resource.h"

// CMyDockablePane

class CMyDockablePane : public CDockablePane
{
	DECLARE_DYNAMIC(CMyDockablePane)

public:
	CMyDockablePane();
	virtual ~CMyDockablePane();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CInnerDlg m_innerDlg;
};


