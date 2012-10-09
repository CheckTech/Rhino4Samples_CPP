////////////////////////////////////////////////////////////////////////////////////
// TestCustomOptionsDockBar.cpp

#include "Stdafx.h"
#include "TestCustomOptionsDockBar.h"

IMPLEMENT_SERIAL( CTestCustomOptionsDockBar, CRhinoUiDockBar, 1 );

CTestCustomOptionsDockBar::CTestCustomOptionsDockBar()
{
}

CTestCustomOptionsDockBar::~CTestCustomOptionsDockBar()
{
}

BEGIN_MESSAGE_MAP( CTestCustomOptionsDockBar, CRhinoUiDockBar )
END_MESSAGE_MAP()

ON_UUID CTestCustomOptionsDockBar::Id()
{
  // {F6670F7A-2A6D-4A01-9EA9-FD92184E6C23}
  static const GUID TestCustomOptionsDockBar_UUID = { 0xF6670F7A, 0x2A6D, 0x4A01, { 0x9E, 0xA9, 0xFD, 0x92, 0x18, 0x4E, 0x6C, 0x23 } };
	return TestCustomOptionsDockBar_UUID;
}

UUID CTestCustomOptionsDockBar::DockBarID() const
{
  return Id();
}

const wchar_t* CTestCustomOptionsDockBar::DockBarName( int language_id )  const
{
	return L"Test Custom Options";
}

bool CTestCustomOptionsDockBar::CreateDockBarControls()
{
	bool rc = CreateDockBarClientDialog(
        CTestCustomOptionsDialog::IDD, 
        0, 
        RUNTIME_CLASS(CTestCustomOptionsDialog), 
        AfxGetStaticModuleState() 
        );

	return rc;
}

void CTestCustomOptionsDockBar::OnShowDockBar( bool bShowDockBar )
{
  CWnd* pWnd = DockBarClientWnd();
  if( pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CTestCustomOptionsDialog)) )
  {
    CTestCustomOptionsDialog* pDialog = static_cast<CTestCustomOptionsDialog*>(pWnd);
    if( pDialog )
      pDialog->OnShowDockBar( bShowDockBar );
  }
}
