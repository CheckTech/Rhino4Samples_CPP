#pragma once

// CToolbarsDlg dialog

class CToolbarsDlg : public CRhinoDialog
{
	DECLARE_DYNAMIC(CToolbarsDlg)

public:
	CToolbarsDlg( const wchar_t* lpsCollectionFileName, CWnd* pParent = NULL);   // standard constructor
	virtual ~CToolbarsDlg();

// Dialog Data
	enum { IDD = IDD_TOOLBARS };

protected:
  ON_wString m_wCollectionFileName;
  CRhinoUiStatic m_StaticFileName;
  CCheckListBox m_ToolBarsListBox;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
  virtual BOOL OnInitDialog();
	afx_msg void OnChkChange();
};
