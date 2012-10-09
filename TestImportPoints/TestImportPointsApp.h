/////////////////////////////////////////////////////////////////////////////
// TestImportPointsApp.h : main header file for the TestImportPoints DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestImportPointsApp
// See TestImportPointsApp.cpp for the implementation of this class
//

class CTestImportPointsApp : public CWinApp
{
public:
	CTestImportPointsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
