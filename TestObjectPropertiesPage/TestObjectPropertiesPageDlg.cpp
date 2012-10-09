/////////////////////////////////////////////////////////////////////////////
// TestObjectPropertiesPageDlg.cpp

#include "StdAfx.h"
#include "TestObjectPropertiesPageApp.h"
#include "TestObjectPropertiesPageDlg.h"

CTestObjectPropertiesPageDlg::CTestObjectPropertiesPageDlg( UINT nID, CWnd* pParent )
: CRhinoObjectPropertiesDialogPage( nID, pParent ),
  m_bVaries(false)
{
}

void CTestObjectPropertiesPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CRhinoObjectPropertiesDialogPage::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_S_HYPERLINK, m_separator);
	DDX_Control(pDX, IDC_E_HYPERLINK, m_edit);
	DDX_Control(pDX, IDC_B_TEST, m_button);
}

BEGIN_MESSAGE_MAP(CTestObjectPropertiesPageDlg, CRhinoObjectPropertiesDialogPage)
	ON_EN_CHANGE(IDC_E_HYPERLINK, OnEditChange)
	ON_EN_KILLFOCUS(IDC_E_HYPERLINK, OnEditKillFocus)
	ON_BN_CLICKED(IDC_B_TEST, OnButton)
END_MESSAGE_MAP()

CRhinoObjectPropertiesDialogPage::page_type CTestObjectPropertiesPageDlg::PageType() const
{
  return CRhinoObjectPropertiesDialogPage::custom_page;
}

void CTestObjectPropertiesPageDlg::InitControls( const CRhinoObject* new_obj )
{
  // Initialize the dialog's controls here.

  if( !::IsWindow(m_hWnd) )
    return;

  const int count = SelectedObjectCount();
  if( count == 0 )
  {
    m_edit.SetWindowText( L"" );
    m_button.EnableWindow( FALSE );
    return;
  }

  m_bVaries = false;

  ON_wString hyperlink;
  const CRhinoObject* obj = GetSelectedObject(0);
  if( obj )
  {
    hyperlink = obj->Attributes().m_url;
    hyperlink.TrimLeftAndRight();
  }

  int i;
  for( i = 1; i < count; i++ )
  {
    obj = GetSelectedObject(i);
    if( obj )
    {
      ON_wString str = obj->Attributes().m_url;
      str.TrimLeftAndRight();
      if( hyperlink.CompareNoCase(str) != 0 )
      {
        m_bVaries = TRUE;
        break;
      }
    }
  }

  if( m_bVaries )
  {
    m_hyperlink = L"varies";
    m_edit.SetWindowText( m_hyperlink );
    m_button.EnableWindow( FALSE );
  }
  else if( hyperlink.IsEmpty() )
  {
    m_hyperlink = L"";
    m_edit.SetWindowText( m_hyperlink );
    m_button.EnableWindow( FALSE );
  }
  else
  {
    m_hyperlink = hyperlink;
    m_edit.SetWindowText( m_hyperlink );
    m_button.EnableWindow( TRUE );
  }
}

void CTestObjectPropertiesPageDlg::InitControls( ON_SimpleArray<const CRhinoObject*>& objects )
{
  // This is called by the scriptable version - RunScript().
  const int count = objects.Count();
  if( count == 0 )
    return;

  m_bVaries = false;

  ON_wString hyperlink;
  const CRhinoObject* obj = GetSelectedObject(0);
  if( obj )
  {
    hyperlink = obj->Attributes().m_url;
    hyperlink.TrimLeftAndRight();
  }

  int i;
  for( i = 1; i < count; i++ )
  {
    obj = GetSelectedObject(i);
    if( obj )
    {
      ON_wString str = obj->Attributes().m_url;
      str.TrimLeftAndRight();
      if( hyperlink.CompareNoCase(str) != 0 )
      {
        m_bVaries = TRUE;
        break;
      }
    }
  }

  if( m_bVaries )
    m_hyperlink = L"varies";
  else if( hyperlink.IsEmpty() )
    m_hyperlink = L"";
  else
    m_hyperlink = hyperlink;
}

BOOL CTestObjectPropertiesPageDlg::AddPageToControlBar( const CRhinoObject* obj ) const
{
  // Here is where we test whether or not we need to add our page
  // to the object properties window based on test object.
  // In this simple example, we will always return true.

  BOOL rc = FALSE;
  if( obj )
  { 
    // Test this object
    rc =  TRUE;
  }
  else
  { 
    // Test all selected objects
    const int count = SelectedObjectCount();
    int i;
    for( i = 0; i < count; i++ )
    {
      rc = TRUE;
    }
  }
  return rc;
}

void CTestObjectPropertiesPageDlg::OnModifyObjectAttributes( CRhinoDoc& doc, CRhinoObject& object, const CRhinoObjectAttributes& old_attributes )
{
  InitControls();
}


