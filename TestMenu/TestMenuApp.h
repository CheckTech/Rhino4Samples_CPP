/////////////////////////////////////////////////////////////////////////////
// TestMenuApp.h : main header file for the TestMenu DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestMenuApp
// See TestMenuApp.cpp for the implementation of this class
//

class CTestMenuApp : public CWinApp
{
public:
	CTestMenuApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
