
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
#include <afx.h>









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif



/************************************************************************/
/* ����ת��  ��int��CString                                                                     */
/************************************************************************/
static CString CStringFormat(int i){
	CString cstr;
	cstr.Format(_T("%d"), i);
	return cstr;
}


/************************************************************************/
/* ����ת��  ��COLOREF��CString                                                                     */
/************************************************************************/
static CString RGB2CString(COLORREF rgb)
{
	CString cstr;
	cstr.Format(_T("%d,%d,%d"), GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));
	return cstr;
}

/************************************************************************/
/* ����ת�� ��CString�� COLOREF                                                                     */
/************************************************************************/
static COLORREF CString2RGB(CString cstr)
{
	int pos = cstr.Find(_T(","));
	CString r = cstr.Left(pos);
	int len = cstr.Delete(0, pos + 1);
	cstr = cstr.Right(len);
	pos = cstr.Find(_T(","));
	CString g = cstr.Left(pos);
	len = cstr.Delete(0, pos + 1);
	CString b = cstr.Right(len);
	return RGB(_ttoi(r), _ttoi(g), _ttoi(b));
}

/************************************************************************/
/* �жϵ��Ƿ���Բ�ڲ�                                                                     */
/************************************************************************/
static BOOL PtInRect(CPoint pt, int x, int y, int w,int h){
	if (pt.x > x&&pt.x<x + w&&pt.y>y&&pt.y < y + h)
		return true;
	else
		return false;
}