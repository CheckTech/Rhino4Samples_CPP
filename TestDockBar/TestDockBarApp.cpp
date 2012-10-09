/////////////////////////////////////////////////////////////////////////////
// TestDockBarApp.cpp

#include "stdafx.h"
#include "TestDockBarApp.h"

// CTestDockBarApp

BEGIN_MESSAGE_MAP(CTestDockBarApp, CWinApp)
END_MESSAGE_MAP()


CTestDockBarApp::CTestDockBarApp()
{
}

// The one and only CTestDockBarApp object
CTestDockBarApp theApp;

BOOL CTestDockBarApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
