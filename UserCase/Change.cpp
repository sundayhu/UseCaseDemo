// Change.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UserCase.h"
#include "Change.h"
#include "afxdialogex.h"


// CChange �Ի���

IMPLEMENT_DYNAMIC(CChange, CDialogEx)

CChange::CChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChange::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CChange::~CChange()
{
}

void CChange::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_type);
}


BEGIN_MESSAGE_MAP(CChange, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CChange::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CChange, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IChange ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {CDD48358-0FE2-4789-BD56-465D8BF29C3F}
static const IID IID_IChange =
{ 0xCDD48358, 0xFE2, 0x4789, { 0xBD, 0x56, 0x46, 0x5D, 0x8B, 0xF2, 0x9C, 0x3F } };

BEGIN_INTERFACE_MAP(CChange, CDialogEx)
	INTERFACE_PART(CChange, IID_IChange, Dispatch)
END_INTERFACE_MAP()


// CChange ��Ϣ�������


BOOL CChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_type.AddString(_T("����"));
	m_type.AddString(_T("�̳�"));
	m_type.AddString(_T("����"));
	m_type.AddString(_T("��չ"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CChange::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_type.GetLBText(m_type.GetCurSel(), m_relation);
}
