/////////////////////////////////////////////////////////////////////////////
// TestDigitizerApp.h : main header file for the TestDigitizer DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDigitizerApp
// See TestDigitizerApp.cpp for the implementation of this class
//

class CTestDigitizerApp : public CWinApp
{
public:
	CTestDigitizerApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
