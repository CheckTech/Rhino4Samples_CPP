/////////////////////////////////////////////////////////////////////////////
// TestObjectPropertiesPagePlugIn.cpp

#include "StdAfx.h"
#include "Resource.h"
#include "TestObjectPropertiesPagePlugIn.h"
#include "TestObjectPropertiesPageDlg.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
// TODO: fill in the following developer declarations 
// with your company information.
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

// The one and only CTestObjectPropertiesPagePlugIn object
static CTestObjectPropertiesPagePlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestObjectPropertiesPagePlugIn definition

CTestObjectPropertiesPagePlugIn& TestObjectPropertiesPagePlugIn()
{ 
  return thePlugIn; 
}

CTestObjectPropertiesPagePlugIn::CTestObjectPropertiesPagePlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestObjectPropertiesPagePlugIn::~CTestObjectPropertiesPagePlugIn()
{
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestObjectPropertiesPagePlugIn::PlugInName() const
{
  return L"TestObjectPropertiesPage";
}

const wchar_t* CTestObjectPropertiesPagePlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestObjectPropertiesPagePlugIn::PlugInID() const
{
  // {723F9D0B-39DC-42E2-A04D-7AE1BE1DFF8B}
  static const GUID TestObjectPropertiesPagePlugIn_UUID =
  { 0x723F9D0B, 0x39DC, 0x42E2, { 0xA0, 0x4D, 0x7A, 0xE1, 0xBE, 0x1D, 0xFF, 0x8B } };
  return TestObjectPropertiesPagePlugIn_UUID;
}

BOOL CTestObjectPropertiesPagePlugIn::OnLoadPlugIn()
{
  return TRUE;
}

void CTestObjectPropertiesPagePlugIn::OnUnloadPlugIn()
{
}

CRhinoPlugIn::plugin_load_time CTestObjectPropertiesPagePlugIn::PlugInLoadTime()
{
  return CRhinoPlugIn::load_plugin_at_startup;
}

void CTestObjectPropertiesPagePlugIn::AddPagesToObjectPropertiesDialog( ON_SimpleArray<class CRhinoObjectPropertiesDialogPage*>& pages )
{
  AFX_MANAGE_STATE( AfxGetStaticModuleState() );
  HWND hWnd = RhinoApp().MainWnd();
  CTestObjectPropertiesPageDlg* page = new CTestObjectPropertiesPageDlg( IDD_OBJPROPPAGE_DIALOG, CWnd::FromHandle(hWnd) );
  if( page )
    pages.Append( page );
}
