#pragma once
#include "resource.h"
#include "afxwin.h"

// CChange 对话框

class CChange : public CDialogEx
{
	DECLARE_DYNAMIC(CChange)

public:
	CChange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChange();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CComboBox m_type;
	CString m_relation;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
};
