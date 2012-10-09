/////////////////////////////////////////////////////////////////////////////
// TestAttributeUserDataApp.cpp

#include "stdafx.h"
#include "TestAttributeUserDataApp.h"

// CTestAttributeUserDataApp

BEGIN_MESSAGE_MAP(CTestAttributeUserDataApp, CWinApp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAttributeUserDataApp construction

CTestAttributeUserDataApp::CTestAttributeUserDataApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CTestAttributeUserDataApp object
CTestAttributeUserDataApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestAttributeUserDataApp initialization

BOOL CTestAttributeUserDataApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
