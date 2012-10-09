////////////////////////////////////////////////////////////////////////////////////
// TestDockBarDialogPage1.h

#pragma once

#include "Resource.h"

// CTestDockBarDialogPage1

class CTestDockBarDialogPage1 : public CRhinoUiTabCtrlPage
{
	DECLARE_DYNAMIC( CTestDockBarDialogPage1 )

public:
	CTestDockBarDialogPage1();
	virtual ~CTestDockBarDialogPage1();

// Dialog Data
	enum { IDD = IDD_TAB_PAGE1 };

public:
  virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	DECLARE_MESSAGE_MAP()
};
