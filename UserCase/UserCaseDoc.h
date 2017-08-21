
// UserCaseDoc.h : CUserCaseDoc ��Ľӿ�
//


#pragma once
#include "ObjectDraw.h"

class CUserCaseDoc : public CDocument
{
protected: // �������л�����
	CUserCaseDoc();
	DECLARE_DYNCREATE(CUserCaseDoc)

// ����
public:

// ����
public:
	CObjectDraw m_ObjectDraw;

	void InitDockablePane();
	void InitTreeData();
	void InitOutputList();
	void InitAllWnd(BOOL bEraseLog = FALSE);
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CUserCaseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
};
