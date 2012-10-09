////////////////////////////////////////////////////////////////////////////////////
// TestOptionsListCtrlDialog.cpp

#include "StdAfx.h"
#include "TestOptionsListCtrlDialog.h"

CTestListCtrl::CTestListCtrl()
{
  m_PointEditBox.SetAutoDelete( false );
  m_ExpandCheckBox1.SetAutoDelete( false );
  m_ExpandCheckBox2.SetAutoDelete( false );
  m_ExpandCheckBox3.SetAutoDelete( false );
  m_ExpandCheckBox4.SetAutoDelete( false );
  m_GroupCombo.SetAutoDelete( false );
  m_NestedGroupCombo.SetAutoDelete( false );
}

CTestListCtrl::~CTestListCtrl()
{
}

void CTestListCtrl::OnEndEditItem( CRhinoUiOptionsListCtrlItem& item )
{
  CRhinoUiOptionsListCtrl::OnEndEditItem( item);
}

bool CTestListCtrl::OnItemButtonClicked( CRhinoUiOptionsListCtrlPushButton& item )
{
  CRhinoUiOptionsListCtrl::OnItemButtonClicked( item );
  return true;
}

bool CTestListCtrl::OnItemButtonClicked( CRhinoUiOptionsListCtrlCheckBox& item )
{
  CRhinoUiOptionsListCtrl::OnItemButtonClicked( item );

  CTestOptionsListCtrlDialog* pDlg = static_cast<CTestOptionsListCtrlDialog*>( GetParent());
  if( item.ItemID() == m_VerticalCheckBox.ItemID())
  {
    //pDlg->GetTabCtrl()->SetExpandableTabFlag( CRhinoUiExpandableTabCtrl::etf_vertical_tabs, BST_CHECKED != m_VerticalCheckBox.GetCheck());
  }
  else if( item.ItemID() == m_HideTabCheckBox.ItemID())
  {
    bool bHide = BST_UNCHECKED == m_HideTabCheckBox.GetCheck();
    //CRhinoUiExpandableTabCtrl* pTabCtrl = pDlg->GetTabCtrl();
    //if( pTabCtrl)
    //{
    //  pTabCtrl->HideTab( 1, bHide);
    //}
  }
  else if( item.ItemID() == m_HasIsoCurves.ItemID())
  {
    bool bEnable = BST_UNCHECKED != m_HasIsoCurves.GetCheck();
    m_ShowIsoCurves.SetIsEnabled( bEnable);
    m_IsoCurveDinsity.SetIsEnabled( bEnable);
    RedrawItem( ItemIndex( m_ShowIsoCurves));
    RedrawItem( m_IsoCurveDinsity);
  }
  return true;
}

bool CTestListCtrl::OnComboBoxPopulated( CRhinoUiOptionsListCtrlComboBox& item)
{
  CRhinoUiOptionsListCtrl::OnComboBoxPopulated( item);

  int cnt = item.GetCount();
  if( cnt < 1)
    return false; // Nothing added
  // Current item text
  CString sText = item.Text();
  // place holder for new text
  CString s;
  // current selection index
  int iCurSel = -1;
  // process combo box for string that matches sText
  for( int i = 0; i < cnt; i++)
  {
    item.GetLBText( i, s);
    if( 0 == sText.CompareNoCase( s))
      iCurSel = i;
  }
  // Set current selection to matching string
  item.SetCurSel( iCurSel);
  return( cnt > 0);
}

bool CTestListCtrl::PopulateItemComboBox( CRhinoUiOptionsListCtrlComboBox& item)
{
  CRhinoUiOptionsListCtrl::PopulateItemComboBox( item);

  CTestOptionsListCtrlDialog* pDlg = static_cast<CTestOptionsListCtrlDialog*>( GetParent());
  // Compare item to layer and color items
  if( &item == pDlg->m_pLayerItem)
  {
    int break_here = 0;
    break_here++;
  }
  else if( &item == pDlg->m_pColorItem)
  {
  }

  return true;
}

void CTestListCtrl::OnItemComboBoxSelChanged( CRhinoUiOptionsListCtrlComboBox& item)
{
  CRhinoUiOptionsListCtrl::OnItemComboBoxSelChanged( item);
  int iCurSel = item.GetCurSel();
  if( iCurSel < 0)
    return;
  // TODO: the combo box changed, update whatever it is connected to.
}

// CTestOptionsListCtrlDialog dialog

IMPLEMENT_SERIAL( CTestOptionsListCtrlDialog, CRhinoUiDockBarDialog, 1 )

CTestOptionsListCtrlDialog::CTestOptionsListCtrlDialog( CWnd* pParent )
: CRhinoUiDockBarDialog(CTestOptionsListCtrlDialog::IDD, pParent)
, m_pLayerItem( 0 )
, m_pColorItem( 0 )
{
}

CTestOptionsListCtrlDialog::~CTestOptionsListCtrlDialog()
{
}

void CTestOptionsListCtrlDialog::DoDataExchange(CDataExchange* pDX)
{
	CRhinoUiDockBarDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestOptionsListCtrlDialog, CRhinoUiDockBarDialog)
  ON_REGISTERED_MESSAGE( CRhinoUiOptionsListCtrl::m_custom_win_msg_id, OnRegisteredMessage)
END_MESSAGE_MAP()

// CTestOptionsListCtrlDialog message handlers

LRESULT CTestOptionsListCtrlDialog::OnRegisteredMessage( WPARAM wParam, LPARAM lParam )
{
  LPRhinoUiOptionsListCtrlNM pNM = (LPRhinoUiOptionsListCtrlNM)wParam;
  LRESULT* pResult = (LRESULT*)lParam;

  *pResult = false;

  CRhinoUiOptionsListCtrlItem* pItem = pNM->m_item;
  if( NULL == pItem )
    return 0L;

  int iItemIndex = (int)pNM->m_NMHDR.idFrom;
  UINT nNotificationCode = pNM->m_NMHDR.code;

  switch( nNotificationCode )
  {
    case CRhinoUiOptionsListCtrl::nc_on_en_change_item:
      if( pItem == &(m_options_list.m_PointEditBox) )
        TRACE( "Point value changed\n" );
      break;

    case CRhinoUiOptionsListCtrl::nc_on_item_button_clicked:
    {
      CRhinoUiOptionsListCtrlPushButton* pItemButton = static_cast<CRhinoUiOptionsListCtrlPushButton*>( pItem);
      CString s, sLabel = pItemButton->Label();
      if( sLabel.IsEmpty() )
        sLabel = L"Untitled";
      s.Format( L"Button %s clicked", sLabel );
      MessageBox( s );
    } 
    break;

    case CRhinoUiOptionsListCtrl::nc_on_item_check_box_clicked:
      if(    pItem == &m_options_list.m_ExpandCheckBox1
          || pItem == &m_options_list.m_ExpandCheckBox2
          || pItem == &m_options_list.m_ExpandCheckBox3
        )
      {
        //m_options_list.ExpandItem( pItem, BST_CHECKED == static_cast<CRhinoUiOptionsListCtrlCheckBox*>( pItem)->GetCheck());
        //m_options_list.RecalcLayout();
        //m_options_list.Invalidate();
      }
      else if( pItem == &m_options_list.m_ExpandCheckBox4 )
      {
      }
      else
      {
        if( static_cast<CRhinoUiOptionsListCtrlCheckBox*>(pItem)->GetCheck() == BST_UNCHECKED )
          pItem->SetText( L"Unchecked" );
        else
          pItem->SetText( L"Checked" );
      }
      break;

    case CRhinoUiOptionsListCtrl::nc_populate_combo_box:
      if( pItem->ItemID() == m_ComboBoxItem.ItemID() )
      {
        CString s;
        int i;
        for( i = 0; i < 10; i++ )
        {
          s.Format( L"Item %2.2d", i+1 );
          m_ComboBoxItem.AddString( s );
        }
        *pResult = m_ComboBoxItem.GetCount() > 0;
      }
      break;

    case CRhinoUiOptionsListCtrl::nc_combo_box_populated:
      if( pItem->ItemID() == m_ComboBoxItem.ItemID() )
      {
        CString s = m_ComboBoxItem.Text();
        if( !s.IsEmpty() )
          m_ComboBoxItem.SetCurSel( m_ComboBoxItem.FindString(-1, s) );
      }
      break;

    case CRhinoUiOptionsListCtrl::nc_on_combo_box_sel_changed:
    {
      CRhinoUiOptionsListCtrlComboBox* pItemComboBox = static_cast<CRhinoUiOptionsListCtrlComboBox*>(pItem);
      if( ::IsWindow( pItemComboBox->m_hWnd) )
      {
        CString s;
        pItemComboBox->GetTextFromListIndex( pItemComboBox->GetCurSel(), s );
        pItemComboBox->SetText( s );
      }
    } 
    break;

    case CRhinoUiOptionsListCtrl::nc_on_radio_button_checked:
    {
      const CRhinoUiOptionsListCtrlRadioButtonColumnBtn* pBtn = static_cast<CRhinoUiOptionsListCtrlRadioButtonColumn*>(pItem)->GetSelectedButton();
      CString s;
      if( pBtn )
        s = pBtn->ButtonLabel();
      pItem->SetText( s );
    } 
    break;

    case CRhinoUiOptionsListCtrl::nc_on_end_edit_item:
      if( pItem == &(m_options_list.m_PointEditBox) )
        TRACE( "Finshed editing point value\n");
      else
      {
        CString sLabel = pItem->Label();
        if( !sLabel.IsEmpty() )
        {
          CString s;
          s.Format( L"nc_on_end_edit_item Label(%s)", sLabel );
          //MessageBox( s);
        }
      }
      break;
  }

  return 0L;
}

