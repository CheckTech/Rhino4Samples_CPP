/////////////////////////////////////////////////////////////////////////////
// TestDockBarDialogPage2.cpp

#include "stdafx.h"
#include "TestDockBarApp.h"
#include "TestDockBarDialogPage2.h"

IMPLEMENT_DYNAMIC( CTestDockBarDialogPage2, CRhinoUiTabCtrlPage )

CTestDockBarDialogPage2::CTestDockBarDialogPage2()
: CRhinoUiTabCtrlPage( CTestDockBarDialogPage2::IDD )
{
}

CTestDockBarDialogPage2::~CTestDockBarDialogPage2()
{
}

void CTestDockBarDialogPage2::DoDataExchange( CDataExchange* pDX )
{
	CRhinoUiTabCtrlPage::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CTestDockBarDialogPage2, CRhinoUiTabCtrlPage )
END_MESSAGE_MAP()

BOOL CTestDockBarDialogPage2::OnInitDialog()
{
  CRhinoUiTabCtrlPage::OnInitDialog();

  // TODO:  Add extra initialization here

  return TRUE;
}