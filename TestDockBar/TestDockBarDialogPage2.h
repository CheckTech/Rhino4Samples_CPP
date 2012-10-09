////////////////////////////////////////////////////////////////////////////////////
// TestDockBarDialogPage2.h

#pragma once

#include "Resource.h"

// CTestDockBarDialogPage2

class CTestDockBarDialogPage2 : public CRhinoUiTabCtrlPage
{
	DECLARE_DYNAMIC( CTestDockBarDialogPage2 )

public:
	CTestDockBarDialogPage2();
	virtual ~CTestDockBarDialogPage2();

// Dialog Data
	enum { IDD = IDD_TAB_PAGE2 };

public:
  virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
};
