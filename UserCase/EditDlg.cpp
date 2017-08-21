// EditDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UserCase.h"
#include "EditDlg.h"
#include "afxdialogex.h"


// CEditDlg �Ի���

IMPLEMENT_DYNAMIC(CEditDlg, CDialogEx)

CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditDlg::IDD, pParent)
	, m_Actor(_T(""))
	, m_Usercase(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();
	/*m_type.AddString(_T("����"));
	m_type.AddString(_T("�̳�"));
	m_type.AddString(_T("����"));
	m_type.AddString(_T("��չ"));*/
}

CEditDlg::~CEditDlg()
{
}

void CEditDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Actor);
	DDV_MaxChars(pDX, m_Actor, 20);
	DDX_Text(pDX, IDC_EDIT2, m_Usercase);
	DDV_MaxChars(pDX, m_Usercase, 20);
	DDX_Control(pDX, IDC_COMBO1, m_type);
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CEditDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CEditDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IEditDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {9DE6E76C-B46F-44C7-9E9E-221BF05D08FE}
static const IID IID_IEditDlg =
{ 0x9DE6E76C, 0xB46F, 0x44C7, { 0x9E, 0x9E, 0x22, 0x1B, 0xF0, 0x5D, 0x8, 0xFE } };

BEGIN_INTERFACE_MAP(CEditDlg, CDialogEx)
	INTERFACE_PART(CEditDlg, IID_IEditDlg, Dispatch)
END_INTERFACE_MAP()


// CEditDlg ��Ϣ�������


BOOL CEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_type.AddString(_T("����"));
	m_type.AddString(_T("�̳�"));
	m_type.AddString(_T("����"));
	m_type.AddString(_T("��չ"));
	//m_type.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CEditDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_type.GetLBText(m_type.GetCurSel(), m_relation);
}
