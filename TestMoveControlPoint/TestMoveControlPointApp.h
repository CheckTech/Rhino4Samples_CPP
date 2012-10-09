/////////////////////////////////////////////////////////////////////////////
// TestMoveControlPointApp.h : main header file for the TestMoveControlPoint DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestMoveControlPointApp
// See TestMoveControlPointApp.cpp for the implementation of this class
//

class CTestMoveControlPointApp : public CWinApp
{
public:
	CTestMoveControlPointApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
