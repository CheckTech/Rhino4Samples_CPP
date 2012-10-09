////////////////////////////////////////////////////////////////////////////////////
// TestDockBarDialog.h

#pragma once

#include "Resource.h"
#include "TestDockBarDialogPage0.h"
#include "TestDockBarDialogPage1.h"
#include "TestDockBarDialogPage2.h"

// CTestDockBarDialog

class CTestDockBarDialog : public CRhinoUiDockBarDialog
{
	DECLARE_SERIAL( CTestDockBarDialog )

public:
	CTestDockBarDialog( CWnd* pParent = NULL );
	virtual ~CTestDockBarDialog();

// Dialog Data
	enum { IDD = IDD_TEST_DOCKBAR_DIALOG };
  CRhinoUiTabPageCtrl m_tab_control;

  CTestDockBarDialogPage0 m_page0;
  CTestDockBarDialogPage1 m_page1;
  CTestDockBarDialogPage2 m_page2;

  // Dockbar visibility handler
  void OnDockBarPositionChanged( DWORD dwNewLocation );
  void OnShowDockBar( bool bShowDockBar );

public:
  virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
};
