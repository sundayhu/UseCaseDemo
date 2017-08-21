#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

// CInnerDlg �Ի���

class CInnerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInnerDlg)

public:
	CInnerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInnerDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTreeCtrl m_tree;
	HTREEITEM hRoot;     // ���ĸ��ڵ�ľ��   
	HTREEITEM hChildItem; // �ɱ�ʾ��һ����ڵ�ľ��
	HTREEITEM hChildItem2; // �ɱ�ʾ��һ����ڵ�ľ��

	void getDataFromTreeCtrlToDoc();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
