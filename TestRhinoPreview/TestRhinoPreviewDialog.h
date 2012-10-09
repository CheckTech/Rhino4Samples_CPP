/////////////////////////////////////////////////////////////////////////////
// TestRhinoPreviewDialog.h

#pragma once

#include "resource.h"
#include "TestRhinoPreviewStatic.h"

class CTestRhinoPreviewDialog : public CRhinoDialog
{
	DECLARE_DYNAMIC( CTestRhinoPreviewDialog )

public:
	CTestRhinoPreviewDialog( CWnd* pParent = NULL );
	virtual ~CTestRhinoPreviewDialog();

// Dialog Data
	enum { IDD = IDD_TESTRHINOPREVIEW_DIALOG };
  CEdit m_edit;
  CButton m_button;
  CTestRhinoPreviewStatic m_preview;

public:
  virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange( CDataExchange* pDX );
  afx_msg void OnPreviewButtonClick();
	DECLARE_MESSAGE_MAP()

private:
  ON_wString m_filename;
};