void CTestOptionsListCtrlDialog::CreateGroup( 
        CRhinoUiOptionsListCtrlGroupComboBox& combo,
        const wchar_t* lpsItem,
        CRhinoUiOptionsListCtrlGroupComboBox* pNestedCombo
        )
{
  const wchar_t* text[] = { L"A", L"B" }; 
  COLORREF colors[] = { RGB(255,0,0), RGB(0,255,0) };
  const int cnt = _countof( text );
  ON_SimpleArray<CRhinoUiOptionsListCtrlItem*> items;
  items.Reserve( cnt );
  items.SetCount( 0 );
  int i;
  for( i = 0; i < cnt; i++)
  {
    //CRhinoUiOptionsListCtrlItem* p = new CRhinoUiOptionsListCtrlStaticText();
    CRhinoUiOptionsListCtrlColorButton* p = new CRhinoUiOptionsListCtrlColorButton();
    if( NULL == p )
      continue;
    items.Append( p );
    p->SetLabel( lpsItem );
    p->SetText( text[i] );
    p->SetColor( colors[i] );
    p->SetIndentLevel( combo.IndentLevel()+1 );
    //ctrl.AddItem( p );
  }
  if( items.Count() < 1 )
    return;

  if( pNestedCombo)
  {
    pNestedCombo->SetLabel( L"Nested group combo" );
    items.Append( pNestedCombo );
  }

  combo.AddGroupItem( lpsItem, items );

  if( pNestedCombo )
  {
    pNestedCombo->SetIndentLevel( combo.IndentLevel()+1 );

    pNestedCombo->AddGroupItem( L"No controls", NULL, 0 );
    CRhinoUiOptionsListCtrlColorButton* pNested = new CRhinoUiOptionsListCtrlColorButton();
    if( pNested )
    {
      pNested->SetLabel(L"Nested group item" );
      pNested->SetText( L"" );
      pNested->SetColor( 0x00000000 );
      pNested->SetIndentLevel( pNestedCombo->IndentLevel()+1 );
      CRhinoUiOptionsListCtrlItem* p = static_cast<CRhinoUiOptionsListCtrlItem*>(pNested);
      pNestedCombo->AddGroupItem( L"color button", &p, 1 );
    }
    pNestedCombo->SetCurGroupSel( 0 );
  }
}

void CTestOptionsListCtrlDialog::OnShowDockBar( bool bShowDockBar )
{
}

