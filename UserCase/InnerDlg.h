#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

// CInnerDlg 对话框

class CInnerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInnerDlg)

public:
	CInnerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInnerDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTreeCtrl m_tree;
	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hChildItem; // 可表示任一分类节点的句柄
	HTREEITEM hChildItem2; // 可表示任一分类节点的句柄

	void getDataFromTreeCtrlToDoc();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
