#pragma once
#include "MyObject.h"
#include <vector>
#include "iostream"
using namespace std;
// CObjectDraw ����Ŀ��

class CObjectDraw : public CObject
{
public:
	CObjectDraw();
	virtual ~CObjectDraw();
	DECLARE_SERIAL(CObjectDraw)

	CPen m_grayPen;
	CFont m_textFont;
	CBrush m_grayBrush;

	CObList m_objList;//������������
	CStringList m_logList;//�����־����
	BOOL m_drawMouseTip;
	CRectTracker m_rectTracker; //��Ƥ��
	void DrawRectTracker(CDC* pDC);//������Ƥ��

	void Draw(CDC* pDC, int cx, int cy, CPoint pt);
	void DrawUserCase(CDC* pDC, int cx, int cy);
	void DrawMouseTip(CDC* pDC, CPoint pt);

	void AddLog(CString cstr);
	CMyObject* GetSelectedObj(CPoint point);

	virtual void Serialize(CArchive& ar);
};


