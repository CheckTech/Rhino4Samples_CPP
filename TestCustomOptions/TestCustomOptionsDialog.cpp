////////////////////////////////////////////////////////////////////////////////////
// TestCustomOptionsDockBar.cpp

#include "stdafx.h"
#include "TestCustomOptionsDialog.h"

#define CHECK_SPACE 10
#define CHEVRON_OFFSET 19

////////////////////////////////////////////////////////////////////////////////////
// CMyOptionsListCtrlSeparator

CMyOptionsListCtrlSeparator::CMyOptionsListCtrlSeparator(LPCTSTR lpsLabel, int iIndentLevel)
:	CRhinoUiOptionsListCtrlSeparator(lpsLabel, iIndentLevel)
, m_bChecked(true)
{
}

void CMyOptionsListCtrlSeparator::OnDrawItem( CDC& dc, const CRect& rItem, const CRect& rDeflate) const
{
	if( 0 == GetListCtrl() )
		return;

	// The rect that comes in is invalid because of the calling code.  
  // However, it is set to the right of the area, so we just need
  // to re-expand it enough to be able to draw the chevon
	CRect r = rItem;
	r.left = r.right - CHECK_SPACE;
	r.top += rDeflate.Height() + 2;

	if( r.Height() < 1 || r.Width() < 1)
		return;

	if( IsEnabled() && GetListCtrl()->IsWindowEnabled() )
	{
		// Draw chevrons
		const COLORREF colChev = LabelTextColor();
		CPen penChev( PS_SOLID, 1, colChev );
		CPen* pOldPen = dc.SelectObject( &penChev );

		const int iChevX = r.right - CHEVRON_OFFSET;
		const int iChevY = r.top + ( m_bChecked ? 12 : 5 );
		const int iDeltaY = m_bChecked ? -1 : +1;

    for( int c = 0; c < 2; c++ )
		{
			const int y = c * iDeltaY * 5;
			for( int x = 0; x < 2; x++ )
			{
				dc.MoveTo( x + iChevX,     y + iChevY );
				dc.LineTo( x + iChevX + 3, y + iChevY + iDeltaY * 3 );
				dc.LineTo( x + iChevX + 7, y + iChevY - iDeltaY );
			}
		}

		dc.SetPixel( iChevX,     iChevY + iDeltaY * 4, colChev );
		dc.SetPixel( iChevX + 7, iChevY + iDeltaY * 4, colChev );
		dc.SelectObject( pOldPen );
	}

	__super::OnDrawItem( dc, rItem, rDeflate );
}

bool CMyOptionsListCtrlSeparator::Checked() const
{ 
  return m_bChecked; 
}

void CMyOptionsListCtrlSeparator::SetChecked(bool bChecked)
{
	m_bChecked = bChecked;
}

////////////////////////////////////////////////////////////////////////////////////
// CTestCustomOptionsDialog

IMPLEMENT_SERIAL( CTestCustomOptionsDialog, CRhinoUiDockBarDialog, 1 )

CTestCustomOptionsDialog::CTestCustomOptionsDialog(CWnd* pParent)
: CRhinoUiDockBarDialog(CTestCustomOptionsDialog::IDD, pParent)
{
}

CTestCustomOptionsDialog::~CTestCustomOptionsDialog()
{
}

void CTestCustomOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CRhinoUiDockBarDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestCustomOptionsDialog, CRhinoUiDockBarDialog)
	ON_REGISTERED_MESSAGE(CRhinoUiOptionsListCtrl::m_custom_win_msg_id, OnOptionsListCtrl)
END_MESSAGE_MAP()

// CTestCustomOptionsDialog message handlers

