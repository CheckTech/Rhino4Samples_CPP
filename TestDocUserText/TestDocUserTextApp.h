/////////////////////////////////////////////////////////////////////////////
// TestDocUserTextApp.h : main header file for the TestDocUserText DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDocUserTextApp
// See TestDocUserTextApp.cpp for the implementation of this class
//

class CTestDocUserTextApp : public CWinApp
{
public:
	CTestDocUserTextApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
