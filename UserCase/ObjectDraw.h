#pragma once
#include "MyObject.h"
#include <vector>
#include "iostream"
using namespace std;
// CObjectDraw 命令目标

class CObjectDraw : public CObject
{
public:
	CObjectDraw();
	virtual ~CObjectDraw();
	DECLARE_SERIAL(CObjectDraw)

	CPen m_grayPen;
	CFont m_textFont;
	CBrush m_grayBrush;

	CObList m_objList;//对象链表容器
	CStringList m_logList;//输出日志链表
	BOOL m_drawMouseTip;
	CRectTracker m_rectTracker; //橡皮筋
	void DrawRectTracker(CDC* pDC);//绘制橡皮筋

	void Draw(CDC* pDC, int cx, int cy, CPoint pt);
	void DrawUserCase(CDC* pDC, int cx, int cy);
	void DrawMouseTip(CDC* pDC, CPoint pt);

	void AddLog(CString cstr);
	CMyObject* GetSelectedObj(CPoint point);

	virtual void Serialize(CArchive& ar);
};