BOOL CTestCustomOptionsDialog::OnInitDialog()
{
  CRhinoUiDockBarDialog::OnInitDialog();

	m_list.SetIndentItems(true);
	m_list.SetBorders(0, 0, 0, 0);

	CWnd* pWnd = GetDlgItem( IDC_FRAME );

	CRect rect;
	GetDlgItemRect( IDC_FRAME, rect );
	if( !m_list.CreateOptionsList(this, pWnd->GetStyle(), rect, IDC_FRAME) )
		return FALSE;

	pWnd->DestroyWindow();

  // General

	m_static_general.SetIndentLevel( 0 );
	m_static_general.SetDrawSeparatorLine( true );
	m_static_general.SetAutoDelete( false );
	m_static_general.SetLabel( L"General" );
	m_list.AddItem( &m_static_general );

  m_edit_name.SetIndentLevel( 1 );
	m_edit_name.SetAutoDelete( false );
	m_edit_name.SetLabel( L"General" );
	m_list.AddItem( &m_edit_name );

  // Position
	m_static_position.SetIndentLevel( 0 );
	m_static_position.SetDrawSeparatorLine( true );
	m_static_position.SetAutoDelete( false );
	m_static_position.SetLabel( L"Position" );
	m_list.AddItem( &m_static_position );

  m_edit_position_x.SetIndentLevel( 1 );
	m_edit_position_x.SetAutoDelete( false );
	m_edit_position_x.SetLabel( L"X Position" );
	m_list.AddItem( &m_edit_position_x );

  m_edit_position_y.SetIndentLevel( 1 );
	m_edit_position_y.SetAutoDelete( false );
	m_edit_position_y.SetLabel( L"Y Position" );
	m_list.AddItem( &m_edit_position_y );

  m_edit_position_z.SetIndentLevel( 1 );
	m_edit_position_z.SetAutoDelete( false );
	m_edit_position_z.SetLabel( L"Z Position" );
	m_list.AddItem( &m_edit_position_z );

  // Rotation
	m_static_rotation.SetIndentLevel( 0 );
	m_static_rotation.SetDrawSeparatorLine( true );
	m_static_rotation.SetAutoDelete( false );
	m_static_rotation.SetLabel( L"Rotation" );
	m_list.AddItem( &m_static_rotation );

  m_edit_rotation_x.SetIndentLevel( 1 );
	m_edit_rotation_x.SetAutoDelete( false );
	m_edit_rotation_x.SetLabel( L"X Rotation" );
	m_list.AddItem( &m_edit_rotation_x );

  m_edit_rotation_y.SetIndentLevel( 1 );
	m_edit_rotation_y.SetAutoDelete( false );
	m_edit_rotation_y.SetLabel( L"Y Rotation" );
	m_list.AddItem( &m_edit_rotation_y );

  m_edit_rotation_z.SetIndentLevel( 1 );
	m_edit_rotation_z.SetAutoDelete( false );
	m_edit_rotation_z.SetLabel( L"Z Rotation" );
	m_list.AddItem( &m_edit_rotation_z );

  // Size
	m_static_size.SetIndentLevel( 0 );
	m_static_size.SetDrawSeparatorLine( true );
	m_static_size.SetAutoDelete( false );
	m_static_size.SetLabel( L"Size" );
	m_list.AddItem( &m_static_size );

  m_edit_size_x.SetIndentLevel( 1 );
	m_edit_size_x.SetAutoDelete( false );
	m_edit_size_x.SetLabel( L"X Size" );
	m_list.AddItem( &m_edit_size_x );

  m_edit_size_y.SetIndentLevel( 1 );
	m_edit_size_y.SetAutoDelete( false );
	m_edit_size_y.SetLabel( L"Y Size" );
	m_list.AddItem( &m_edit_size_y );

  m_edit_size_z.SetIndentLevel( 1 );
	m_edit_size_z.SetAutoDelete( false );
	m_edit_size_z.SetLabel( L"Z Size" );
	m_list.AddItem( &m_edit_size_z );

	// Here, I would probably read some boolean values from the registry
  // which indicated the open/close state of the expandable/collapsable separators.
  // In this example, we'll just set manually
	m_static_position.SetChecked( true );
	m_static_rotation.SetChecked( false );
	m_static_size.SetChecked( true );

  SetListControlPositions();
	EnableDisableControls();

  return TRUE;
}

void CTestCustomOptionsDialog::OnShowDockBar( bool bShowDockBar )
{
}

