// ConfirmDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UserCase.h"
#include "ConfirmDlg.h"
#include "afxdialogex.h"


// CConfirmDlg �Ի���

IMPLEMENT_DYNAMIC(CConfirmDlg, CDialogEx)

CConfirmDlg::CConfirmDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfirmDlg::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

CConfirmDlg::~CConfirmDlg()
{
}

void CConfirmDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfirmDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CConfirmDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IConfirmDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {24ACB983-321D-43D9-A77D-DF7294114CE1}
static const IID IID_IConfirmDlg =
{ 0x24ACB983, 0x321D, 0x43D9, { 0xA7, 0x7D, 0xDF, 0x72, 0x94, 0x11, 0x4C, 0xE1 } };

BEGIN_INTERFACE_MAP(CConfirmDlg, CDialogEx)
	INTERFACE_PART(CConfirmDlg, IID_IConfirmDlg, Dispatch)
END_INTERFACE_MAP()


// CConfirmDlg ��Ϣ�������
