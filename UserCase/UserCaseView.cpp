
// UserCaseView.cpp : CUserCaseView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CUserCaseView 构造/析构

CUserCaseView::CUserCaseView()
{
	// TODO:  在此处添加构造代码
}

CUserCaseView::~CUserCaseView()
{
}

BOOL CUserCaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CUserCaseView 绘制

void CUserCaseView::OnDraw(CDC* pDC)
{
	CUserCaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	CRect rect;
	GetClientRect(&rect);

	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);

	pDoc->m_ObjectDraw.Draw(pDC, rect.Width(), rect.Height(), pt/*, rect.PtInRect(pt)*/);
}


// CUserCaseView 打印


void CUserCaseView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CUserCaseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CUserCaseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CUserCaseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
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


// CUserCaseView 诊断

#ifdef _DEBUG
void CUserCaseView::AssertValid() const
{
	CView::AssertValid();
}

void CUserCaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUserCaseDoc* CUserCaseView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUserCaseDoc)));
	return (CUserCaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CUserCaseView 消息处理程序
void CUserCaseView::OnAdd()
{
	// TODO:  在此添加命令处理程序代码
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
		
		GetDocument()->m_ObjectDraw.AddLog(_T("添加一个元素"));
		GetDocument()->InitAllWnd(FALSE);
		Invalidate(FALSE);
	}
}


void CUserCaseView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDblClk(nFlags, point);
}


void CUserCaseView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CUserCaseDoc* pDoc = GetDocument();

	if (!pDoc->m_ObjectDraw.m_rectTracker.m_rect.PtInRect(point))//如果不在矩形范围内
	{
		CMyObject* obj = GetDocument()->m_ObjectDraw.GetSelectedObj(point);
		if (obj == NULL)//并且 所在位置没有气泡
		{
			pDoc->m_ObjectDraw.m_rectTracker.m_rect.SetRect(0, 0, 0, 0);//隐藏橡皮筋 
			pDoc->m_ObjectDraw.m_drawMouseTip = TRUE;
			m_selectedObj = NULL;
			return;
		}
		else//否则，改变选择的气泡
		{
			m_selectedObj = obj;
			pDoc->m_ObjectDraw.m_drawMouseTip = FALSE;
		}
	}
	//显示属性
	/*CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetPropertiesWnd()->SetProperties(m_selectedObj);*/
	//橡皮筋的范围为气泡的矩形范围
	pDoc->m_ObjectDraw.m_rectTracker.m_rect.CopyRect(m_selectedObj->GetRect());
	pDoc->m_ObjectDraw.m_rectTracker.m_rect.NormalizeRect();

	if (pDoc->m_ObjectDraw.m_rectTracker.HitTest(point) > 0)
	{
		//移动或缩放
		pDoc->m_ObjectDraw.m_rectTracker.Track(this, point, TRUE);
		pDoc->m_ObjectDraw.m_rectTracker.m_rect.NormalizeRect();
		//改变气泡属性
		m_selectedObj->SetRect(pDoc->m_ObjectDraw.m_rectTracker.m_rect);
		pDoc->m_ObjectDraw.m_rectTracker.m_rect.CopyRect(m_selectedObj->GetRect());
	}

	pDoc->InitAllWnd(FALSE);
	Invalidate(FALSE);

	CView::OnLButtonDown(nFlags, point);
}


BOOL CUserCaseView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	ScreenToClient(&pt);
	if (nFlags == MK_CONTROL)//Ctrl键按下
	{
		if (zDelta > 0)//向上滚动
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
		else//向下滚动
		{
			if (m_selectedObj != NULL)
			{
				if (m_selectedObj->GetRect().PtInRect(pt))
				{
					m_selectedObj->m_w -= 5;
					if (m_selectedObj->m_w < 30)//最小值30
					{
						m_selectedObj->m_w = 30;
					}
					m_selectedObj->m_h -= 5;
					if (m_selectedObj->m_h < 30)//最小值30
					{
						m_selectedObj->m_h = 30;
					}
				}
			}
		}
	}

	//橡皮筋的范围为气泡的矩形范围
	GetDocument()->m_ObjectDraw.m_rectTracker.m_rect.CopyRect(m_selectedObj->GetRect());
	GetDocument()->m_ObjectDraw.m_rectTracker.m_rect.NormalizeRect();

	GetDocument()->InitAllWnd(FALSE);
	Invalidate(FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CUserCaseView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}


BOOL CUserCaseView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if ((pWnd == this) && (GetDocument()->m_ObjectDraw.m_rectTracker.SetCursor(this, nHitTest)))
	{
		return TRUE;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}
