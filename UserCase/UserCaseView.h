
// UserCaseView.h : CUserCaseView ��Ľӿ�
//

#pragma once
#include "MyObject.h"

class CUserCaseView : public CView
{
protected: // �������л�����
	CUserCaseView();
	DECLARE_DYNCREATE(CUserCaseView)

// ����
public:
	CUserCaseDoc* GetDocument() const;

// ����
public:
	CMyObject* m_selectedObj;
	CPoint m_pt;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CUserCaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAdd();
	HTREEITEM hRoot;     // ���ĸ��ڵ�ľ��   
	HTREEITEM hChildItem; // �ɱ�ʾ��һ����ڵ�ľ��
	HTREEITEM hChildItem2; // �ɱ�ʾ��һ����ڵ�ľ��

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

#ifndef _DEBUG  // UserCaseView.cpp �еĵ��԰汾
inline CUserCaseDoc* CUserCaseView::GetDocument() const
   { return reinterpret_cast<CUserCaseDoc*>(m_pDocument); }
#endif

