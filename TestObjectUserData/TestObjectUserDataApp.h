/////////////////////////////////////////////////////////////////////////////
// TestObjectUserDataApp.h : main header file for the TestObjectUserData DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestObjectUserDataApp
// See TestObjectUserDataApp.cpp for the implementation of this class
//

class CTestObjectUserDataApp : public CWinApp
{
public:
	CTestObjectUserDataApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
