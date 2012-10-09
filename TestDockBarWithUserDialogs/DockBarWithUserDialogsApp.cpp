/////////////////////////////////////////////////////////////////////////////
// DockBarWithUserDialogsApp.cpp

#include "stdafx.h"
#include "DockBarWithUserDialogsApp.h"

// CDockBarWithUserDialogsApp

BEGIN_MESSAGE_MAP(CDockBarWithUserDialogsApp, CWinApp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDockBarWithUserDialogsApp construction

CDockBarWithUserDialogsApp::CDockBarWithUserDialogsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CDockBarWithUserDialogsApp object
CDockBarWithUserDialogsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDockBarWithUserDialogsApp initialization

BOOL CDockBarWithUserDialogsApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
