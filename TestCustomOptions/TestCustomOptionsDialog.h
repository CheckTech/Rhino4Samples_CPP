////////////////////////////////////////////////////////////////////////////////////
// TestCustomOptionsDockBar.h

#pragma once

#include "Resource.h"

////////////////////////////////////////////////////////////////////////////////////
// CMyOptionsListCtrlSeparator

class CMyOptionsListCtrlSeparator : public CRhinoUiOptionsListCtrlSeparator
{
public:
	CMyOptionsListCtrlSeparator( LPCTSTR lpsLabel = NULL, int iIndentLevel = 0 );

	virtual void OnDrawItem( CDC& dc, const CRect& rItem, const CRect& rDeflate ) const;

	bool Checked() const;
	void SetChecked( bool bChecked );

private:
	bool m_bChecked;
};

////////////////////////////////////////////////////////////////////////////////////
// CTestCustomOptionsDialog

class CTestCustomOptionsDialog : public CRhinoUiDockBarDialog
{
	DECLARE_SERIAL( CTestCustomOptionsDialog )

public:
	CTestCustomOptionsDialog( CWnd* pParent = 0 );
	virtual ~CTestCustomOptionsDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG };
	CRhinoUiOptionsListCtrl	m_list;
  // General
	CRhinoUiOptionsListCtrlSeparator m_static_general;
	CRhinoUiOptionsListCtrlEditBox m_edit_name;
  // Position
	CMyOptionsListCtrlSeparator m_static_position;
	CRhinoUiOptionsListCtrlEditBox m_edit_position_x;
	CRhinoUiOptionsListCtrlEditBox m_edit_position_y;
	CRhinoUiOptionsListCtrlEditBox m_edit_position_z;
  // Rotation
	CMyOptionsListCtrlSeparator m_static_rotation;
	CRhinoUiOptionsListCtrlEditBox m_edit_rotation_x;
	CRhinoUiOptionsListCtrlEditBox m_edit_rotation_y;
	CRhinoUiOptionsListCtrlEditBox m_edit_rotation_z;
  // Size
	CMyOptionsListCtrlSeparator m_static_size;
	CRhinoUiOptionsListCtrlEditBox m_edit_size_x;
	CRhinoUiOptionsListCtrlEditBox m_edit_size_y;
	CRhinoUiOptionsListCtrlEditBox m_edit_size_z;

public:
  virtual BOOL OnInitDialog();
  void OnShowDockBar( bool bShowDockBar );

protected:
  LRESULT OnOptionsListCtrl(WPARAM wParam, LPARAM lParam);
  virtual void DoDataExchange( CDataExchange* pDX );
	DECLARE_MESSAGE_MAP()

  void SetListControlPositions();
  void EnableDisableControls();

};
