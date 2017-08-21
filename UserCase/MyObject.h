#include <vector>
#include "iostream"
using namespace std;

#pragma once

struct Usercase
{
	CString name;//������
	CString type;//��ϵ
};
struct Actor
{
	CString name;//��������
	vector<Usercase> m_Usercase;//����
};
// CMyObject ����Ŀ��

class CMyObject : public CObject
{
public:
	CMyObject();
	virtual ~CMyObject();
	DECLARE_SERIAL(CMyObject)

	Actor m_Actor;
	int m_x;//���x
	int m_y;//���y
	int m_w;//��
	int m_h;//��
	int m_len;//��������

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


