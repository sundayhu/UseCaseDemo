
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "MyDockablePane.h"

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
	COutputWnd        m_wndOutput;
	CPropertiesWnd    m_wndProperties;
	CMyDockablePane   m_wndMyDockablePane;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	CMyDockablePane* GetMyDockablePane(){
		return &(this->m_wndMyDockablePane);
	}
	COutputList* GetOutputList(){
		return this->m_wndOutput.GetOutputList();
	}
	CViewTree* GetTree(){
		return this->m_wndFileView.GetTree();
	}
	CMFCStatusBar* GetStatusBar(){
		return &(this->m_wndStatusBar);
	}
	CPropertiesWnd* GetPropertiesWnd(){
		return &(this->m_wndProperties);
	}
	CMFCToolBar*  GetToolBar(){
		return &(this->m_wndToolBar);
	}

	CTreeCtrl* GetTreeCtrl(){
		return &(this->m_wndMyDockablePane.m_innerDlg.m_tree);
	}

	CInnerDlg* GetMyInnerDlg(){
		return &(this->m_wndMyDockablePane.m_innerDlg);
	}
protected:
	afx_msg LRESULT OnActivateTabChanged(WPARAM wParam, LPARAM lParam);
};


