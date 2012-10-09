/////////////////////////////////////////////////////////////////////////////
// TestAssociationDataApp.cpp

#include "stdafx.h"
#include "TestAssociationDataApp.h"

// CTestAssociationDataApp

BEGIN_MESSAGE_MAP(CTestAssociationDataApp, CWinApp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAssociationDataApp construction

CTestAssociationDataApp::CTestAssociationDataApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CTestAssociationDataApp object
CTestAssociationDataApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestAssociationDataApp initialization

BOOL CTestAssociationDataApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
