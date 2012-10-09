/////////////////////////////////////////////////////////////////////////////
// TestRhinoCommandsApp.h : main header file for the TestRhinoCommands DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestRhinoCommandsApp
// See TestRhinoCommandsApp.cpp for the implementation of this class
//

class CTestRhinoCommandsApp : public CWinApp
{
public:
	CTestRhinoCommandsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
