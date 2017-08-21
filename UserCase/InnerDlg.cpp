// InnerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UserCase.h"
#include "InnerDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "UserCaseDoc.h"
#include "EditDlg.h"
#include "Change.h"
#include "ChangeDlg.h"
#include "ConfirmDlg.h"
#include "MyObject.h"

// CInnerDlg 对话框

IMPLEMENT_DYNAMIC(CInnerDlg, CDialogEx)

CInnerDlg::CInnerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInnerDlg::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CInnerDlg::~CInnerDlg()
{
}

void CInnerDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CInnerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}


BEGIN_MESSAGE_MAP(CInnerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CInnerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInnerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CInnerDlg::OnBnClickedButton3)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CInnerDlg::OnTvnSelchangedTree1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CInnerDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IInnerDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {821EC038-D1C7-49C8-8C9C-60F9A83BF08D}
static const IID IID_IInnerDlg =
{ 0x821EC038, 0xD1C7, 0x49C8, { 0x8C, 0x9C, 0x60, 0xF9, 0xA8, 0x3B, 0xF0, 0x8D } };

BEGIN_INTERFACE_MAP(CInnerDlg, CDialogEx)
	INTERFACE_PART(CInnerDlg, IID_IInnerDlg, Dispatch)
END_INTERFACE_MAP()


// CInnerDlg 消息处理程序


BOOL CInnerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD dwOriginalStyle = m_tree.GetStyle();
	m_tree.ModifyStyle(m_tree.m_hWnd, dwOriginalStyle,
		dwOriginalStyle | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
void CInnerDlg::getDataFromTreeCtrlToDoc()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();
	//RemoveAll前清理
	POSITION pos = pDoc->m_ObjectDraw.m_objList.GetHeadPosition();
	while (pos)
	{
		CMyObject* obj = (CMyObject*)pDoc->m_ObjectDraw.m_objList.GetNext(pos);
		delete obj;
		obj = NULL;
	}

	pDoc->m_ObjectDraw.m_objList.RemoveAll();

	CString str;
	CMyObject* obj = new CMyObject();
	Usercase usecase;

	hRoot = m_tree.GetRootItem();//获取根节点
	if (hRoot != NULL)
	{
		str = m_tree.GetItemText(hRoot);
		obj->m_Actor.name = str;
		hChildItem = m_tree.GetChildItem(hRoot);//获取子节点
		if (hChildItem != NULL)
		{
			str = m_tree.GetItemText(hChildItem);
			usecase.name = str;

			hChildItem2 = m_tree.GetChildItem(hChildItem);
			str = m_tree.GetItemText(hChildItem2);
			usecase.type = str;
			obj->m_Actor.m_Usercase.push_back(usecase);

			hChildItem = m_tree.GetNextSiblingItem(hChildItem);
			while (hChildItem != NULL)
			{
				Usercase usecase;
				str = m_tree.GetItemText(hChildItem);
				usecase.name = str;
				hChildItem2 = m_tree.GetChildItem(hChildItem);
				str = m_tree.GetItemText(hChildItem2);
				usecase.type = str;
				obj->m_Actor.m_Usercase.push_back(usecase);
				hChildItem = m_tree.GetNextSiblingItem(hChildItem);
			}
		}
		pDoc->m_ObjectDraw.m_objList.AddTail(obj);

		hRoot = m_tree.GetNextSiblingItem(hRoot);
		while (hRoot != NULL)
		{
			CMyObject* obj = new CMyObject();
			Usercase usecase;
			obj->m_Actor.name = "";
			obj->m_Actor.m_Usercase.clear();

			str = m_tree.GetItemText(hRoot);
			obj->m_Actor.name = str;
			hChildItem = m_tree.GetChildItem(hRoot);
			if (hChildItem != NULL)
			{
				str = m_tree.GetItemText(hChildItem);
				usecase.name = str;
				hChildItem2 = m_tree.GetChildItem(hChildItem);
				str = m_tree.GetItemText(hChildItem2);
				usecase.type = str;
				obj->m_Actor.m_Usercase.push_back(usecase);
				hChildItem = m_tree.GetNextSiblingItem(hChildItem);
				while (hChildItem != NULL)
				{
					Usercase usecase;
					str = m_tree.GetItemText(hChildItem);
					usecase.name = str;
					hChildItem2 = m_tree.GetChildItem(hChildItem);
					str = m_tree.GetItemText(hChildItem2);
					usecase.type = str;
					obj->m_Actor.m_Usercase.push_back(usecase);
					hChildItem = m_tree.GetNextSiblingItem(hChildItem);
				}
			}
			pDoc->m_ObjectDraw.m_objList.AddTail(obj);
			hRoot = m_tree.GetNextSiblingItem(hRoot);
		}
	}
}

