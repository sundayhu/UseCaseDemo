
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
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
/* 类型转换  从int到CString                                                                     */
/************************************************************************/
static CString CStringFormat(int i){
	CString cstr;
	cstr.Format(_T("%d"), i);
	return cstr;
}


/************************************************************************/
/* 类型转换  从COLOREF到CString                                                                     */
/************************************************************************/
static CString RGB2CString(COLORREF rgb)
{
	CString cstr;
	cstr.Format(_T("%d,%d,%d"), GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));
	return cstr;
}

/************************************************************************/
/* 类型转换 从CString到 COLOREF                                                                     */
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
/* 判断点是否在圆内部                                                                     */
/************************************************************************/
static BOOL PtInRect(CPoint pt, int x, int y, int w,int h){
	if (pt.x > x&&pt.x<x + w&&pt.y>y&&pt.y < y + h)
		return true;
	else
		return false;
}