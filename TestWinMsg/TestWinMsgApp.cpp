/////////////////////////////////////////////////////////////////////////////
// TestWinMsgApp.cpp

#include "stdafx.h"
#include "TestWinMsgApp.h"

// CTestWinMsgApp

BEGIN_MESSAGE_MAP( CTestWinMsgApp, CWinApp )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestWinMsgApp construction

CTestWinMsgApp::CTestWinMsgApp()
{
}

// The one and only CTestWinMsgApp object
CTestWinMsgApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestWinMsgApp initialization

BOOL CTestWinMsgApp::InitInstance()
{
	CWinApp::InitInstance();
	return TRUE;
}