//添加
void CInnerDlg::OnBnClickedButton1()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();
	
	CEditDlg pDlg;
	CString str1, str2, str3;
	bool flag = false, flag1 = false;
	if (pDlg.DoModal() == IDOK)
	{
		str1 = pDlg.m_Actor;
		str2 = pDlg.m_Usercase;
		str3 = pDlg.m_relation;
		POSITION pos = pDoc->m_ObjectDraw.m_objList.GetHeadPosition();
		while (pos)
		{
			CMyObject* obj = (CMyObject*)pDoc->m_ObjectDraw.m_objList.GetNext(pos);
			if (obj->m_Actor.name == str1)
			{
				flag = true;
				for (vector<Usercase>::iterator it = obj->m_Actor.m_Usercase.begin(); it != obj->m_Actor.m_Usercase.end(); it++)
				{
					if (it->name == str2&&it->type == str3)
					{
						flag1 = true;
						break;
					}
				}
				if (flag1 == false)
				{
					Usercase uc;
					uc.name = str2;
					uc.type = str3;
					obj->m_Actor.m_Usercase.push_back(uc);
				}
				break;
			}
		}
		if (flag == false)
		{
			CMyObject* obj = new CMyObject();
			obj->m_Actor.name = str1;
			Usercase uc;
			uc.name = str2;
			uc.type = str3;
			obj->m_Actor.m_Usercase.push_back(uc);
			pDoc->m_ObjectDraw.m_objList.AddTail(obj);
		}

		pChildFrame->GetActiveView()->Invalidate(FALSE);
		pDoc->m_ObjectDraw.AddLog(_T("添加一个元素"));
		pDoc->InitAllWnd(FALSE);
	}
	
	// TODO:  在此添加控件通知处理程序代码
}

//删除
void CInnerDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();
	HTREEITEM hItem, hNextItem, hPrevItem,hChildItem, hRoot;
	hItem = m_tree.GetSelectedItem();
	hRoot = m_tree.GetParentItem(hItem);
	hPrevItem = m_tree.GetPrevSiblingItem(hItem);
	hNextItem = m_tree.GetNextSiblingItem(hItem);
	hChildItem = m_tree.GetChildItem(hItem);
	if ((hRoot == NULL) || (hRoot != NULL&&hChildItem != NULL && (hNextItem != NULL || hPrevItem != NULL)))
	{
		CConfirmDlg pDlg;
		if (pDlg.DoModal() == IDOK)
		{
			m_tree.DeleteItem(hItem);
			getDataFromTreeCtrlToDoc();

			pDoc->m_ObjectDraw.AddLog(_T("删除了一个元素"));
			pDoc->InitAllWnd(FALSE);
			Invalidate(FALSE);
		}
	}
	else if (hRoot != NULL&&hChildItem != NULL && hNextItem == NULL && hPrevItem == NULL)
	{
		m_tree.DeleteItem(hRoot);
		getDataFromTreeCtrlToDoc();

		pDoc->m_ObjectDraw.AddLog(_T("删除了一个元素"));
		pDoc->InitAllWnd(FALSE);
		Invalidate(FALSE);
	}
	else
	{
		MessageBox(_T("不能删除此项！"));
	}
}

//修改
void CInnerDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();

	HTREEITEM hItem, hChildItem;
	hItem = m_tree.GetSelectedItem();
	hChildItem = m_tree.GetChildItem(hItem);//获取子节点
	if (hChildItem != NULL)
	{
		CChangeDlg pDlg;
		CString str;
		if (pDlg.DoModal() == IDOK)
		{
			str = pDlg.m_change;
			m_tree.SetItemText(hItem, str);

			getDataFromTreeCtrlToDoc();
			pChildFrame->GetActiveView()->Invalidate(TRUE);
			pDoc->m_ObjectDraw.AddLog(L"编辑某个元素");
			pDoc->InitAllWnd(FALSE);
		}
	}
	else
	{
		CChange pDlg;
		CString str;
		if (pDlg.DoModal() == IDOK)
		{
			str = pDlg.m_relation;
			m_tree.SetItemText(hItem, str);

			getDataFromTreeCtrlToDoc();
			pChildFrame->GetActiveView()->Invalidate(TRUE);
			pDoc->m_ObjectDraw.AddLog(L"编辑某个元素");
			pDoc->InitAllWnd(FALSE);
		}
	}
}


void CInnerDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();

	//if (pNMTreeView->action < 0) return;

	//POSITION pos = pDoc->m_ObjectDraw.m_objList.FindIndex(pNMTreeView->action);
	//CMyObject* obj = (CMyObject*)pDoc->m_ObjectDraw.m_objList.GetAt(pos);
	HTREEITEM hItem = m_tree.GetSelectedItem();
	CString str = m_tree.GetItemText(hItem);
	
	pMainFrame->GetPropertiesWnd()->SetProperties(str);
	*pResult = 0;
}
