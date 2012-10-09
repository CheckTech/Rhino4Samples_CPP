/////////////////////////////////////////////////////////////////////////////
// TestPointCloudUserDataApp.cpp

#include "stdafx.h"
#include "TestPointCloudUserDataApp.h"

BEGIN_MESSAGE_MAP(CTestPointCloudUserDataApp, CWinApp)
END_MESSAGE_MAP()

CTestPointCloudUserDataApp::CTestPointCloudUserDataApp()
{
}

// The one and only CTestPointCloudUserDataApp object
CTestPointCloudUserDataApp theApp;

BOOL CTestPointCloudUserDataApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
