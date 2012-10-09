/////////////////////////////////////////////////////////////////////////////
// SculptedPrimsPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "SculptedPrimsPlugIn.h"

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

// The one and only CSculptedPrimsPlugIn object
static CSculptedPrimsPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CSculptedPrimsPlugIn definition

CSculptedPrimsPlugIn& SculptedPrimsPlugIn()
{ 
  // Return a reference to the one and only CSculptedPrimsPlugIn object
  return thePlugIn; 
}

CSculptedPrimsPlugIn::CSculptedPrimsPlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CSculptedPrimsPlugIn::~CSculptedPrimsPlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CSculptedPrimsPlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return L"Sculpted Prims";
}

const wchar_t* CSculptedPrimsPlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CSculptedPrimsPlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {A82B5748-4C55-463A-9AF9-36A264B164EF}
  static const GUID SculptedPrimsPlugIn_UUID =
  { 0xA82B5748, 0x4C55, 0x463A, { 0x9A, 0xF9, 0x36, 0xA2, 0x64, 0xB1, 0x64, 0xEF } };
  return SculptedPrimsPlugIn_UUID;
}

BOOL CSculptedPrimsPlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CSculptedPrimsPlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

/////////////////////////////////////////////////////////////////////////////
// Online help overrides

BOOL CSculptedPrimsPlugIn::AddToPlugInHelpMenu() const
{
  return TRUE;
}

BOOL CSculptedPrimsPlugIn::OnDisplayPlugInHelp( HWND hWnd ) const
{
  // TODO: Add support for online help here.
  return CRhinoUtilityPlugIn::OnDisplayPlugInHelp( hWnd );
}

