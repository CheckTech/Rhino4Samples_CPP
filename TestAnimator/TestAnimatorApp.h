/////////////////////////////////////////////////////////////////////////////
// TestAnimatorApp.h : main header file for the TestAnimator DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestAnimatorApp
// See TestAnimatorApp.cpp for the implementation of this class
//

class CTestAnimatorApp : public CWinApp
{
public:
	CTestAnimatorApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
