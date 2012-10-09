/////////////////////////////////////////////////////////////////////////////
// TestPreviewDialog.h

#pragma once

#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewConduit

class CTestPreviewConduit : public CRhinoDisplayConduit
{
public:
  CTestPreviewConduit();
              
  bool ExecConduit( 
        CRhinoDisplayPipeline& dp, // pipeline executing this conduit
        UINT nChannel,             // current channel within the pipeline
        bool& bTerminate           // channel termination flag
        );

  ON_Circle m_circle;
};

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewDialog

class CTestPreviewDialog : public CRhinoDialog
{
	DECLARE_DYNAMIC(CTestPreviewDialog)

public:
	CTestPreviewDialog(CWnd* pParent = NULL);
	virtual ~CTestPreviewDialog();

// Dialog Data
	enum { IDD = IDD_TEST_PREVIEW };
  CRhinoUiSeparator m_sep1;
  CRhinoUiSeparator m_sep2;
  CRhinoUiEdit m_edit_center_x;
  CRhinoUiEdit m_edit_center_y;
  CRhinoUiEdit m_edit_center_z;
  CRhinoUiEdit m_edit_radius;
  double m_center_x;
  double m_center_y;
  double m_center_z;
  double m_radius;

  CTestPreviewConduit m_preview;

public:
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedPreview();
	afx_msg void OnBnClickedCancel();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()

};
