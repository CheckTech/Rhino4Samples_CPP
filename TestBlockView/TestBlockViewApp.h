/////////////////////////////////////////////////////////////////////////////
// TestBlockViewApp.h

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestBlockViewApp

class CTestBlockViewApp : public CWinApp
{
public:
	CTestBlockViewApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
