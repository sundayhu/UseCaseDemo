#pragma once
#include "resource.h"
#include "afxwin.h"


// CEditDlg �Ի���

class CEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDlg)

public:
	CEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString m_Actor;
	CString m_Usercase;
	CComboBox m_type;
	CString m_relation;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
};
