/////////////////////////////////////////////////////////////////////////////
// TestArchiveApp.h : main header file for the TestArchive DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestArchiveApp
// See TestArchiveApp.cpp for the implementation of this class
//

class CTestArchiveApp : public CWinApp
{
public:
	CTestArchiveApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
