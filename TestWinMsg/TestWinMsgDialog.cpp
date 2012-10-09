/////////////////////////////////////////////////////////////////////////////
// TestWinMsgDialog.cpp

#include "stdafx.h"
#include "TestWinMsgDialog.h"

// Register our new, unique window messages
const UINT TEST_WND_MSG_OK = ::RegisterWindowMessage( L"TEST_WND_MSG_COMPLETE_E5E70FC-E269-4DA5-AAD4-50A0D0941782" );
const UINT TEST_WND_MSG_CANCEL = ::RegisterWindowMessage( L"TEST_WND_MSG_CANCEL_4703B8A4-B408-4650-82ED-66F2F78CF3CE" );

UINT CTestWinMsgDialog::TestWinMsgOk() { return TEST_WND_MSG_OK; }
UINT CTestWinMsgDialog::TestWinMsgCancel() { return TEST_WND_MSG_CANCEL; }

static void PostTestWinMsgOk( WPARAM wParam, LPARAM lParam)
{
  ::PostMessage( RhinoApp().MainWnd(), CTestWinMsgDialog::TestWinMsgOk(), wParam, lParam );
}

static void PostTestWinMsgCancel( WPARAM wParam, LPARAM lParam )
{
  ::PostMessage( RhinoApp().MainWnd(), CTestWinMsgDialog::TestWinMsgCancel(), wParam, lParam );
}

/////////////////////////////////////////////////////////////////////////////
// CTestWinMsgDialog dialog

IMPLEMENT_DYNAMIC( CTestWinMsgDialog, CRhinoDialog )

CTestWinMsgDialog::CTestWinMsgDialog( bool m_bAutoDelete )
: CRhinoDialog((UINT)0, 0)
, m_bAutoDelete(true)
{
}

CTestWinMsgDialog::~CTestWinMsgDialog()
{
}

BOOL CTestWinMsgDialog::Create( UINT nIDTemplate, CWnd* pParentWnd ) 
{  
	return CRhinoDialog::Create( nIDTemplate, pParentWnd );
}

BOOL CTestWinMsgDialog::Create( LPCTSTR lpszTemplateName, CWnd* pParentWnd ) 
{
  return CRhinoDialog::Create( lpszTemplateName, pParentWnd );
}       

void CTestWinMsgDialog::PostNcDestroy()
{
  if( m_bAutoDelete )
	  delete this;
}

void CTestWinMsgDialog::DoDataExchange( CDataExchange* pDX )
{
	CRhinoDialog::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CTestWinMsgDialog, CRhinoDialog )
END_MESSAGE_MAP()

// CTestWinMsgDialog message handlers

BOOL CTestWinMsgDialog::OnInitDialog()
{
  CRhinoDialog::OnInitDialog();

  // TODO:  Add extra initialization here

  return TRUE;
}

void CTestWinMsgDialog::OnOK() 
{
  // Post a TEST_WND_MSG_OK message
  PostTestWinMsgOk( 0, 0 );
	DestroyWindow();
}

void CTestWinMsgDialog::OnCancel() 
{
  // Post a TEST_WND_MSG_CANCEL message
  PostTestWinMsgCancel( 0, 0 );
	DestroyWindow();
}
