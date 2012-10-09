/////////////////////////////////////////////////////////////////////////////
// TestDockBarDialogPage1.cpp

#include "stdafx.h"
#include "TestDockBarApp.h"
#include "TestDockBarDialogPage1.h"

IMPLEMENT_DYNAMIC( CTestDockBarDialogPage1, CRhinoUiTabCtrlPage )

CTestDockBarDialogPage1::CTestDockBarDialogPage1()
: CRhinoUiTabCtrlPage( CTestDockBarDialogPage1::IDD )
{
}

CTestDockBarDialogPage1::~CTestDockBarDialogPage1()
{
}

void CTestDockBarDialogPage1::DoDataExchange( CDataExchange* pDX )
{
	CRhinoUiTabCtrlPage::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CTestDockBarDialogPage1, CRhinoUiTabCtrlPage )
END_MESSAGE_MAP()

BOOL CTestDockBarDialogPage1::OnInitDialog()
{
  CRhinoUiTabCtrlPage::OnInitDialog();

  // TODO:  Add extra initialization here

  return TRUE;
}