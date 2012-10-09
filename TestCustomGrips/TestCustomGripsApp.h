/////////////////////////////////////////////////////////////////////////////
// TestCustomGripsApp.h : main header file for the TestCustomGrips DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestCustomGripsApp
// See TestCustomGripsApp.cpp for the implementation of this class
//

class CTestCustomGripsApp : public CWinApp
{
public:
	CTestCustomGripsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
