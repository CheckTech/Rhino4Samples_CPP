////////////////////////////////////////////////////////////////////////////////////
// TestDockBarDialogPage0.h

#pragma once

#include "Resource.h"

// CTestDockBarDialogPage0

class CTestDockBarDialogPage0 : public CRhinoUiTabCtrlPage
{
	DECLARE_DYNAMIC( CTestDockBarDialogPage0 )

public:
	CTestDockBarDialogPage0();
	virtual ~CTestDockBarDialogPage0();

// Dialog Data
	enum { IDD = IDD_TAB_PAGE0 };

public:
  virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	DECLARE_MESSAGE_MAP()
};
