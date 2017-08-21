
// UserCaseView.cpp : CUserCaseView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "UserCase.h"
#endif

#include "UserCaseDoc.h"
#include "UserCaseView.h"


#include "MainFrm.h"
#include "ChildFrm.h"
#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUserCaseView

IMPLEMENT_DYNCREATE(CUserCaseView, CView)

BEGIN_MESSAGE_MAP(CUserCaseView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CUserCaseView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ADD, &CUserCaseView::OnAdd)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

// CUserCaseView ����/����

CUserCaseView::CUserCaseView()
{
	// TODO:  �ڴ˴���ӹ������
}

CUserCaseView::~CUserCaseView()
{
}

BOOL CUserCaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CUserCaseView ����

void CUserCaseView::OnDraw(CDC* pDC)
{
	CUserCaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect rect;
	GetClientRect(&rect);

	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);

	pDoc->m_ObjectDraw.Draw(pDC, rect.Width(), rect.Height(), pt/*, rect.PtInRect(pt)*/);
}


// CUserCaseView ��ӡ


void CUserCaseView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CUserCaseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CUserCaseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CUserCaseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CUserCaseView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	m_pt.x = point.x;
	m_pt.y = point.y;
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CUserCaseView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CUserCaseView ���

#ifdef _DEBUG
void CUserCaseView::AssertValid() const
{
	CView::AssertValid();
}

void CUserCaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUserCaseDoc* CUserCaseView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUserCaseDoc)));
	return (CUserCaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CUserCaseView ��Ϣ�������
void CUserCaseView::OnAdd()
{
	// TODO:  �ڴ���������������
	CEditDlg pDlg;
	CString str1, str2, str3;
	bool flag = false, flag1 = false;
	if (pDlg.DoModal() == IDOK)
	{
		str1 = pDlg.m_Actor;
		str2 = pDlg.m_Usercase;
		str3 = pDlg.m_relation;
		POSITION pos = GetDocument()->m_ObjectDraw.m_objList.GetHeadPosition();
		while (pos)
		{
			CMyObject* obj = (CMyObject*)GetDocument()->m_ObjectDraw.m_objList.GetNext(pos);
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
			GetDocument()->m_ObjectDraw.m_objList.AddTail(obj);
		}
		
		GetDocument()->m_ObjectDraw.AddLog(_T("���һ��Ԫ��"));
		GetDocument()->InitAllWnd(FALSE);
		Invalidate(FALSE);
	}
}


void CUserCaseView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonDblClk(nFlags, point);
}


void CUserCaseView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CUserCaseDoc* pDoc = GetDocument();

	if (!pDoc->m_ObjectDraw.m_rectTracker.m_rect.PtInRect(point))//������ھ��η�Χ��
	{
		CMyObject* obj = GetDocument()->m_ObjectDraw.GetSelectedObj(point);
		if (obj == NULL)//���� ����λ��û������
		{
			pDoc->m_ObjectDraw.m_rectTracker.m_rect.SetRect(0, 0, 0, 0);//������Ƥ�� 
			pDoc->m_ObjectDraw.m_drawMouseTip = TRUE;
			m_selectedObj = NULL;
			return;
		}
		else//���򣬸ı�ѡ�������
		{
			m_selectedObj = obj;
			pDoc->m_ObjectDraw.m_drawMouseTip = FALSE;
		}
	}
	//��ʾ����
	/*CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetPropertiesWnd()->SetProperties(m_selectedObj);*/
	//��Ƥ��ķ�ΧΪ���ݵľ��η�Χ
	pDoc->m_ObjectDraw.m_rectTracker.m_rect.CopyRect(m_selectedObj->GetRect());
	pDoc->m_ObjectDraw.m_rectTracker.m_rect.NormalizeRect();

	if (pDoc->m_ObjectDraw.m_rectTracker.HitTest(point) > 0)
	{
		//�ƶ�������
		pDoc->m_ObjectDraw.m_rectTracker.Track(this, point, TRUE);
		pDoc->m_ObjectDraw.m_rectTracker.m_rect.NormalizeRect();
		//�ı���������
		m_selectedObj->SetRect(pDoc->m_ObjectDraw.m_rectTracker.m_rect);
		pDoc->m_ObjectDraw.m_rectTracker.m_rect.CopyRect(m_selectedObj->GetRect());
	}

	pDoc->InitAllWnd(FALSE);
	Invalidate(FALSE);

	CView::OnLButtonDown(nFlags, point);
}


BOOL CUserCaseView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ScreenToClient(&pt);
	if (nFlags == MK_CONTROL)//Ctrl������
	{
		if (zDelta > 0)//���Ϲ���
		{
			if (m_selectedObj != NULL)
			{
				if (m_selectedObj->GetRect().PtInRect(pt))
				{
					m_selectedObj->m_w += 5;
					m_selectedObj->m_h += 5;
				}
			}
		}
		else//���¹���
		{
			if (m_selectedObj != NULL)
			{
				if (m_selectedObj->GetRect().PtInRect(pt))
				{
					m_selectedObj->m_w -= 5;
					if (m_selectedObj->m_w < 30)//��Сֵ30
					{
						m_selectedObj->m_w = 30;
					}
					m_selectedObj->m_h -= 5;
					if (m_selectedObj->m_h < 30)//��Сֵ30
					{
						m_selectedObj->m_h = 30;
					}
				}
			}
		}
	}

	//��Ƥ��ķ�ΧΪ���ݵľ��η�Χ
	GetDocument()->m_ObjectDraw.m_rectTracker.m_rect.CopyRect(m_selectedObj->GetRect());
	GetDocument()->m_ObjectDraw.m_rectTracker.m_rect.NormalizeRect();

	GetDocument()->InitAllWnd(FALSE);
	Invalidate(FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CUserCaseView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}


BOOL CUserCaseView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ((pWnd == this) && (GetDocument()->m_ObjectDraw.m_rectTracker.SetCursor(this, nHitTest)))
	{
		return TRUE;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}
