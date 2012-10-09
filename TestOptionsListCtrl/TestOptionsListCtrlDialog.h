////////////////////////////////////////////////////////////////////////////////////
// TestOptionsListCtrlDialog.h

#pragma once

#include "Resource.h"

class CTestListCtrl : public CRhinoUiOptionsListCtrl
{
public:
  CTestListCtrl();
  ~CTestListCtrl();

  void OnEndEditItem( CRhinoUiOptionsListCtrlItem& item );
  bool OnItemButtonClicked( CRhinoUiOptionsListCtrlPushButton& item );
  bool OnItemButtonClicked( CRhinoUiOptionsListCtrlCheckBox& item );
  bool PopulateItemComboBox( CRhinoUiOptionsListCtrlComboBox& item );
  bool OnComboBoxPopulated( CRhinoUiOptionsListCtrlComboBox& item );
  void OnItemComboBoxSelChanged( CRhinoUiOptionsListCtrlComboBox& item );

  CRhinoUiOptionsListCtrlCheckBox m_HasIsoCurves;
  CRhinoUiOptionsListCtrlCheckBox m_ShowIsoCurves;
  CRhinoUiOptionsListCtrlEditBox m_IsoCurveDinsity;
  CRhinoUiOptionsListCtrlIPAddress m_IPAddress;
  CRhinoUiOptionsListCtrlCheckBox m_VerticalCheckBox;
  CRhinoUiOptionsListCtrlCheckBox m_HideTabCheckBox;
  CRhinoUiOptionsListCtrlRadioButtonColumn m_RadioColumn;
  CRhinoUiOptionsListCtrlPointEditBox m_PointEditBox;
  CRhinoUiOptionsListCtrlCheckBox m_ExpandCheckBox1;
  CRhinoUiOptionsListCtrlCheckBox m_ExpandCheckBox2;
  CRhinoUiOptionsListCtrlCheckBox m_ExpandCheckBox3;
  CRhinoUiOptionsListCtrlCheckBox m_ExpandCheckBox4;
  CRhinoUiOptionsListCtrlGroupComboBox m_GroupCombo;
  CRhinoUiOptionsListCtrlGroupComboBox m_NestedGroupCombo;
};


class CTestOptionsListCtrlDialog : public CRhinoUiDockBarDialog
{
	DECLARE_SERIAL( CTestOptionsListCtrlDialog )

public:
	CTestOptionsListCtrlDialog( CWnd* pParent = NULL );
	virtual ~CTestOptionsListCtrlDialog();

// Dialog Data
	enum { IDD = IDD_TEST_DIALOG };

public:
  virtual BOOL OnInitDialog();
  void OnShowDockBar( bool bShowDockBar );

protected:
	virtual void DoDataExchange( CDataExchange* pDX );
  afx_msg LRESULT OnRegisteredMessage( WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
  friend class CTestListCtrl;
  CRhinoUiOptionsListCtrlComboBox* m_pLayerItem;
  CRhinoUiOptionsListCtrlComboBox* m_pColorItem;
  CRhinoUiOptionsListCtrlComboBox m_ComboBoxItem;
  CTestListCtrl m_options_list;

  void CreateGroup( 
      CRhinoUiOptionsListCtrlGroupComboBox& combo,
      const wchar_t* lpsItem,
      CRhinoUiOptionsListCtrlGroupComboBox* pNestedCombo = NULL
      );
};
