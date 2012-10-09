/////////////////////////////////////////////////////////////////////////////
// TestObjectPropertiesPageApp.h : main header file for the TestObjectPropertiesPage DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestObjectPropertiesPageApp
// See TestObjectPropertiesPageApp.cpp for the implementation of this class
//

class CTestObjectPropertiesPageApp : public CWinApp
{
public:
	CTestObjectPropertiesPageApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
