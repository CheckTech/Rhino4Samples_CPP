/////////////////////////////////////////////////////////////////////////////
// TestBlockViewApp.cpp

#include "stdafx.h"
#include "TestBlockViewApp.h"

BEGIN_MESSAGE_MAP(CTestBlockViewApp, CWinApp)
END_MESSAGE_MAP()

CTestBlockViewApp::CTestBlockViewApp()
{
}

// The one and only CTestBlockViewApp object
CTestBlockViewApp theApp;

BOOL CTestBlockViewApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