void CTestCustomOptionsDialog::SetListControlPositions()
{
	int cy = 0;
	for( int i = 0; i < m_list.GetItemCount(); i++ )
	{
		CRhinoUiOptionsListCtrlItem* pItem = m_list.GetItem(i);
		if( pItem )
			cy += pItem->ItemHeight();
	}

	if( cy > 0 )
	{
		const CRect rBorders = m_list.Borders();
		cy += rBorders.top  + rBorders.bottom;

		CRect rC, rW;
		m_list.GetWindowRect( rW );
		m_list.GetClientRect( rC );

		const int cyWinBorder = rW.Height() - rC.Height();
		if( cyWinBorder > 0 )
			cy += cyWinBorder;

		if( rW.Height() != cy )
		{
			const int iGrowBy = cy - rW.Height();
			CRect rDlg;
			GetWindowRect( rDlg );
			SetWindowPos( 0, 0, 0, rDlg.Width(), rDlg.Height() + iGrowBy, SWP_NOMOVE | SWP_NOZORDER );
			m_list.SetWindowPos( 0, 0, 0, rW.Width(), cy, SWP_NOMOVE | SWP_NOZORDER );

      CWnd* pWnd = 0;
			for( pWnd = GetTopWindow(); 0 != pWnd; pWnd = pWnd->GetNextWindow() )
			{
				CRect r;
				pWnd->GetWindowRect( r );
				if( (r.top <= rW.top) || (pWnd == &m_list) )
					continue;

				ScreenToClient( r );
				pWnd->SetWindowPos( 0, r.left, r.top + iGrowBy, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
			}
		}
	}
}

LRESULT CTestCustomOptionsDialog::OnOptionsListCtrl( WPARAM wParam, LPARAM lParam )
{
	LPRhinoUiOptionsListCtrlNM pNM = (LPRhinoUiOptionsListCtrlNM)wParam;
	LRESULT* pResult = (LRESULT*)lParam;
	*pResult = 0;

	CRhinoUiOptionsListCtrlItem* pItem = pNM->m_item;
	if( 0 == pItem )
		return 0;

	if( CRhinoUiOptionsListCtrl::nc_on_separator_clicked == pNM->m_NMHDR.code )
	{
		if( pItem == static_cast<CRhinoUiOptionsListCtrlItem*>(&m_static_position) )
			m_static_position.SetChecked( !m_static_position.Checked() );
		else if (pItem == static_cast<CRhinoUiOptionsListCtrlItem*>(&m_static_rotation))
			m_static_rotation.SetChecked( !m_static_rotation.Checked() );
		else if (pItem == static_cast<CRhinoUiOptionsListCtrlItem*>(&m_static_size))
			m_static_size.SetChecked( !m_static_size.Checked() );
		else
			return 0L;

		EnableDisableControls();
	}

	return *pResult;
}

void CTestCustomOptionsDialog::EnableDisableControls()
{
	const bool bP = m_static_position.Checked();
	const bool bR = m_static_rotation.Checked();
	const bool bS = m_static_size.Checked();

	m_edit_position_x.SetItemState( CRhinoUiOptionsListCtrlItem::hidden_state, !bP );
	m_edit_position_y.SetItemState( CRhinoUiOptionsListCtrlItem::hidden_state, !bP );
	m_edit_position_z.SetItemState( CRhinoUiOptionsListCtrlItem::hidden_state, !bP );

	m_edit_rotation_x.SetItemState( CRhinoUiOptionsListCtrlItem::hidden_state, !bR );
	m_edit_rotation_y.SetItemState( CRhinoUiOptionsListCtrlItem::hidden_state, !bR );
	m_edit_rotation_z.SetItemState( CRhinoUiOptionsListCtrlItem::hidden_state, !bR );

	m_edit_size_x.SetItemState( CRhinoUiOptionsListCtrlItem::hidden_state, !bS );
	m_edit_size_y.SetItemState( CRhinoUiOptionsListCtrlItem::hidden_state, !bS );
	m_edit_size_z.SetItemState( CRhinoUiOptionsListCtrlItem::hidden_state, !bS );

	m_list.SizeToContent( true );
	m_list.Invalidate();
}