CRhinoCommand::result CTestObjectPropertiesPageDlg::RunScript( ON_SimpleArray<const CRhinoObject*>& objects )
{
  // Scriptable version of our dialog box is handled here.

  if( 0 == objects.Count() )
    return CRhinoCommand::nothing;

  InitControls( objects );

  CRhinoGetString gs;
  gs.SetCommandPrompt( L"Hyperlink" );
  gs.SetDefaultString( m_hyperlink );
  gs.AcceptNothing();
  CRhinoGet::result res = gs.GetString();
  if( res == CRhinoGet::cancel )
    return CRhinoCommand::cancel;
  else if( res == CRhinoGet::nothing )
    return CRhinoCommand::nothing;
  else if( res != CRhinoGet::string )
    return CRhinoCommand::failure;

  ON_wString hyperlink = gs.String();
  hyperlink.TrimLeftAndRight();
  if( m_hyperlink.CompareNoCase(hyperlink) == 0 )
    return CRhinoCommand::nothing;

  ModifyObjectList( objects, hyperlink );

  return CRhinoCommand::success;
}

BOOL CTestObjectPropertiesPageDlg::OnInitDialog() 
{
  m_Resize.Add( IDC_S_HYPERLINK, CRhinoUiDialogItemResizer::resize_lockleft | CRhinoUiDialogItemResizer::resize_lockright );
  m_Resize.Add( IDC_E_HYPERLINK, CRhinoUiDialogItemResizer::resize_lockleft | CRhinoUiDialogItemResizer::resize_lockright );

	CRhinoObjectPropertiesDialogPage::OnInitDialog();
	
	return TRUE;
}

void CTestObjectPropertiesPageDlg::OnEditChange() 
{
  CString str;
  m_edit.GetWindowText( str );
  
  str.TrimLeft();
  str.TrimRight();
  
  if( str.IsEmpty() )
    m_button.EnableWindow( FALSE );
  else if( str.CompareNoCase(L"varies") == 0 )
    m_button.EnableWindow( FALSE );
  else
    m_button.EnableWindow( TRUE );
}

void CTestObjectPropertiesPageDlg::OnButton() 
{
  CString str;
  m_edit.GetWindowText( str );

  str.TrimLeft();
  str.TrimRight();
  
  if( str.IsEmpty() )
    return;

  if( str.CompareNoCase(L"varies") == 0 )
    return;

  ::ShellExecute( RhinoApp().MainWnd(), L"open", str, NULL, NULL, SW_SHOWNORMAL );
}

void CTestObjectPropertiesPageDlg::OnEditKillFocus() 
{
  CString str;
  m_edit.GetWindowText( str );

  str.TrimLeft();
  str.TrimRight();

  if( m_hyperlink.CompareNoCase(str) == 0 )
    return;

  ModifyObjectList( str );
}

void CTestObjectPropertiesPageDlg::ModifyObjectList( const wchar_t* hyperlink )
{
  const int count = SelectedObjectCount();
  if( count == 0 )
    return;

  ON_SimpleArray<const CRhinoObject*> objects;
  objects.Reserve( count );

  int i;
  for( i = 0; i < count; i++ )
    objects.Append( GetSelectedObject(i) );

  ModifyObjectList( objects, hyperlink );
}

void CTestObjectPropertiesPageDlg::ModifyObjectList( ON_SimpleArray<const CRhinoObject*>& objects, const wchar_t* hyperlink )
{
  const int count = objects.Count();
  if( count == 0 )
    return;

  m_hyperlink = hyperlink;
  m_bVaries = FALSE;

  bool bRecordUndo = false;
  CRhinoDoc* doc = RhinoApp().ActiveDoc();
  if( doc )
    bRecordUndo = doc->BeginUndoRecord( L"Object Properties change" );

  int i;
  for( i = 0; i < count; i++ )
  {
    const CRhinoObject* obj = objects[i];
    if( obj )
    {
      ON_3dmObjectAttributes attrib = obj->Attributes();
      attrib.m_url = hyperlink;
      doc->ModifyObjectAttributes( CRhinoObjRef(obj), attrib, false );
    }
  }

  if( bRecordUndo )
    doc->EndUndoRecord();
}

void CTestObjectPropertiesPageDlg::RhinoDeleteThisPage()
{
  // This member is called when the dialog is about to be destroyed,
  // but the page was never been created. If this is the case, then
  // PostNcDestroy() will never get called. Thus, we are responsible 
  // for making sure that the dialog that we "new-ed" up in our plug-in's 
  // AddPagesToObjectPropertiesDialog() member is deleted.
  delete this;
}

void CTestObjectPropertiesPageDlg::PostNcDestroy()
{
  CRhinoObjectPropertiesDialogPage::PostNcDestroy();
  // No need to do anyting here, RhinoDeleteThisPage() will get called
  // by the dialog that owns this page.
}