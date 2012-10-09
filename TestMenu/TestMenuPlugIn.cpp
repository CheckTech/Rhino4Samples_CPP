/////////////////////////////////////////////////////////////////////////////
// TestMenuPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "TestMenuApp.h"
#include "TestMenuPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

/////////////////////////////////////////////////////////////////////////////
// CTestMenuPlugIn definition

CTestMenuPlugIn::CTestMenuPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
  m_script_mode = false;
}

CTestMenuPlugIn::~CTestMenuPlugIn()
{
}

// The one and only CTestMenuPlugIn object
static CTestMenuPlugIn thePlugIn;

CTestMenuPlugIn& TestMenuPlugIn()
{ 
  return thePlugIn; 
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestMenuPlugIn::PlugInName() const
{
  return L"TestMenu";
}

const wchar_t* CTestMenuPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestMenuPlugIn::PlugInID() const
{
  // {3A181BB3-634D-4067-A343-146686A2D380}
  static const GUID TestMenuPlugIn_UUID =
  { 0x3A181BB3, 0x634D, 0x4067, { 0xA3, 0x43, 0x14, 0x66, 0x86, 0xA2, 0xD3, 0x80 } };
  return TestMenuPlugIn_UUID;
}

BOOL CTestMenuPlugIn::OnLoadPlugIn()
{
  AFX_MANAGE_STATE( AfxGetStaticModuleState() );

  if( m_menu.LoadMenu(IDR_TESTMENU) )
    InsertPlugInMenuToRhinoMenu( m_menu.GetSafeHmenu(), 0);

  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestMenuPlugIn::OnUnloadPlugIn()
{
  // Since plug-ins are not unloadable, there is no reason
  // to unload our plug-in menu here.
}

/////////////////////////////////////////////////////////////////////////////
// Online help overrides

BOOL CTestMenuPlugIn::AddToPlugInHelpMenu() const
{
  return TRUE;
}

BOOL CTestMenuPlugIn::OnDisplayPlugInHelp( HWND hWnd ) const
{
  ::RhinoMessageBox( L"TODO: Add online help here.", PlugInName(), MB_OK );
  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Additional overrides

void CTestMenuPlugIn::OnInitPlugInMenuPopups( WPARAM wParam, LPARAM /*lParam*/ )
{
  HMENU hMenu = (HMENU)wParam;
  if( hMenu )
  {
    UINT uCheck = MF_BYCOMMAND;
    if( m_script_mode )
      uCheck |= MF_CHECKED;
    else
      uCheck |= MF_UNCHECKED;
    ::CheckMenuItem( hMenu, ID_TESTMENU_SCRIPTMODE, uCheck );
  }
}

BOOL CTestMenuPlugIn::OnPlugInMenuCommand( WPARAM wParam )
{
  switch( wParam )
  {
  case ID_TESTMENU_TESTCOMMAND1:
    {
      if( m_script_mode )
        RhinoApp().RunScript( L"_-TestMenu1" );
      else
        RhinoApp().RunScript( L"_TestMenu1" );
    }
    break;

  case ID_TESTMENU_TESTCOMMAND2:
    {
      if( m_script_mode )
        RhinoApp().RunScript( L"_-TestMenu2" );
      else
        RhinoApp().RunScript( L"_TestMenu2" );
    }
    break;

  case ID_TESTMENU_SCRIPTMODE:
    {
      if( m_script_mode )
        m_script_mode = false;
      else
        m_script_mode = true;
    }
    break;

  default:
    return FALSE;
  }

  return TRUE;
}
