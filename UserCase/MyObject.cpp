// MyObject.cpp : ʵ���ļ�
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


// CMyObject ��Ա����
void CMyObject::Draw(CDC* cdc, int cx, int cy)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();
	
	int rectheight = cy;
	int rectwidth = cx;

	Graphics graphics(cdc->GetSafeHdc());//��ȡpDC�����������

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

		if (m_Actor.m_Usercase[j].type == "����")
		{
				//����
				//ʵ��
			cdc->MoveTo(act_x + act_w, act_y + act_h / 2);
			cdc->LineTo(x, y + 10);
				//�ռ�ͷ
			DrawJ(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
		}
		else if (m_Actor.m_Usercase[j].type == "����")
		{
				//����
			DrawTLine(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10, _T("<include>"));
				//����
			DrawXline(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
				//�ռ�ͷ
			DrawJ(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
		}
		else if (m_Actor.m_Usercase[j].type == "��չ")
		{
				//��չ
			DrawTLine(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10, _T("<extend>"));
				//����
			DrawXline(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
				//�ռ�ͷ
			DrawJ(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
		}
		else if (m_Actor.m_Usercase[j].type == "�̳�")
		{
				//�̳�
				//ʵ��
			cdc->MoveTo(act_x + act_w, act_y + act_h / 2);
			cdc->LineTo(x, y + 10);
				//�պϼ�ͷ
			DrawSJ(cdc, act_x + act_w, act_y + act_h / 2, x, y + 10);
		}
		cdc->TextOutW(x + 10, y + tempy / 4, m_Actor.m_Usercase[j].name);
			
	}
}
//��ͷ
void CMyObject::DrawJ(CDC* cdc, int Start_x, int Start_y, int End_x, int End_y)
{
	double t = PI / 4;    //��ͷ��ֱ�߼н�
	double l = 0.2;     //��ͷ�߳���ռֱ�߳��ȵİٷֱ�
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
//�պϼ�ͷ
void CMyObject::DrawSJ(CDC* cdc, int Start_x, int Start_y, int End_x, int End_y)
{
	double t = PI / 4;    //��ͷ��ֱ�߼н�
	double l = 0.2;     //��ͷ�߳���ռֱ�߳��ȵİٷֱ�
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
//����
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
//���ϵ���
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
//���л�
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
//�жϵ��Ƿ��ھ��ο���
BOOL CMyObject::PtInRect(CPoint pt)
{
	if (pt.x > m_x&&pt.x<(m_x + m_w) && pt.y>m_y&&pt.y < (m_y + m_h))
		return true;
	else
		return false;
}
//��ȡ�����ľ���
CRect CMyObject::GetRect()
{
	CRect rt(m_x, m_y, m_x + m_w, m_y + m_h);
	return rt;
}
//������������
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