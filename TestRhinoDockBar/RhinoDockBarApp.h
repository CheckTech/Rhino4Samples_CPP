/////////////////////////////////////////////////////////////////////////////
// RhinoDockBarApp.h : main header file for the RhinoDockBar DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRhinoDockBarApp
// See RhinoDockBarApp.cpp for the implementation of this class
//

class CRhinoDockBarApp : public CWinApp
{
public:
	CRhinoDockBarApp();



// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
