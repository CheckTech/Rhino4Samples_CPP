/////////////////////////////////////////////////////////////////////////////
// TestDockBarDialogPage0.cpp

#include "stdafx.h"
#include "TestDockBarApp.h"
#include "TestDockBarDialogPage0.h"

IMPLEMENT_DYNAMIC( CTestDockBarDialogPage0, CRhinoUiTabCtrlPage )

CTestDockBarDialogPage0::CTestDockBarDialogPage0()
: CRhinoUiTabCtrlPage( CTestDockBarDialogPage0::IDD )
{
}

CTestDockBarDialogPage0::~CTestDockBarDialogPage0()
{
}

void CTestDockBarDialogPage0::DoDataExchange( CDataExchange* pDX )
{
	CRhinoUiTabCtrlPage::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CTestDockBarDialogPage0, CRhinoUiTabCtrlPage )
END_MESSAGE_MAP()

BOOL CTestDockBarDialogPage0::OnInitDialog()
{
  CRhinoUiTabCtrlPage::OnInitDialog();

  // TODO:  Add extra initialization here

  return TRUE;
}