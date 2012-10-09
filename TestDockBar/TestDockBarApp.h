/////////////////////////////////////////////////////////////////////////////
// TestDockBarApp.h

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"

// CTestDockBarApp

class CTestDockBarApp : public CWinApp
{
public:
	CTestDockBarApp();

public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};
