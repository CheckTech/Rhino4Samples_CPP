/////////////////////////////////////////////////////////////////////////////
// GridListCtrlExampleApp.h : main header file for the GridListCtrlExample DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGridListCtrlExampleApp
// See GridListCtrlExampleApp.cpp for the implementation of this class
//

class CGridListCtrlExampleApp : public CWinApp
{
public:
	CGridListCtrlExampleApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
