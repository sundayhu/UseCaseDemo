#pragma once
#include "resource.h"
#include "afxwin.h"

// CChange �Ի���

class CChange : public CDialogEx
{
	DECLARE_DYNAMIC(CChange)

public:
	CChange(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChange();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CComboBox m_type;
	CString m_relation;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
};
