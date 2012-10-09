/////////////////////////////////////////////////////////////////////////////
// TestRhinoPreviewApp.cpp

#include "stdafx.h"
#include "TestRhinoPreviewApp.h"

BEGIN_MESSAGE_MAP(CTestRhinoPreviewApp, CWinApp)
END_MESSAGE_MAP()

CTestRhinoPreviewApp::CTestRhinoPreviewApp()
{
}

// The one and only CTestRhinoPreviewApp object
CTestRhinoPreviewApp theApp;

BOOL CTestRhinoPreviewApp::InitInstance()
{
	CWinApp::InitInstance();
	return TRUE;
}
