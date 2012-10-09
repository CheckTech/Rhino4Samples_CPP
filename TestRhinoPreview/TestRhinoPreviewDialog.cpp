/////////////////////////////////////////////////////////////////////////////
// TestRhinoPreviewDialog.cpp

#include "stdafx.h"
#include "TestRhinoPreviewDialog.h"

IMPLEMENT_DYNAMIC(CTestRhinoPreviewDialog, CRhinoDialog)

CTestRhinoPreviewDialog::CTestRhinoPreviewDialog(CWnd* pParent /*=NULL*/)
: CRhinoDialog(CTestRhinoPreviewDialog::IDD, pParent)
{
}

CTestRhinoPreviewDialog::~CTestRhinoPreviewDialog()
{
}

void CTestRhinoPreviewDialog::DoDataExchange(CDataExchange* pDX)
{
	CRhinoDialog::DoDataExchange(pDX);
 	DDX_Control( pDX, IDC_PREVIEW_EDIT, m_edit );
	DDX_Control( pDX, IDC_PREVIEW_BUTTON, m_button );
  DDX_Control( pDX, IDC_PREVIEW_STATIC, m_preview );
}

BEGIN_MESSAGE_MAP(CTestRhinoPreviewDialog, CRhinoDialog)
  ON_BN_CLICKED(IDC_PREVIEW_BUTTON, &CTestRhinoPreviewDialog::OnPreviewButtonClick)
END_MESSAGE_MAP()

BOOL CTestRhinoPreviewDialog::OnInitDialog()
{
  EnableSaveDialogPositionAndSize( true );
  SetMinSizeToCurrentSize();

  m_Resize.Add( IDC_PREVIEW_EDIT, CRhinoUiDialogItemResizer::resize_lockleft|CRhinoUiDialogItemResizer::resize_lockright );
  m_Resize.Add( IDC_PREVIEW_BUTTON, CRhinoUiDialogItemResizer::resize_lockright );
  m_Resize.Add( IDC_PREVIEW_STATIC, CRhinoUiDialogItemResizer::resize_lockall );
  m_Resize.Add( IDOK, CRhinoUiDialogItemResizer::resize_lockbottom );

  CRhinoDialog::OnInitDialog();

  m_edit.SetWindowText( L"<filename>" );

  return TRUE;
}

void CTestRhinoPreviewDialog::OnPreviewButtonClick()
{
  CRhinoGetFileDialog dialog;
  dialog.SetScriptMode( FALSE );
  BOOL rc = dialog.DisplayFileDialog( CRhinoGetFileDialog::open_rhino_only_dialog, m_filename );
  if( rc )
  {
    ON_wString filename = dialog.FileName();
    if( m_preview.UpdateDib(filename) )
    {
      m_filename = filename;
      m_edit.SetWindowText( m_filename );
    }
    else
    {
      m_edit.SetWindowText( L"<filename>" );
    }
  }
}
