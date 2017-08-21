#include <vector>
#include "iostream"
using namespace std;

#pragma once

struct Usercase
{
	CString name;//用例名
	CString type;//关系
};
struct Actor
{
	CString name;//参与者名
	vector<Usercase> m_Usercase;//用例
};
// CMyObject 命令目标

class CMyObject : public CObject
{
public:
	CMyObject();
	virtual ~CMyObject();
	DECLARE_SERIAL(CMyObject)

	Actor m_Actor;
	int m_x;//起点x
	int m_y;//起点y
	int m_w;//宽
	int m_h;//高
	int m_len;//用例个数

	void Draw(CDC* cdc, int cx, int cy);
	void DrawJ(CDC* cdc, int Start_x, int Start_y, int End_x, int End_y);
	void DrawSJ(CDC* cdc, int Start_x, int Start_y, int End_x, int End_y);
	void DrawXline(CDC* cdc, int Start_x, int Start_y, int End_x, int End_y);
	void DrawTLine(CDC* cdc, int Start_x, int Start_y, int End_x, int End_y, CString str);

	BOOL PtInRect(CPoint pt);
	CRect GetRect();
	void SetRect(CRect rect);
	virtual void Serialize(CArchive& ar);
};


