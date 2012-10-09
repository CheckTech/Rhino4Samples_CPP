/////////////////////////////////////////////////////////////////////////////
// TestOptionsListCtrlApp.h

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestOptionsListCtrlApp

class CTestOptionsListCtrlApp : public CWinApp
{
public:
	CTestOptionsListCtrlApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
