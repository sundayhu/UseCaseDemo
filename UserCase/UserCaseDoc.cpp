
// UserCaseDoc.cpp : CUserCaseDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CUserCaseDoc ����/����

CUserCaseDoc::CUserCaseDoc()
{
	// TODO:  �ڴ����һ���Թ������

}

CUserCaseDoc::~CUserCaseDoc()
{
}

BOOL CUserCaseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	InitAllWnd(TRUE);
	return TRUE;
}




// CUserCaseDoc ���л�

void CUserCaseDoc::Serialize(CArchive& ar)
{
	m_ObjectDraw.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
	}
}
void CUserCaseDoc::InitDockablePane()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CTreeCtrl* pTree = pMainFrame->GetTreeCtrl();
	CInnerDlg* pMyDlg = pMainFrame->GetMyInnerDlg();
	HTREEITEM hRoot;     // ���ĸ��ڵ�ľ��   
	HTREEITEM hChildItem; // �ɱ�ʾ��һ����ڵ�ľ��
	HTREEITEM hChildItem2; // �ɱ�ʾ��һ����ڵ�ľ��
	pTree->DeleteAllItems();

	POSITION pos = m_ObjectDraw.m_objList.GetHeadPosition();
	if (pos != NULL)
	{
		CMyObject* obj = (CMyObject*)(m_ObjectDraw.m_objList.GetNext(pos));
		int count = 0;
		hRoot = pTree->InsertItem(obj->m_Actor.name, TVI_ROOT);
		count = obj->m_Actor.m_Usercase.size();
		hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[0].name, hRoot);//��ӵ�һ�����ӽڵ�
		hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[0].type, hChildItem);
		for (int i = 1; i < count; i++)
		{
			hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[i].name, hRoot, hChildItem);//��Ӻ��ӽڵ�
			hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[i].type, hChildItem);
		}
		while (pos)
		{
			CMyObject* obj = (CMyObject*)(m_ObjectDraw.m_objList.GetNext(pos));
			hRoot = pTree->InsertItem(obj->m_Actor.name, TVI_ROOT, hRoot);
			count = obj->m_Actor.m_Usercase.size();
			hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[0].name, hRoot);//��ӵ�һ�����ӽڵ�
			hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[0].type, hChildItem);
			for (int i = 1; i < count; i++)
			{
				hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[i].name, hRoot, hChildItem);//��Ӻ��ӽڵ�
				hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[i].type, hChildItem);
			}
		}
	}
}

/************************************************************************/
/*  ���                                                                     */
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
	HTREEITEM hRoot;     // ���ĸ��ڵ�ľ��   
	HTREEITEM hChildItem; // �ɱ�ʾ��һ����ڵ�ľ��
	HTREEITEM hChildItem2; // �ɱ�ʾ��һ����ڵ�ľ��
	pTree->DeleteAllItems();

	POSITION pos = m_ObjectDraw.m_objList.GetHeadPosition();
	if (pos != NULL)
	{
		CMyObject* obj = (CMyObject*)(m_ObjectDraw.m_objList.GetNext(pos));
		int count = 0;
		hRoot = pTree->InsertItem(obj->m_Actor.name, TVI_ROOT);
		count = obj->m_Actor.m_Usercase.size();
		hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[0].name, hRoot);//��ӵ�һ�����ӽڵ�
		hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[0].type, hChildItem);
		for (int i = 1; i < count; i++)
		{
			hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[i].name, hRoot, hChildItem);//��Ӻ��ӽڵ�
			hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[i].type, hChildItem);
		}
		while (pos)
		{
			CMyObject* obj = (CMyObject*)(m_ObjectDraw.m_objList.GetNext(pos));
			hRoot = pTree->InsertItem(obj->m_Actor.name, TVI_ROOT, hRoot);
			count = obj->m_Actor.m_Usercase.size();
			hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[0].name, hRoot);//��ӵ�һ�����ӽڵ�
			hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[0].type, hChildItem);
			for (int i = 1; i < count; i++)
			{
				hChildItem = pTree->InsertItem(obj->m_Actor.m_Usercase[i].name, hRoot, hChildItem);//��Ӻ��ӽڵ�
				hChildItem2 = pTree->InsertItem(obj->m_Actor.m_Usercase[i].type, hChildItem);
			}
		}
	}
}

/************************************************************************/
/* ˢ�����еĴ���                                                          */
/* bEraseLog  �Ƿ������־��Ϣ                                             */
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

// ����ͼ��֧��
void CUserCaseDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CUserCaseDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CUserCaseDoc ���

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


// CUserCaseDoc ����


BOOL CUserCaseDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������
	InitAllWnd(TRUE);
	return TRUE;
}


void CUserCaseDoc::OnCloseDocument()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDocument::OnCloseDocument();
}
