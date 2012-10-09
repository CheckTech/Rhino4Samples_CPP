////////////////////////////////////////////////////////////////////////////////////
// TestOptionsListCtrlDockBar.cpp

#include "Stdafx.h"
#include "TestOptionsListCtrlDockBar.h"

IMPLEMENT_SERIAL( CTestOptionsListCtrlDockBar, CRhinoUiDockBar, 1 );

CTestOptionsListCtrlDockBar::CTestOptionsListCtrlDockBar()
{
}

CTestOptionsListCtrlDockBar::~CTestOptionsListCtrlDockBar()
{
}

BEGIN_MESSAGE_MAP( CTestOptionsListCtrlDockBar, CRhinoUiDockBar )
END_MESSAGE_MAP()

ON_UUID CTestOptionsListCtrlDockBar::Id()
{
  // {17A388EF-EDE3-4568-AFD0-C875586CB62F}
  static const GUID TestOptionsListCtrlDockBar_UUID =
  { 0x17A388EF, 0xEDE3, 0x4568, { 0xAF, 0xD0, 0xC8, 0x75, 0x58, 0x6C, 0xB6, 0x2F } };
	return TestOptionsListCtrlDockBar_UUID;
}

UUID CTestOptionsListCtrlDockBar::DockBarID() const
{
  return Id();
}

const wchar_t* CTestOptionsListCtrlDockBar::DockBarName( int language_id )  const
{
	return L"TestOptions";
}

bool CTestOptionsListCtrlDockBar::CreateDockBarControls()
{
	bool rc = CreateDockBarClientDialog(
        CTestOptionsListCtrlDialog::IDD, 
        NULL, 
        RUNTIME_CLASS(CTestOptionsListCtrlDialog), 
        AfxGetStaticModuleState() 
        );

	return rc;
}

void CTestOptionsListCtrlDockBar::OnShowDockBar( bool bShowDockBar )
{
  CWnd* pWnd = DockBarClientWnd();
  if( pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CTestOptionsListCtrlDialog)) )
  {
    CTestOptionsListCtrlDialog* pDialog = static_cast<CTestOptionsListCtrlDialog*>(pWnd);
    if( pDialog )
      pDialog->OnShowDockBar( bShowDockBar );
  }
}
