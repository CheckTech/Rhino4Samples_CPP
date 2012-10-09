////////////////////////////////////////////////////////////////////////////////////
// TestDockBar.cpp

#include "Stdafx.h"
#include "TestDockBar.h"

IMPLEMENT_SERIAL( CTestDockBar, CRhinoUiDockBar, 1 );

CTestDockBar::CTestDockBar()
{
}

CTestDockBar::~CTestDockBar()
{
}

BEGIN_MESSAGE_MAP( CTestDockBar, CRhinoUiDockBar )
END_MESSAGE_MAP()

ON_UUID CTestDockBar::Id()
{
  // {CD312401-B41A-4a59-9C54-62215E818624}
  static const GUID TestDockBar_UUID =
  { 0xcd312401, 0xb41a, 0x4a59, { 0x9c, 0x54, 0x62, 0x21, 0x5e, 0x81, 0x86, 0x24 } };
	return TestDockBar_UUID;
}

UUID CTestDockBar::DockBarID() const
{
  return Id();
}

const wchar_t* CTestDockBar::DockBarName( int language_id )  const
{
	return L"TestDockBar";
}

bool CTestDockBar::CreateDockBarControls()
{
	bool rc = CreateDockBarClientDialog(
        CTestDockBarDialog::IDD, 
        NULL, 
        RUNTIME_CLASS(CTestDockBarDialog), 
        AfxGetStaticModuleState() 
        );

	return rc;
}

void CTestDockBar::OnDockBarPositionChanged( DWORD dwNewLocation )
{
  CWnd* pWnd = DockBarClientWnd();
  if( pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CTestDockBarDialog)) )
  {
    CTestDockBarDialog* pDialog = static_cast<CTestDockBarDialog*>(pWnd);
    if( pDialog )
      pDialog->OnDockBarPositionChanged( dwNewLocation );
  }
}

void CTestDockBar::OnShowDockBar( bool bShowDockBar )
{
  CWnd* pWnd = DockBarClientWnd();
  if( pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CTestDockBarDialog)) )
  {
    CTestDockBarDialog* pDialog = static_cast<CTestDockBarDialog*>(pWnd);
    if( pDialog )
      pDialog->OnShowDockBar( bShowDockBar );
  }
}
