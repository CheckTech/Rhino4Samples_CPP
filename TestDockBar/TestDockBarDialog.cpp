/////////////////////////////////////////////////////////////////////////////
// TestDockBarDialog.cpp

#include "stdafx.h"
#include "TestDockBarApp.h"
#include "TestDockBarDialog.h"

IMPLEMENT_SERIAL( CTestDockBarDialog, CRhinoUiDockBarDialog, 1 )

CTestDockBarDialog::CTestDockBarDialog( CWnd* pParent )
: CRhinoUiDockBarDialog( CTestDockBarDialog::IDD, pParent )
{
}

CTestDockBarDialog::~CTestDockBarDialog()
{
}

void CTestDockBarDialog::DoDataExchange( CDataExchange* pDX )
{
  CRhinoUiDockBarDialog::DoDataExchange( pDX );
  DDX_Control( pDX, IDC_TAB, m_tab_control );
}

BEGIN_MESSAGE_MAP( CTestDockBarDialog, CRhinoUiDockBarDialog )
END_MESSAGE_MAP()

BOOL CTestDockBarDialog::OnInitDialog()
{
  CRhinoUiDockBarDialog::OnInitDialog();

  m_tab_control.AddPage( m_page0, L"Page 0" );
  m_tab_control.AddPage( m_page1, L"Page 1" );
  m_tab_control.AddPage( m_page2, L"Page 2" );

  m_tab_control.SetActivePage( 0);

  return TRUE;
}

void CTestDockBarDialog::OnDockBarPositionChanged( DWORD dwNewLocation )
{
  if( dwNewLocation == AFX_IDW_DOCKBAR_FLOAT )
  {
  }
  else
  {
  }
}

void CTestDockBarDialog::OnShowDockBar( bool bShowDockBar )
{
  if( bShowDockBar )
  {
  }
  else
  {
  }
}
