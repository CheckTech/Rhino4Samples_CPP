/////////////////////////////////////////////////////////////////////////////
// TestWinMsgApp.h

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestWinMsgApp

class CTestWinMsgApp : public CWinApp
{
public:
	CTestWinMsgApp();

// Overrides
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};
