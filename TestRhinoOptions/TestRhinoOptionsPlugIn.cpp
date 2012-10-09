#include "StdAfx.h"
#include "TestRhinoOptionsPlugIn.h"
#include "TestRhinoOptionsPage.h"
#include "TestRhinoDocPropsPage.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"Robert McNeel & Associates" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"3670 Woodland Park Avenue North\015\012Seattle WA 98103" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"United States" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"206-545-6877" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"206-545-7321" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"tech@mcneel.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.rhino3d.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www2.rhino3d.com/sr/plugin.asp?id=19210E65-65DB-4F73-BD01-EFB65D308FBA" );

// The one and only CTestRhinoOptionsPlugIn object
static CTestRhinoOptionsPlugIn thePlugIn;

CTestRhinoOptionsPlugIn& TestRhinoOptionsPlugIn()
{ 
  return thePlugIn; 
}

CTestRhinoOptionsPlugIn::CTestRhinoOptionsPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestRhinoOptionsPlugIn::~CTestRhinoOptionsPlugIn()
{
}

const wchar_t* CTestRhinoOptionsPlugIn::PlugInName() const
{
  return L"TestRhinoOptions";
}

const wchar_t* CTestRhinoOptionsPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestRhinoOptionsPlugIn::PlugInID() const
{
  // {19210E65-65DB-4F73-BD01-EFB65D308FBA}
  static const GUID TestRhinoOptionsPlugIn_UUID =
  { 0x19210E65, 0x65DB, 0x4F73, { 0xBD, 0x1, 0xEF, 0xB6, 0x5D, 0x30, 0x8F, 0xBA } };
  return TestRhinoOptionsPlugIn_UUID;
}

BOOL CTestRhinoOptionsPlugIn::OnLoadPlugIn()
{
  return TRUE;
}

void CTestRhinoOptionsPlugIn::OnUnloadPlugIn()
{
}

BOOL CTestRhinoOptionsPlugIn::AddToPlugInHelpMenu() const
{
  return TRUE;
}

BOOL CTestRhinoOptionsPlugIn::OnDisplayPlugInHelp( HWND hWnd ) const
{
  RhinoMessageBox( RhinoApp().MainWnd(), L"Add online help support here", PlugInName(), MB_OK );
  return CRhinoUtilityPlugIn::OnDisplayPlugInHelp( hWnd );
}

CRhinoPlugIn::plugin_load_time CTestRhinoOptionsPlugIn::PlugInLoadTime()
{
  return CRhinoPlugIn::load_plugin_at_startup;
}

void CTestRhinoOptionsPlugIn::AddPagesToOptionsDialog( HWND hWnd, ON_SimpleArray<CRhinoOptionsDialogPage*>& pages )
{
  AFX_MANAGE_STATE( AfxGetStaticModuleState() );
  CTestRhinoOptionsPage* p = new CTestRhinoOptionsPage( CWnd::FromHandle(hWnd) );
  if( p )
    pages.Append( p );
}

void CTestRhinoOptionsPlugIn::AddPagesToDocumentPropertiesDialog( CRhinoDoc& doc, HWND hWnd, ON_SimpleArray<CRhinoOptionsDialogPage*>& pages )
{
  AFX_MANAGE_STATE( AfxGetStaticModuleState() );
  CTestRhinoDocPropsPage* p = new CTestRhinoDocPropsPage( CWnd::FromHandle(hWnd) );
  if( p )
    pages.Append( p );
}