BOOL CTestOptionsListCtrlDialog::OnInitDialog()
{
  CRhinoUiDockBarDialog::OnInitDialog();

  CRect r;
  GetClientRect( r);

  m_options_list.SetBorders( 0, 0, 0, 0 );

  if( m_options_list.CreateOptionsList(this, WS_VISIBLE | WS_CHILD, r) )
  {
    m_options_list.SetIndentItems( true );

    m_options_list.AddItem( new CRhinoUiOptionsListCtrlStaticText(L"Object type", L"unknown type") );
    m_options_list.AddItem( new CRhinoUiOptionsListCtrlEditBox(L"Name", L"*unnamed*") );
    m_pLayerItem = new CRhinoUiOptionsListCtrlLayerComboBox( L"Layer", L"Layer 01" );
    m_options_list.AddItem( m_pLayerItem );
    m_pColorItem = new CRhinoUiOptionsListCtrlColorComboBox( L"Color", L"Black" );
    m_options_list.AddItem( m_pColorItem );
    m_options_list.AddItem( new CRhinoUiOptionsListCtrlPushButton(L"Details", L"...") );
    m_options_list.AddItem( new CRhinoUiOptionsListCtrlColorButton(L"Color button", RGB(255,0,0)) );

    m_options_list.m_HasIsoCurves.SetAutoDelete( false );
    m_options_list.m_HasIsoCurves.SetCheck( BST_CHECKED );
    m_options_list.m_HasIsoCurves.SetLabel( L"Object has Isocurves" );
    m_options_list.m_HasIsoCurves.SetText( L"True" );
    m_options_list.m_HasIsoCurves.SetCheckText( L"True" );
    m_options_list.AddItem( &m_options_list.m_HasIsoCurves );

    m_options_list.m_ShowIsoCurves.SetAutoDelete( false );
    m_options_list.m_ShowIsoCurves.SetLabel( L"Isocurves" );
    m_options_list.m_ShowIsoCurves.SetText( L"Display" );
    m_options_list.m_ShowIsoCurves.SetCheckText( L"Display" );
    m_options_list.AddItem( &m_options_list.m_ShowIsoCurves );

    m_options_list.m_IsoCurveDinsity.SetAutoDelete( false );
    m_options_list.m_IsoCurveDinsity.SetLabel( L"Isocurve density" );
    m_options_list.m_IsoCurveDinsity.SetEditType( CRhinoUiEdit::et_int );
    m_options_list.m_IsoCurveDinsity.SetText( L"1" );
    m_options_list.m_IsoCurveDinsity.SetValue( 1 );
    m_options_list.m_IsoCurveDinsity.SetMin( true, 0 );
    m_options_list.m_IsoCurveDinsity.SetMax( true, 99 );
    m_options_list.m_IsoCurveDinsity.SetAllowEmpty( false );
    m_options_list.m_IsoCurveDinsity.SetNonZero( false );
    m_options_list.m_IsoCurveDinsity.SetIncludeSpinner( true );
    m_options_list.AddItem( &m_options_list.m_IsoCurveDinsity );

    m_options_list.m_PointEditBox.SetLabel( L"Point edit test" );
    m_options_list.m_PointEditBox.SetPoint( 1.0, 2.0, 3.0 );
    m_options_list.AddItem( &m_options_list.m_PointEditBox );

    m_options_list.AddItem( new CRhinoUiOptionsListCtrlSeparator(L"This is a separator") );
    
    m_options_list.m_ExpandCheckBox1.SetLabel( L"Expandable item" );
    m_options_list.m_ExpandCheckBox1.SetText( L"One" );
    m_options_list.m_ExpandCheckBox1.SetCheckText( L"One" );
    m_options_list.m_ExpandCheckBox1.SetCheck( BST_CHECKED );
    int iCheck1 = m_options_list.AddItem( &m_options_list.m_ExpandCheckBox1 );

    int iIndent = 1;
    m_options_list.m_ExpandCheckBox2.SetLabel( L"Expandable item" );
    m_options_list.m_ExpandCheckBox2.SetText( L"Two" );
    m_options_list.m_ExpandCheckBox2.SetCheckText( L"Two" );
    m_options_list.m_ExpandCheckBox2.SetIndentLevel( iIndent++ );
    m_options_list.m_ExpandCheckBox2.SetCheck( BST_CHECKED );
    m_options_list.m_ExpandCheckBox2.SetIsFullRowItem( true );
    int iCheck2 = m_options_list.AddItem( &m_options_list.m_ExpandCheckBox2 );
    m_options_list.m_ExpandCheckBox2.SetParentIndex( iCheck1 );

    m_options_list.m_ExpandCheckBox3.SetLabel( L"Expandable item" );
    m_options_list.m_ExpandCheckBox3.SetText( L"Three" );
    m_options_list.m_ExpandCheckBox3.SetCheckText( L"Three" );
    m_options_list.m_ExpandCheckBox3.SetIndentLevel( iIndent++ );
    m_options_list.m_ExpandCheckBox3.SetCheck( BST_CHECKED );
    int iCheck3 = m_options_list.AddItem( &m_options_list.m_ExpandCheckBox3 );
    m_options_list.m_ExpandCheckBox3.SetParentIndex( iCheck2 );

    m_options_list.m_ExpandCheckBox4.SetLabel( L"Expandable item" );
    m_options_list.m_ExpandCheckBox4.SetText( L"Four" );
    m_options_list.m_ExpandCheckBox4.SetCheckText( L"Four" );
    m_options_list.m_ExpandCheckBox4.SetIndentLevel( 1 );
    m_options_list.m_ExpandCheckBox4.SetCheck( BST_CHECKED );
    m_options_list.AddItem( &m_options_list.m_ExpandCheckBox4 );
    m_options_list.m_ExpandCheckBox4.SetParentIndex( iCheck1 );

    m_options_list.m_GroupCombo.SetLabel( L"Group combo" );
    m_options_list.AddItem( &m_options_list.m_GroupCombo );
    m_options_list.m_GroupCombo.SetParentIndex( iCheck1 );
    m_options_list.m_GroupCombo.SetIndentLevel( 1 );

    m_options_list.m_GroupCombo.AddGroupItem( L"No controls", NULL, 0 );
    CreateGroup( m_options_list.m_GroupCombo, L"One", &m_options_list.m_NestedGroupCombo );
    m_options_list.m_GroupCombo.SetCurGroupSel( 0 );

    int iTestFullRow = m_options_list.AddItem( new CRhinoUiOptionsListCtrlStaticText( L"label", L"Indented, full row", 1));
    if( iTestFullRow >= 0)
    {
      CRhinoUiOptionsListCtrlStaticText* pST = static_cast<CRhinoUiOptionsListCtrlStaticText*>( m_options_list.GetItem( iTestFullRow));
      if( pST)
      {
        pST->SetParentIndex( iCheck1);
        pST->SetIndentLevel( 1);
        pST->SetIsFullRowItem( true);
        int iTestFullRowSubItem = m_options_list.AddItem( new CRhinoUiOptionsListCtrlStaticText( L"label", L"full row sub item", 1));
        if( iTestFullRowSubItem >= 0)
        {
          CRhinoUiOptionsListCtrlStaticText* pSI = static_cast<CRhinoUiOptionsListCtrlStaticText*>( m_options_list.GetItem( iTestFullRowSubItem));
          if( pSI)
          {
            pSI->SetParentIndex( iTestFullRow);
            pSI->SetIndentLevel( 2);
            pSI->SetIsFullRowItem( true);
          }
        }
      }
    }

    m_options_list.ExpandItem( iCheck1, true );
    m_options_list.ExpandItem( iCheck2, true );

    int iFullRowCheck = m_options_list.AddItem( new CRhinoUiOptionsListCtrlCheckBox( L"Full row check", L"Full row check", 1));
    if( iFullRowCheck >= 0)
    {
      CRhinoUiOptionsListCtrlItem* pI = m_options_list.GetItem( iFullRowCheck );
      if( pI)
      {
        pI->SetIsFullRowItem( true );
        static_cast<CRhinoUiOptionsListCtrlCheckBox*>(pI)->SetCheckText( L"Full row check" );
      }
    }

    m_options_list.m_VerticalCheckBox.SetAutoDelete( false );
    m_options_list.m_VerticalCheckBox.SetLabel( L"Tab Alignment" );
    m_options_list.m_VerticalCheckBox.SetText( L"Top" );
    m_options_list.m_VerticalCheckBox.SetCheckText( L"Top" );
    m_options_list.m_VerticalCheckBox.SetCheck( BST_CHECKED );
    m_options_list.m_VerticalCheckBox.SetLabelBackGroundColor( RGB(200,0,0) );
    m_options_list.m_VerticalCheckBox.SetLabelTextColor( RGB(255,255,255) );
    m_options_list.m_VerticalCheckBox.SetIndentLevel( 1 );
    //m_options_list.AddItem( &m_options_list.m_VerticalCheckBox);

    m_options_list.m_HideTabCheckBox.SetAutoDelete( false );
    m_options_list.m_HideTabCheckBox.SetLabel( L"Test Tab Three" );
    m_options_list.m_HideTabCheckBox.SetText( L"Show" );
    m_options_list.m_HideTabCheckBox.SetCheckText( L"Show" );
    m_options_list.m_HideTabCheckBox.SetCheck( BST_CHECKED );
    m_options_list.m_HideTabCheckBox.SetLabelBackGroundColor( RGB(255,0,0) );
    m_options_list.m_HideTabCheckBox.SetLabelTextColor( RGB(255,255,255) );
    m_options_list.AddItem( &m_options_list.m_HideTabCheckBox );

    m_options_list.m_IPAddress.SetAutoDelete( false );
    m_options_list.m_IPAddress.SetLabel( L"Test IP Address" );
    m_options_list.m_IPAddress.SetIPAddress( MAKEIPADDRESS(255, 255, 255, 255) );
    m_options_list.m_IPAddress.SetIsReadOnly( true );
    m_options_list.m_IPAddress.SetIndentLevel( 1 );
    m_options_list.AddItem( &m_options_list.m_IPAddress );

    m_options_list.m_RadioColumn.SetLabel( L"Radio button test" );
    m_options_list.m_RadioColumn.SetAutoDelete( false );
    m_options_list.m_RadioColumn.AddRadioButton( L"One" );
    m_options_list.m_RadioColumn.AddRadioButton( L"Two" );
    m_options_list.m_RadioColumn.AddRadioButton( L"Three" );
    m_options_list.m_RadioColumn.SetSelectedButton( 1 );
    m_options_list.m_RadioColumn.SetIndentLevel( 1 );
    m_options_list.AddItem( &m_options_list.m_RadioColumn );

    m_options_list.AddItem( new CRhinoUiOptionsListCtrlColorComboBox(L"Color combo test", L"Black", 1) );
    m_options_list.AddItem( new CRhinoUiOptionsListCtrlEditBox(L"File name test", L"C:\\Temp\\3dm\\AtoZ.jpg", 1) );
    m_options_list.AddItem( new CRhinoUiOptionsListCtrlFontComboBox(L"Font combo test", L"Arial", 1) );

    m_ComboBoxItem.SetLabel( L"Combo Box test" );
    m_ComboBoxItem.SetText( L"Item 01" );
    m_ComboBoxItem.SetAutoDelete( false );
    m_ComboBoxItem.SetIndentLevel( 1 );
    m_options_list.AddItem( &m_ComboBoxItem );

    CRect rBefore;
    m_options_list.GetWindowRect( rBefore );
    m_options_list.SizeToContent( true );
    
    CRect rAfter;
    m_options_list.GetWindowRect( rAfter );
    
    CRect r;
    GetWindowRect( r );
    if( rAfter.Height() != rBefore.Height() )
      SetWindowPos( NULL, 0, 0, r.Width(), r.Height() + (rAfter.Height() - rBefore.Height()), SWP_NOZORDER|SWP_NOMOVE );

    m_Resize.Add( &m_options_list, CRhinoUiDialogItemResizer::resize_lockall );
  }

  return TRUE;
}
