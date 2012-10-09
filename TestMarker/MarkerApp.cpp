/////////////////////////////////////////////////////////////////////////////
// MarkerApp.cpp : Defines the initialization routines for the DLL.
//

#include "StdAfx.h"
#include "MarkerApp.h"

BEGIN_MESSAGE_MAP(CMarkerApp, CWinApp)
END_MESSAGE_MAP()

CMarkerApp::CMarkerApp()
{
}

// The one and only CMarkerApp object
CMarkerApp theApp;

BOOL CMarkerApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
