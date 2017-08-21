// InnerDlg.cpp : ʵ���ļ�
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

// CInnerDlg �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IInnerDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {821EC038-D1C7-49C8-8C9C-60F9A83BF08D}
static const IID IID_IInnerDlg =
{ 0x821EC038, 0xD1C7, 0x49C8, { 0x8C, 0x9C, 0x60, 0xF9, 0xA8, 0x3B, 0xF0, 0x8D } };

BEGIN_INTERFACE_MAP(CInnerDlg, CDialogEx)
	INTERFACE_PART(CInnerDlg, IID_IInnerDlg, Dispatch)
END_INTERFACE_MAP()


// CInnerDlg ��Ϣ�������


BOOL CInnerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	DWORD dwOriginalStyle = m_tree.GetStyle();
	m_tree.ModifyStyle(m_tree.m_hWnd, dwOriginalStyle,
		dwOriginalStyle | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
void CInnerDlg::getDataFromTreeCtrlToDoc()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();
	//RemoveAllǰ����
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

	hRoot = m_tree.GetRootItem();//��ȡ���ڵ�
	if (hRoot != NULL)
	{
		str = m_tree.GetItemText(hRoot);
		obj->m_Actor.name = str;
		hChildItem = m_tree.GetChildItem(hRoot);//��ȡ�ӽڵ�
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

//���
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
		pDoc->m_ObjectDraw.AddLog(_T("���һ��Ԫ��"));
		pDoc->InitAllWnd(FALSE);
	}
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

//ɾ��
void CInnerDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

			pDoc->m_ObjectDraw.AddLog(_T("ɾ����һ��Ԫ��"));
			pDoc->InitAllWnd(FALSE);
			Invalidate(FALSE);
		}
	}
	else if (hRoot != NULL&&hChildItem != NULL && hNextItem == NULL && hPrevItem == NULL)
	{
		m_tree.DeleteItem(hRoot);
		getDataFromTreeCtrlToDoc();

		pDoc->m_ObjectDraw.AddLog(_T("ɾ����һ��Ԫ��"));
		pDoc->InitAllWnd(FALSE);
		Invalidate(FALSE);
	}
	else
	{
		MessageBox(_T("����ɾ�����"));
	}
}

//�޸�
void CInnerDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CUserCaseDoc* pDoc = (CUserCaseDoc*)pChildFrame->GetActiveDocument();

	HTREEITEM hItem, hChildItem;
	hItem = m_tree.GetSelectedItem();
	hChildItem = m_tree.GetChildItem(hItem);//��ȡ�ӽڵ�
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
			pDoc->m_ObjectDraw.AddLog(L"�༭ĳ��Ԫ��");
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
			pDoc->m_ObjectDraw.AddLog(L"�༭ĳ��Ԫ��");
			pDoc->InitAllWnd(FALSE);
		}
	}
}


void CInnerDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
