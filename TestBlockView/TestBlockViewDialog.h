/////////////////////////////////////////////////////////////////////////////
// TestBlockViewDialog.h

#pragma once

#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTestBlockViewDialog

class CTestBlockViewDialog : public CRhinoDialog
{
	DECLARE_DYNAMIC( CTestBlockViewDialog )

public:
  CTestBlockViewDialog( CWnd* pParent, CRhinoDoc& doc );
	virtual ~CTestBlockViewDialog();

  // Dialog Data
	enum { IDD = IDD_BLOCKVIEW_DIALOG };
  CListBox m_listbox;
  CStatic m_preview;

public:
  virtual BOOL OnInitDialog();
  afx_msg void OnSelChangeListBox();
  afx_msg void OnPaint();

protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	DECLARE_MESSAGE_MAP()

  void CreateTopViewport( CRhinoViewport& vp );
  void ZoomExtentsViewport( CRhinoViewport& vp );
  CRect GetPaintRect();

protected:
  CRhinoDoc& m_doc;
  const CRhinoInstanceDefinition* m_idef;
};
