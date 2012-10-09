// Dialog1.cpp : implementation file
//

#include "stdafx.h"
#include "Dialog1.h"

// CDialog1ListCtrl control

IMPLEMENT_DYNAMIC(CDialog1ListCtrl, CRhinoUiGridListCtrl)

CDialog1ListCtrl::CDialog1ListCtrl( CRhinoDoc& doc)
: m_doc( doc)
{
}

CDialog1ListCtrl::~CDialog1ListCtrl()
{
}

BEGIN_MESSAGE_MAP(CDialog1ListCtrl, CRhinoUiGridListCtrl)
END_MESSAGE_MAP()

BOOL CDialog1ListCtrl::DoneEditing( long nItem, int nSubItem, LPCTSTR lpszText)
{
  const CRhinoLayer* pL = (const CRhinoLayer*)GetItemData( nItem);

  if( pL)
  {
    ON_wString w = lpszText;
    if( nSubItem == 0)
    {
      if( w.IsEmpty())
      {
        MessageBox( L"Layer name can not be blank");
        return false;
      }
      if( 0 == m_wOriginalString.Compare( w)) // case sensitive compare
        return true; // Name unchanged
      if( m_wOriginalString.CompareNoCase( w))
      {
        // Something besides the case of the name has changed so make sure the
        // new name is not currently in use
        if( m_doc.m_layer_table.FindLayer( w) >= 0)
        {
          MessageBox( L"Layer name is allready in use, please choose another name");
          return false;
        }
      }
      ON_Layer l = *pL;
      if( l.SetLayerName( w) && m_doc.m_layer_table.ModifyLayer( l, pL->LayerIndex(), false))
      {
        SetItemText( nItem, nSubItem, l.LayerName());
        return true;
      }
      return false;
    }
    else if( nSubItem == 1 && !w.IsEmpty())
    {
      ON_Layer l = *pL;
      if( 0 == w.CompareNoCase( L"Locked"))
      {
        l.SetVisible( true);
        l.SetLocked( true);
      }
      else if( 0 == w.CompareNoCase( L"Off"))
      {
        l.SetVisible( false);
      }
      else
      {
        w = L"On";
        l.SetVisible( true);
        l.SetLocked( false);
      }
      if(  m_doc.m_layer_table.ModifyLayer( l, pL->LayerIndex(), false))
      {
        m_doc.Redraw();
        SetItemText( nItem, nSubItem, w);
        return true;
      }
      return false;
    }
  }
  return __super::DoneEditing( nItem, nSubItem, lpszText);
}

BOOL CDialog1ListCtrl::ModifyGridItem( long nItem, int nSubItem)
{
  m_wOriginalString.Empty();
  const CRhinoLayer* pL = (const CRhinoLayer*)GetItemData( nItem);
  if( pL)
  {
    if( nSubItem == 0)
    {
      m_wOriginalString = pL->LayerName();
      return EditGridItem( nItem, nSubItem);
    }
    else if( nSubItem == 1)
    {
      CStringList strings;
      strings.AddTail( L"On");
      strings.AddTail( L"Off");
      strings.AddTail( L"Locked");
      int iCurSel = 0;
      if( pL->IsLocked() && pL->IsVisible())
        iCurSel = 2;
      else if( pL->IsVisible())
        iCurSel = 0;
      else
        iCurSel = 1;
      return( NULL != ListGridItem( nItem, nSubItem, strings, iCurSel));
    }
  }
  return __super::ModifyGridItem( nItem, nSubItem);
}

// CDialog1 dialog

IMPLEMENT_DYNAMIC(CDialog1, CRhinoDialog)

CDialog1::CDialog1( CRhinoDoc& doc, CWnd* pParent /*=NULL*/)
: CRhinoDialog(CDialog1::IDD, pParent)
, m_doc( doc)
, m_ListCtrl( doc)
{

}

CDialog1::~CDialog1()
{
}

void CDialog1::DoDataExchange(CDataExchange* pDX)
{
  CRhinoDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDialog1, CRhinoDialog)
END_MESSAGE_MAP()


// CDialog1 message handlers

BOOL CDialog1::OnInitDialog()
{
  AddResizeControl( true);
  SetMinSizeToCurrentSize();
  EnableSaveDialogPositionAndSize( true);

  m_Resize.Add( IDC_LIST1, CRhinoUiDialogItemResizer::resize_lockall);
  m_Resize.Add( IDOK, CRhinoUiDialogItemResizer::resize_lockbottomright);

  CDialog::OnInitDialog();

  m_ListCtrl.Setup( true);

  int iCol = 0;
  m_ListCtrl.InsertColumn( iCol++, L"Name");
  m_ListCtrl.InsertColumn( iCol++, L"Visible");

  m_ListCtrl.DisableColumnResizing( 1);

  CRect rLC;
  m_ListCtrl.GetClientRect( rLC);

  const int cxState = 80;

  m_ListCtrl.SetColumnWidth( 0, rLC.Width() - cxState);
  m_ListCtrl.SetColumnWidth( 1, cxState);

  ON_SimpleArray<const CRhinoLayer*>layers;
  m_doc.m_layer_table.GetSortedList( layers);
  if( layers.Count() < 1)
  {
    for( int i = 0; i < m_doc.m_layer_table.LayerCount(); i++)
    {
      const CRhinoLayer& l = m_doc.m_layer_table[i];
      if( !l.IsDeleted() && !l.IsReference())
        layers.Append( &l);
    }
  }

  for( int i = 0, j = 0; i < layers.Count(); i++)
  {
    const CRhinoLayer* pL = layers[i];
    if( pL)
    {
      int x = m_ListCtrl.InsertItem( j++, pL->LayerName());
      if( x >= 0)
      {
        m_ListCtrl.SetItemData( x, (DWORD_PTR)pL);
        if( pL->IsLocked() && pL->IsVisible())
          m_ListCtrl.SetItemText( x, 1, L"Locked");
        else if( pL->IsVisible())
          m_ListCtrl.SetItemText( x, 1, L"On");
        else
          m_ListCtrl.SetItemText( x, 1, L"Off");
      }
    }
  }

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}
