// clang-format off
/******************************************************************************
  Description   :  Include file for precompiled header
  Author(s)     :  Anish Kumar
  Copyright (c) 2011, Robert Bosch Engineering and Business Solutions.  All rights reserved.
******************************************************************************/
// clang-format on

#ifndef KERNEL_BUSMASTERDRIVERINTERFACE_DIL_J1939_DIL_J1939_STDAFX_H_
#define KERNEL_BUSMASTERDRIVERINTERFACE_DIL_J1939_DIL_J1939_STDAFX_H_

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN  // Exclude rarely-used stuff from Windows headers
#endif

// some CString constructors will be explicit
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#include <afxext.h>  // MFC extensions
#include <afxwin.h>  // MFC core and standard components

#ifndef _AFX_NO_OLE_SUPPORT
#endif  // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#endif  // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#endif  // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>  // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>  // MFC support for Windows Common Controls
#include <afxtempl.h>
#include <locale.h>
#endif  // _AFX_NO_AFXCMN_SUPPORT

#endif  // KERNEL_BUSMASTERDRIVERINTERFACE_DIL_J1939_DIL_J1939_STDAFX_H_