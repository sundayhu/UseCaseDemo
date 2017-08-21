
// UserCaseView.h : CUserCaseView 类的接口
//

#pragma once
#include "MyObject.h"

class CUserCaseView : public CView
{
protected: // 仅从序列化创建
	CUserCaseView();
	DECLARE_DYNCREATE(CUserCaseView)

// 特性
public:
	CUserCaseDoc* GetDocument() const;

// 操作
public:
	CMyObject* m_selectedObj;
	CPoint m_pt;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CUserCaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAdd();
	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hChildItem; // 可表示任一分类节点的句柄
	HTREEITEM hChildItem2; // 可表示任一分类节点的句柄

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

#ifndef _DEBUG  // UserCaseView.cpp 中的调试版本
inline CUserCaseDoc* CUserCaseView::GetDocument() const
   { return reinterpret_cast<CUserCaseDoc*>(m_pDocument); }
#endif

