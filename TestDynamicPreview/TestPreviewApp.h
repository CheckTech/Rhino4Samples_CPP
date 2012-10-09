/////////////////////////////////////////////////////////////////////////////
// TestPreviewApp.h : main header file for the TestPreview DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewApp
// See TestPreviewApp.cpp for the implementation of this class
//

class CTestPreviewApp : public CWinApp
{
public:
	CTestPreviewApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
