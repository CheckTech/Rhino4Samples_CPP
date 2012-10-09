/////////////////////////////////////////////////////////////////////////////
// ToolBarTestPlugInApp.h : main header file for the ToolBarTestPlugIn DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CToolBarTestPlugInApp
// See ToolBarTestPlugInApp.cpp for the implementation of this class
//

class CToolBarTestPlugInApp : public CWinApp
{
public:
	CToolBarTestPlugInApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
