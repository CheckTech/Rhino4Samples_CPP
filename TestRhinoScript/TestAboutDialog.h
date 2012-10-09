/////////////////////////////////////////////////////////////////////////////
// TestScriptObject.cpp
//

#pragma once

#include "Resource.h"

class CTestAboutDialog : public CRhinoDialog
{
	DECLARE_DYNAMIC(CTestAboutDialog)

public:
	CTestAboutDialog(CWnd* pParent = NULL);
	virtual ~CTestAboutDialog();

// Dialog Data
	enum { IDD = IDD_ABOUT };

public:
  virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
};
