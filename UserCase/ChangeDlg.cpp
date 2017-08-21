// ChangeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UserCase.h"
#include "ChangeDlg.h"
#include "afxdialogex.h"


// CChangeDlg �Ի���

IMPLEMENT_DYNAMIC(CChangeDlg, CDialogEx)

CChangeDlg::CChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeDlg::IDD, pParent)
	, m_change(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CChangeDlg::~CChangeDlg()
{
}

void CChangeDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_change);
	DDV_MaxChars(pDX, m_change, 20);
}


BEGIN_MESSAGE_MAP(CChangeDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CChangeDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IChangeDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {3EE0BAE0-C572-4F09-9A8A-4A2AC8FB3405}
static const IID IID_IChangeDlg =
{ 0x3EE0BAE0, 0xC572, 0x4F09, { 0x9A, 0x8A, 0x4A, 0x2A, 0xC8, 0xFB, 0x34, 0x5 } };

BEGIN_INTERFACE_MAP(CChangeDlg, CDialogEx)
	INTERFACE_PART(CChangeDlg, IID_IChangeDlg, Dispatch)
END_INTERFACE_MAP()


// CChangeDlg ��Ϣ�������
