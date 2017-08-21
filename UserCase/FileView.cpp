
#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "UserCase.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "UserCaseDoc.h"
#include "EditDlg.h"
#include "ChangeDlg.h"
#include "ConfirmDlg.h"
#include "MyObject.h"
#include "Change.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_ADD_T, OnAdd)
	ON_COMMAND(ID_EDIT_T, OnEdit)
	ON_COMMAND(ID_DEL_T, OnDel)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 消息处理程序

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("未能创建文件视图\n");
		return -1;      // 未能创建
	}

	// 加载视图图像: 
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由: 
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
	FillFileView();
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::FillFileView()
{
	HTREEITEM hRoot = m_wndFileView.InsertItem(_T("FakeApp 文件"), 0, 0);
	m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hSrc = m_wndFileView.InsertItem(_T("FakeApp 源文件"), 0, 0, hRoot);

	m_wndFileView.InsertItem(_T("FakeApp.cpp"), 1, 1, hSrc);
	m_wndFileView.InsertItem(_T("FakeApp.rc"), 1, 1, hSrc);
	m_wndFileView.InsertItem(_T("FakeAppDoc.cpp"), 1, 1, hSrc);
	m_wndFileView.InsertItem(_T("FakeAppView.cpp"), 1, 1, hSrc);
	m_wndFileView.InsertItem(_T("MainFrm.cpp"), 1, 1, hSrc);
	m_wndFileView.InsertItem(_T("StdAfx.cpp"), 1, 1, hSrc);

	HTREEITEM hInc = m_wndFileView.InsertItem(_T("FakeApp 头文件"), 0, 0, hRoot);

	m_wndFileView.InsertItem(_T("FakeApp.h"), 2, 2, hInc);
	m_wndFileView.InsertItem(_T("FakeAppDoc.h"), 2, 2, hInc);
	m_wndFileView.InsertItem(_T("FakeAppView.h"), 2, 2, hInc);
	m_wndFileView.InsertItem(_T("Resource.h"), 2, 2, hInc);
	m_wndFileView.InsertItem(_T("MainFrm.h"), 2, 2, hInc);
	m_wndFileView.InsertItem(_T("StdAfx.h"), 2, 2, hInc);

	HTREEITEM hRes = m_wndFileView.InsertItem(_T("FakeApp 资源文件"), 0, 0, hRoot);

	m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
	m_wndFileView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
	m_wndFileView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
	m_wndFileView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);

	m_wndFileView.Expand(hRoot, TVE_EXPAND);
	m_wndFileView.Expand(hSrc, TVE_EXPAND);
	m_wndFileView.Expand(hInc, TVE_EXPAND);
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项: 
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	AfxMessageBox(_T("属性...."));

}

void CFileView::OnFileOpen()
{
	// TODO:  在此处添加命令处理程序代码
}

void CFileView::OnFileOpenWith()
{
	// TODO:  在此处添加命令处理程序代码
}

void CFileView::OnDummyCompile()
{
	// TODO:  在此处添加命令处理程序代码
}

void CFileView::OnEditCut()
{
	// TODO:  在此处添加命令处理程序代码
}

void CFileView::OnEditCopy()
{
	// TODO:  在此处添加命令处理程序代码
}

void CFileView::OnEditClear()
{
	// TODO:  在此处添加命令处理程序代码
}


void CFileView::OnAdd()
{
	// TODO:  在此处添加命令处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();

	CEditDlg pDlg;
	CString str1, str2, str3;
	bool flag = false, flag1 = false;
	if (pDlg.DoModal() == IDOK)
	{
		str1 = pDlg.m_Actor;
		str2 = pDlg.m_Usercase;
		str3 = pDlg.m_relation;
		POSITION pos = pDoc->m_ObjectDraw.m_objList.GetHeadPosition();
		while (pos)
		{
			CMyObject* obj = (CMyObject*)pDoc->m_ObjectDraw.m_objList.GetNext(pos);
			if (obj->m_Actor.name == str1)
			{
				flag = true;
				for (vector<Usercase>::iterator it = obj->m_Actor.m_Usercase.begin(); it != obj->m_Actor.m_Usercase.end(); it++)
				{
					if (it->name == str2&&it->type == str3)
					{
						flag1 = true;
						break;
					}
				}
				if (flag1 == false)
				{
					Usercase uc;
					uc.name = str2;
					uc.type = str3;
					obj->m_Actor.m_Usercase.push_back(uc);
				}
				break;
			}
		}
		if (flag == false)
		{
			CMyObject* obj = new CMyObject();
			obj->m_Actor.name = str1;
			Usercase uc;
			uc.name = str2;
			uc.type = str3;
			obj->m_Actor.m_Usercase.push_back(uc);
			pDoc->m_ObjectDraw.m_objList.AddTail(obj);
		}

		pDoc->m_ObjectDraw.AddLog(_T("添加一个元素"));
		pDoc->InitAllWnd(FALSE);
		Invalidate(FALSE);
	}
}


