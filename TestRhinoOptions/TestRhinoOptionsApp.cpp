#include "stdafx.h"
#include "TestRhinoOptionsApp.h"

BEGIN_MESSAGE_MAP(CTestRhinoOptionsApp, CWinApp)
END_MESSAGE_MAP()

CTestRhinoOptionsApp::CTestRhinoOptionsApp()
{
}

// The one and only CTestRhinoOptionsApp object
CTestRhinoOptionsApp theApp;

BOOL CTestRhinoOptionsApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
