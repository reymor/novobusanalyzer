// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef BUSMASTER_UDS_PROTOCOL_STDAFX_H_
#define BUSMASTER_UDS_PROTOCOL_STDAFX_H_

#define VC_EXTRALEAN  // Exclude rarely-used stuff from Windows headers
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  // some CString constructors will be
                                            // explicit

#include <afxdtctl.h>  // MFC support for Internet Explorer 4 Common Controls
#include <afxext.h>    // MFC extensions
#include <afxwin.h>    // MFC core and standard components

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>  // MFC support for Windows Common Controls
#endif               // _AFX_NO_AFXCMN_SUPPORT

#include <IO.H>  // i/0 header definitions
#include <afxmt.h>
#include <afxpriv.h>
#include <afxtempl.h>
#include <locale.h>
#include <math.h>
#include <mmsystem.h>
#include <stdlib.h>  // standard library definitions

// TODO: reference additional headers your program requires here

#endif  // BUSMASTER_UDS_PROTOCOL_STDAFX_H_