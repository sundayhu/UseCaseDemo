
// UserCaseDoc.cpp : CUserCaseDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "UserCase.h"
#endif

#include "UserCaseDoc.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "MyObject.h"
#include "InnerDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CUserCaseDoc

IMPLEMENT_DYNCREATE(CUserCaseDoc, CDocument)

BEGIN_MESSAGE_MAP(CUserCaseDoc, CDocument)
END_MESSAGE_MAP()


// CUserCaseDoc 构造/析构

CUserCaseDoc::CUserCaseDoc()
{
	// TODO:  在此添加一次性构造代码

}

CUserCaseDoc::~CUserCaseDoc()
{
}

BOOL CUserCaseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	InitAllWnd(TRUE);
	return TRUE;
}




// CUserCaseDoc 序列化

void CUserCaseDoc::Serialize(CArchive& ar)
{
	m_ObjectDraw.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}
void CUserCaseDoc::InitDockablePane()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CTreeCtrl* pTree = pMainFrame->GetTreeCtrl();
	CInnerDlg* pMyDlg = pMainFrame->GetMyInnerDlg();
	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hChildItem; // 可表示任一分类节点的句柄
	HTREEITEM hChildItem2; // 可表示任一分类节点的句柄
	pTree->DeleteAllItems();

	POSITION pos = m_ObjectDraw.m_objList.GetHeadPosition();
	if (pos != NULL)
	{
		CMyObject* obj = (CMyObject*)(m_ObjectDraw.m_objList.GetNext(pos));
		int count = 0;
		hRoot = pTree->InsertItem(obj->m_Actor.name, TVI_ROOT);
		count = obj->m_Actor.m_Usercase.size();
		hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[0].name, hRoot);//添加第一个孩子节点
		hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[0].type, hChildItem);
		for (int i = 1; i < count; i++)
		{
			hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[i].name, hRoot, hChildItem);//添加孩子节点
			hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[i].type, hChildItem);
		}
		while (pos)
		{
			CMyObject* obj = (CMyObject*)(m_ObjectDraw.m_objList.GetNext(pos));
			hRoot = pTree->InsertItem(obj->m_Actor.name, TVI_ROOT, hRoot);
			count = obj->m_Actor.m_Usercase.size();
			hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[0].name, hRoot);//添加第一个孩子节点
			hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[0].type, hChildItem);
			for (int i = 1; i < count; i++)
			{
				hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[i].name, hRoot, hChildItem);//添加孩子节点
				hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[i].type, hChildItem);
			}
		}
	}
}

/************************************************************************/
/*  输出                                                                     */
/************************************************************************/
void CUserCaseDoc::InitOutputList()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetOutputList()->ResetContent();
	POSITION pos = m_ObjectDraw.m_logList.GetHeadPosition();
	while (pos)
	{
		pMainFrame->GetOutputList()->AddString(m_ObjectDraw.m_logList.GetNext(pos));
	}
	pMainFrame->GetOutputList()->SetCurSel(pMainFrame->GetOutputList()->GetCount() - 1);
}


void CUserCaseDoc::InitTreeData()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CViewTree* pTree = pMainFrame->GetTree();
	pTree->DeleteAllItems();
	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hChildItem; // 可表示任一分类节点的句柄
	HTREEITEM hChildItem2; // 可表示任一分类节点的句柄
	pTree->DeleteAllItems();

	POSITION pos = m_ObjectDraw.m_objList.GetHeadPosition();
	if (pos != NULL)
	{
		CMyObject* obj = (CMyObject*)(m_ObjectDraw.m_objList.GetNext(pos));
		int count = 0;
		hRoot = pTree->InsertItem(obj->m_Actor.name, TVI_ROOT);
		count = obj->m_Actor.m_Usercase.size();
		hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[0].name, hRoot);//添加第一个孩子节点
		hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[0].type, hChildItem);
		for (int i = 1; i < count; i++)
		{
			hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[i].name, hRoot, hChildItem);//添加孩子节点
			hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[i].type, hChildItem);
		}
		while (pos)
		{
			CMyObject* obj = (CMyObject*)(m_ObjectDraw.m_objList.GetNext(pos));
			hRoot = pTree->InsertItem(obj->m_Actor.name, TVI_ROOT, hRoot);
			count = obj->m_Actor.m_Usercase.size();
			hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[0].name, hRoot);//添加第一个孩子节点
			hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[0].type, hChildItem);
			for (int i = 1; i < count; i++)
			{
				hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[i].name, hRoot, hChildItem);//添加孩子节点
				hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[i].type, hChildItem);
			}
		}
	}
}

/************************************************************************/
/* 刷新所有的窗口                                                          */
/* bEraseLog  是否擦除日志信息                                             */
/************************************************************************/
void CUserCaseDoc::InitAllWnd(BOOL bEraseLog)
{
	this->InitDockablePane();
	this->InitTreeData();
	if (bEraseLog)
	{
		this->m_ObjectDraw.m_logList.RemoveAll();
	}
	this->InitOutputList();
}
#ifdef SHARED_HANDLERS

// 缩略图的支持
void CUserCaseDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CUserCaseDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CUserCaseDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CUserCaseDoc 诊断

#ifdef _DEBUG
void CUserCaseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUserCaseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CUserCaseDoc 命令


BOOL CUserCaseDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	InitAllWnd(TRUE);
	return TRUE;
}


void CUserCaseDoc::OnCloseDocument()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDocument::OnCloseDocument();
}