void CFileView::OnEdit()
{
	// TODO:  在此处添加命令处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();

	HTREEITEM hItem, hChildItem;
	hItem = m_wndFileView.GetSelectedItem();
	hChildItem = m_wndFileView.GetChildItem(hItem);//获取子节点
	if (hChildItem != NULL)
	{
		CChangeDlg pDlg;
		CString str;
		if (pDlg.DoModal() == IDOK)
		{
			str = pDlg.m_change;
			m_wndFileView.SetItemText(hItem, str);

			getDataFromTreeCtrlToDoc();
			pChildFrame->GetActiveView()->Invalidate(TRUE);
			pDoc->m_ObjectDraw.AddLog(L"编辑某个元素");
			pDoc->InitAllWnd(FALSE);
		}
	}
	else
	{
		CChange pDlg;
		CString str;
		if (pDlg.DoModal() == IDOK)
		{
			str = pDlg.m_relation;
			m_wndFileView.SetItemText(hItem, str);

			getDataFromTreeCtrlToDoc();
			pChildFrame->GetActiveView()->Invalidate(TRUE);
			pDoc->m_ObjectDraw.AddLog(L"编辑某个元素");
			pDoc->InitAllWnd(FALSE);
		}
	}
}


void CFileView::OnDel()
{
	// TODO:  在此处添加命令处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();

	HTREEITEM hItem, hNextItem, hPrevItem, hChildItem, hRoot;
	hItem = m_wndFileView.GetSelectedItem();
	hRoot = m_wndFileView.GetParentItem(hItem);
	hPrevItem = m_wndFileView.GetPrevSiblingItem(hItem);
	hNextItem = m_wndFileView.GetNextSiblingItem(hItem);
	hChildItem = m_wndFileView.GetChildItem(hItem);
	if ((hRoot == NULL) || (hRoot != NULL&&hChildItem != NULL && (hNextItem != NULL || hPrevItem != NULL)))
	{
		CConfirmDlg pDlg;
		if (pDlg.DoModal() == IDOK)
		{
			m_wndFileView.DeleteItem(hItem);
			getDataFromTreeCtrlToDoc();

			pDoc->m_ObjectDraw.AddLog(_T("删除了一个元素"));
			pDoc->InitAllWnd(FALSE);
			Invalidate(FALSE);
		}
	}
	else if (hRoot != NULL&&hChildItem != NULL && hNextItem == NULL && hPrevItem == NULL)
	{
		m_wndFileView.DeleteItem(hRoot);
		getDataFromTreeCtrlToDoc();

		pDoc->m_ObjectDraw.AddLog(_T("删除了一个元素"));
		pDoc->InitAllWnd(FALSE);
		Invalidate(FALSE);
	}
	else
	{
		MessageBox(_T("不能删除此项！"));
	}
}

void CFileView::getDataFromTreeCtrlToDoc()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();
	//RemoveAll前清理
	POSITION pos = pDoc->m_ObjectDraw.m_objList.GetHeadPosition();
	while (pos)
	{
		CMyObject* obj = (CMyObject*)pDoc->m_ObjectDraw.m_objList.GetNext(pos);
		delete obj;
		obj = NULL;
	}

	pDoc->m_ObjectDraw.m_objList.RemoveAll();

	CString str;
	CMyObject* obj = new CMyObject();
	Usercase usecase;

	hRoot = m_wndFileView.GetRootItem();//获取根节点
	if (hRoot != NULL)
	{
		str = m_wndFileView.GetItemText(hRoot);
		obj->m_Actor.name = str;
		hChildItem = m_wndFileView.GetChildItem(hRoot);//获取子节点
		if (hChildItem != NULL)
		{
			str = m_wndFileView.GetItemText(hChildItem);
			usecase.name = str;

			hChildItem2 = m_wndFileView.GetChildItem(hChildItem);
			str = m_wndFileView.GetItemText(hChildItem2);
			usecase.type = str;
			obj->m_Actor.m_Usercase.push_back(usecase);

			hChildItem = m_wndFileView.GetNextSiblingItem(hChildItem);
			while (hChildItem != NULL)
			{
				Usercase usecase;
				str = m_wndFileView.GetItemText(hChildItem);
				usecase.name = str;
				hChildItem2 = m_wndFileView.GetChildItem(hChildItem);
				str = m_wndFileView.GetItemText(hChildItem2);
				usecase.type = str;
				obj->m_Actor.m_Usercase.push_back(usecase);
				hChildItem = m_wndFileView.GetNextSiblingItem(hChildItem);
			}
		}
		pDoc->m_ObjectDraw.m_objList.AddTail(obj);
		
		hRoot = m_wndFileView.GetNextSiblingItem(hRoot);
		while (hRoot != NULL)
		{
			CMyObject* obj = new CMyObject();
			Usercase usecase;
			obj->m_Actor.name = "";
			obj->m_Actor.m_Usercase.clear();

			str = m_wndFileView.GetItemText(hRoot);
			obj->m_Actor.name = str;
			hChildItem = m_wndFileView.GetChildItem(hRoot);
			if (hChildItem != NULL)
			{
				str = m_wndFileView.GetItemText(hChildItem);
				usecase.name = str;
				hChildItem2 = m_wndFileView.GetChildItem(hChildItem);
				str = m_wndFileView.GetItemText(hChildItem2);
				usecase.type = str;
				obj->m_Actor.m_Usercase.push_back(usecase);
				hChildItem = m_wndFileView.GetNextSiblingItem(hChildItem);
				while (hChildItem != NULL)
				{
					Usercase usecase;
					str = m_wndFileView.GetItemText(hChildItem);
					usecase.name = str;
					hChildItem2 = m_wndFileView.GetChildItem(hChildItem);
					str = m_wndFileView.GetItemText(hChildItem2);
					usecase.type = str;
					obj->m_Actor.m_Usercase.push_back(usecase);
					hChildItem = m_wndFileView.GetNextSiblingItem(hChildItem);
				}
			}
			pDoc->m_ObjectDraw.m_objList.AddTail(obj);
			hRoot = m_wndFileView.GetNextSiblingItem(hRoot);
		}
	}
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 锁定*/);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图:  %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}


