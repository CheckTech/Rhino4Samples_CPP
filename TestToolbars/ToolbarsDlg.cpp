// ToolbarsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ToolbarsDlg.h"


// CToolbarsDlg dialog

IMPLEMENT_DYNAMIC(CToolbarsDlg, CRhinoDialog)

CToolbarsDlg::CToolbarsDlg( const wchar_t* lpsCollectionFileName, CWnd* pParent /*=NULL*/)
: CRhinoDialog(CToolbarsDlg::IDD, pParent)
, m_wCollectionFileName( lpsCollectionFileName)
{

}

CToolbarsDlg::~CToolbarsDlg()
{
}

void CToolbarsDlg::DoDataExchange(CDataExchange* pDX)
{
  CRhinoDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_S_FILENAME, m_StaticFileName);
  DDX_Control(pDX, IDC_L_TOOLBARS, m_ToolBarsListBox);
}


BEGIN_MESSAGE_MAP(CToolbarsDlg, CRhinoDialog)
  ON_CONTROL( CLBN_CHKCHANGE, IDC_L_TOOLBARS, OnChkChange)
END_MESSAGE_MAP()


// CToolbarsDlg message handlers

BOOL CToolbarsDlg::OnInitDialog()
{
  AddResizeControl( true );
  EnableSaveDialogPositionAndSize( true );
  SetMinSizeToCurrentSize();

  m_Resize.Add( IDC_S_FILENAME, CRhinoUiDialogItemResizer::resize_lockwidth);
  m_Resize.Add( IDC_L_TOOLBARS, CRhinoUiDialogItemResizer::resize_lockall);
  m_Resize.Add( IDOK, CRhinoUiDialogItemResizer::resize_lockbottomright);

  CRhinoDialog::OnInitDialog();

  m_StaticFileName.SetTextIsFilePath( true);
  SetDlgItemText( IDC_S_FILENAME, m_wCollectionFileName);

  const CRhinoUiToolBarCollection* pC = RhinoApp().RhinoUiToolBarManager().Collection( m_wCollectionFileName, false);
  CString sName;
  // Put toolbar names in list box
  for( int i = 0; pC && i < pC->ToolBarCount(); i++)
  {
    const CRhinoUiToolBar* pTB = pC->ToolBar( i);
    if( NULL == pTB)
      continue;
    sName = pTB->Name();
    if( sName.IsEmpty())
      continue;
    int iIndex = m_ToolBarsListBox.AddString( sName);
    if( iIndex < 0)
      continue;
    m_ToolBarsListBox.SetItemDataPtr( iIndex, (LPVOID)pTB);
    m_ToolBarsListBox.SetCheck( iIndex, pTB->IsToolBarVisible() ? BST_CHECKED : BST_UNCHECKED);
  }

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CToolbarsDlg::OnChkChange() 
{
  CRhinoUiToolBarManager& tbm = RhinoApp().RhinoUiToolBarManager();
  for( int i = 0, cnt = m_ToolBarsListBox.GetCount(); i < cnt; i++)
  {
    const CRhinoUiToolBar* pTB = static_cast<const CRhinoUiToolBar*>( m_ToolBarsListBox.GetItemDataPtr( i));
    if( NULL == pTB)
      continue;
    bool bChecked = (m_ToolBarsListBox.GetCheck( i) == BST_CHECKED);
    if( pTB->IsToolBarVisible() != bChecked)
      tbm.ShowToolBar( pTB, bChecked, true);
  }
} 
