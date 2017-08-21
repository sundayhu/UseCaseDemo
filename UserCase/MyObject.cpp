// MyObject.cpp : 实现文件
//

#include "stdafx.h"
#include "UserCase.h"
#include "MyObject.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "UserCaseDoc.h"

#include<gdiplus.h>
using namespace Gdiplus;
#include "iostream"
using namespace std;
const double PI = 3.1415926;
// CMyObject
IMPLEMENT_SERIAL(CMyObject, CObject, 0)
CMyObject::CMyObject()
{
}

CMyObject::~CMyObject()
{
}


// CMyObject 成员函数
void CMyObject::Draw(CDC* cdc, int cx, int cy)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();
	
	int rectheight = cy;
	int rectwidth = cx;

	Graphics graphics(cdc->GetSafeHdc());//获取pDC的输出上下文

	CPoint p[4];
	CBrush brs[11] = { { RGB(255, 128, 0) }, { RGB(148, 0, 211) }, { RGB(30, 144, 255) }, { RGB(46, 139, 87) }, { RGB(255, 255, 0) }, { RGB(105, 105, 105) }, { RGB(255, 0, 0) }, { RGB(0, 255, 0) }, { RGB(0, 0, 255) },
	{ RGB(0, 255, 255) }, { RGB(255, 105, 180) } };
	CBrush br = RGB(255, 192, 203);
	SolidBrush black(Color(0, 0, 0));
	Graphics gdiplusObject(cdc->m_hDC);

	int act_w = m_w/4;
	int act_h = m_h / 10;
	int act_x = 0;
	int act_y = 0;
	int temp = m_w;
	int tempy = 0;
	int x = 0, y = 0;
	act_x = m_x;
	act_y = m_h / 3;
	cdc->SelectObject(&br);
	cdc->Ellipse(act_x, act_y, act_x + act_w, act_y + act_h);

	cdc->MoveTo(act_x, act_y + 2 * act_h);
	cdc->LineTo(act_x + act_w, act_y + 2 * act_h);

	cdc->MoveTo(act_x + act_w / 2, act_y + act_h);
	cdc->LineTo(act_x + act_w / 2, act_y + 2 * act_h);

	cdc->MoveTo(act_x + act_w / 2, act_y + 2 * act_h);
	cdc->LineTo(act_x, act_y + 3 * act_h);

	cdc->MoveTo(act_x + act_w / 2, act_y + 2 * act_h);
	cdc->LineTo(act_x + act_w, act_y + 3 * act_h);

	cdc->TextOutW(act_x, act_y + 3 * act_h, m_Actor.name);
	tempy = m_h / (m_Actor.m_Usercase.size() + 1);
	for (int j = 0; j < m_Actor.m_Usercase.size(); j++)
	{
		x = m_x + temp / 2;
		y = tempy*(j + 1) - 20;

		cdc->SelectObject(&brs[j]);
		cdc->Ellipse(x, y, x + temp / 3, y + tempy / 4);

		if (m_Actor.m_Usercase[j].type == "关联")
		{
				//关联
				//实线
			cdc->MoveTo(act_x + act_w, act_y + act_h / 2);
			cdc->LineTo(x, y + 10);
				//空箭头
			DrawJ(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
		}
		else if (m_Actor.m_Usercase[j].type == "包含")
		{
				//包含
			DrawTLine(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10, _T("<include>"));
				//虚线
			DrawXline(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
				//空箭头
			DrawJ(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
		}
		else if (m_Actor.m_Usercase[j].type == "扩展")
		{
				//扩展
			DrawTLine(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10, _T("<extend>"));
				//虚线
			DrawXline(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
				//空箭头
			DrawJ(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
		}
		else if (m_Actor.m_Usercase[j].type == "继承")
		{
				//继承
				//实线
			cdc->MoveTo(act_x + act_w, act_y + act_h / 2);
			cdc->LineTo(x, y + 10);
				//闭合箭头
			DrawSJ(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
		}
		cdc->TextOutW(x + 10, y + tempy / 4, m_Actor.m_Usercase[j].name);
			
	}
}
//箭头
void CMyObject::DrawJ(CDC* cdc, int Start_x, int Start_y, int End_x, int End_y)
{
	double t = PI / 4;    //箭头与直线夹角
	double l = 0.2;     //箭头边长度占直线长度的百分比
	int px = 0, py = 0;

	px = (int)(l*((Start_x - End_x)*cos(t) - (Start_y - End_y)*sin(t)) + End_x);
	py = (int)(l*((Start_x - End_x)*sin(t) + (Start_y - End_y)*cos(t)) + End_y);
	cdc->MoveTo(px, py);
	cdc->LineTo(End_x, End_y);

	px = (int)(l*((Start_x - End_x)*cos(-t) - (Start_y - End_y)*sin(-t)) + End_x);
	py = (int)(l*((Start_x - End_x)*sin(-t) + (Start_y - End_y)*cos(-t)) + End_y);
	cdc->MoveTo(px, py);
	cdc->LineTo(End_x, End_y);
}
//闭合箭头
void CMyObject::DrawSJ(CDC* cdc, int Start_x, int Start_y, int End_x, int End_y)
{
	double t = PI / 4;    //箭头与直线夹角
	double l = 0.2;     //箭头边长度占直线长度的百分比
	int px1 = 0, py1 = 0;
	int px2 = 0, py2 = 0;
	px1 = (int)(l*((Start_x - End_x)*cos(t) - (Start_y - End_y)*sin(t)) + End_x);
	py1 = (int)(l*((Start_x - End_x)*sin(t) + (Start_y - End_y)*cos(t)) + End_y);
	cdc->MoveTo(px1, py1);
	cdc->LineTo(End_x, End_y);

	px2 = (int)(l*((Start_x - End_x)*cos(-t) - (Start_y - End_y)*sin(-t)) + End_x);
	py2 = (int)(l*((Start_x - End_x)*sin(-t) + (Start_y - End_y)*cos(-t)) + End_y);
	cdc->MoveTo(px2, py2);
	cdc->LineTo(End_x, End_y);

	cdc->MoveTo(px1, py1);
	cdc->LineTo(px2, py2);
}
//虚线
void CMyObject::DrawXline(CDC* cdc, int Start_x, int Start_y, int End_x, int End_y)
{
	int px1 = 0, py1 = 0;
	int px2 = 0, py2 = 0;
	double angle = (End_y - Start_y) / (End_x - Start_x);
	int tempx = (End_x - Start_x) / 10;
	int tempy = (End_y - Start_y) / 10;
	for (int i = 0; i < 9; i++)
	{
		px1 = Start_x + tempx*i;
		py1 = Start_y + tempy*i;
		i++;
		px2 = Start_x + tempx*i;
		py2 = Start_y + tempy*i;
		cdc->MoveTo(px1, py1);
		cdc->LineTo(px2, py2);
	}
}
//线上的字
void CMyObject::DrawTLine(CDC* cdc, int Start_x, int Start_y, int End_x, int End_y, CString str)
{
	int px1 = 0, py1 = 0;
	int px2 = 0, py2 = 0;
	int tempx = (End_x - Start_x) / 3;
	int tempy = (End_y - Start_y) / 3;
	px1 = Start_x + tempx;
	py1 = Start_y + tempy;
	px2 = Start_x + 2 * tempx;
	py2 = Start_y + 2 * tempy;

	cdc->TextOutW(px1, py1, str);
}
//序列化
void CMyObject::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		m_len = m_Actor.m_Usercase.size();
		ar << m_Actor.name << m_len << m_x << m_y << m_w << m_h;
		for (int i = 0; i < m_len; i++)
		{
			ar << m_Actor.m_Usercase[i].name << m_Actor.m_Usercase[i].type;
		}
	}
	else
	{	// loading code
		Actor ac;
		ar >> ac.name >> m_len >> m_x >> m_y >> m_w >> m_h;
		for (int i = 0; i < m_len; i++)
		{
			Usercase uc;
			ar >> uc.name >> uc.type;
			ac.m_Usercase.push_back(uc);
		}
		m_Actor = ac;
	}
}
//判断点是否在矩形框内
BOOL CMyObject::PtInRect(CPoint pt)
{
	if (pt.x > m_x&&pt.x<(m_x + m_w) && pt.y>m_y&&pt.y < (m_y + m_h))
		return true;
	else
		return false;
}
//获取用例的矩形
CRect CMyObject::GetRect()
{
	CRect rt(m_x, m_y, m_x + m_w, m_y + m_h);
	return rt;
}
//重新设置属性
void CMyObject::SetRect(CRect rect)
{
	CPoint p1, p2;
	p1 = rect.TopLeft();
	p2 = rect.BottomRight();
	m_x =p1.x;
	m_y = p1.y;
	m_w = p2.x - p1.x;
	m_h = p2.y - p1.y;
}