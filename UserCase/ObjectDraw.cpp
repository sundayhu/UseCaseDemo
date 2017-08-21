// ObjectDraw.cpp : 实现文件
//

#include "stdafx.h"
#include "UserCase.h"
#include "ObjectDraw.h"
#include "MainFrm.h"

// CObjectDraw
IMPLEMENT_SERIAL(CObjectDraw, CObject, 0)
CObjectDraw::CObjectDraw()
{
	m_grayBrush.CreateSolidBrush(RGB(192, 192, 192));
	m_grayPen.CreatePen(PS_SOLID, 1, RGB(192, 192, 192));//创建画笔
	m_textFont.CreateFontW(30, 0, 0, 0, FW_BOLD, 1, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Courier New"));

	m_drawMouseTip = TRUE;

	m_rectTracker.m_nStyle = CRectTracker::resizeInside | CRectTracker::dottedLine;
	m_rectTracker.m_nHandleSize = 5;
	m_rectTracker.m_rect = NULL;

}

CObjectDraw::~CObjectDraw()
{
	POSITION pos = m_objList.GetHeadPosition();
	while (pos)
	{
		CMyObject* obj = (CMyObject*)m_objList.GetNext(pos);
		delete obj;
	}
	m_objList.RemoveAll();
	m_logList.RemoveAll();

	m_grayBrush.DeleteObject();
	m_grayPen.DeleteObject();
	m_textFont.DeleteObject();
}


// CObjectDraw 成员函数

/************************************************************************/
/* 双缓冲                                                                */
/*pDC       DC句柄                                                       */
/*cx cy     view区域的长和宽                                               */
/*pt        当前的鼠标位置                                                 */
/*fDrawTip  是否绘制MouseTip                                              */
/************************************************************************/
void CObjectDraw::Draw(CDC* pDC, int cx, int cy, CPoint pt/*, BOOL fDrawTip*/)
{
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(pDC, cx, cy);
	memDC.SelectObject(&memBitmap);
	memDC.FillSolidRect(0, 0, cx, cy, RGB(255, 255, 255));
	DrawUserCase(&memDC,cx,cy);
	m_rectTracker.Draw(&memDC);//绘制橡皮筋
	//if (m_drawMouseTip)
	//	DrawMouseTip(&memDC, pt);


	pDC->BitBlt(0, 0, cx, cy, &memDC, 0, 0, SRCCOPY);

	memDC.DeleteDC();
	memBitmap.DeleteObject();
}


/************************************************************************/
/* 遍历每个对象，绘制                                                                     */
/************************************************************************/
void CObjectDraw::DrawUserCase(CDC* pDC,int cx,int cy)
{
	
	POSITION pos = m_objList.GetHeadPosition();
	int len = 0;
	while (pos)
	{
		CMyObject* obj = (CMyObject*)m_objList.GetNext(pos);
		len++;
	}
	int i = 0;
	int temp;
	if (len == 0)
	{
		temp = 0;
	}
	else
	{
		temp = cx / len;
	}
	pos = m_objList.GetHeadPosition();
	while (pos)
	{
		CMyObject* obj = (CMyObject*)m_objList.GetNext(pos);
		obj->m_x = temp*i;
		obj->m_y = 0;
		obj->m_w = temp;
		obj->m_h = cy;
		i++;
		obj->Draw(pDC,cx,cy);
	}
}
/************************************************************************/
/* 根据位置得到选择的对象                                                                    */
/************************************************************************/
CMyObject* CObjectDraw::GetSelectedObj(CPoint point)
{
	POSITION pos = m_objList.GetHeadPosition();
	while (pos)
	{
		CMyObject* obj = (CMyObject*)m_objList.GetNext(pos);
		if (obj->PtInRect(point))
		{
			return obj;
		}
	}
	return NULL;
}

/************************************************************************/
/* 添加输出                                                                     */
/************************************************************************/
void CObjectDraw::AddLog(CString cstr)
{
	CString Time = COleDateTime::GetCurrentTime().Format();
	m_logList.AddTail(Time + _T(" ") + cstr);
}


void CObjectDraw::Serialize(CArchive& ar)
{
	/*POSITION pos = m_objList.GetHeadPosition();
	while (pos)
	{
		CMyObject* obj = (CMyObject*)m_objList.GetNext(pos);
		obj->Serialize(ar);
	}*/
	m_objList.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


/************************************************************************/
/* 绘制跟随鼠标的信息                                                                     */
/************************************************************************/
void CObjectDraw::DrawMouseTip(CDC* pDC, CPoint pt)
{
	CMyObject* obj = GetSelectedObj(pt);
	if (obj == NULL) return;
	CFont* pOldFont = pDC->SelectObject(&m_textFont);
	CSize pSize = pDC->GetTextExtent(_T("X:1234"));
	CPoint pt0;
	pt0.x = pt.x;
	pt0.y = pt.y - 4 * pSize.cy;   //绘制的信息在鼠标右上角
	pDC->Rectangle(pt0.x, pt0.y, pt0.x + pSize.cx + 10, pt0.y + 4 * pSize.cy);
	pDC->TextOutW(pt0.x + 5, pt0.y, _T("用户:") + obj->m_Actor.name);
	/*pDC->TextOutW(pt0.x + 5, pt0.y + pSize.cy, _T("用例:") + CStringFormat(obj->m_y));
	pDC->TextOutW(pt0.x + 5, pt0.y + 2 * pSize.cy, _T("R:") + CStringFormat(obj->m_r));
	pDC->TextOutW(pt0.x + 5, pt0.y + 3 * pSize.cy, _T("Name:") + CStringFormat(obj->m_name));*/
	pDC->SelectObject(pOldFont);
}