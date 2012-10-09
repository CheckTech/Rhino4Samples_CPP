/////////////////////////////////////////////////////////////////////////////
// StdAfx.h : Include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently
//

#if !defined(AFX_STDAFX_H__1B19BC45_62FC_44AB_8CAB_DD61E99C5BB6__INCLUDED_)
#define AFX_STDAFX_H__1B19BC45_62FC_44AB_8CAB_DD61E99C5BB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

// Rhino plug-ins must always use the release MFC that Rhino uses.
// Rhino plug-ins that require debugging information need to be built
// with RHINO_DEBUG_PLUGIN defined.
#if defined( _DEBUG )
#error Do not define _DEBUG - use RHINO_DEBUG_PLUGIN instead
#endif

// Rhino SDK Preamble
#include "..\..\Program Files\Rhino 3.0 SDK\Inc\RhinoSdkStdafxPreamble.h"

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


// Add other stuff frequently used by Rhino plug-in developers here
#include <RichEdit.h>
#include <Shlwapi.h>
#include <Imagehlp.h>
#include <io.h>
#include <tchar.h>
#include <atlbase.h>

// Rhino SDK classes
#include "..\..\Program Files\Rhino 3.0 SDK\Inc\RhinoSdk.h"
#include "TestDocumentDataPlugin.h"

#if defined( RHINO_DEBUG_PLUGIN )
// Now that all the system headers are read, we can
// safely define _DEBUG so the developers can test
// for _DEBUG in their code.
#define _DEBUG
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1B19BC45_62FC_44AB_8CAB_DD61E99C5BB6__INCLUDED_)
