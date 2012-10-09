/////////////////////////////////////////////////////////////////////////////
// HippoPlugInPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "HippoPlugInPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
// TODO: fill in the following developer declarations 
// with your company information.
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"Robert McNeel & Associates" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"3670 Woodland Park Avenue North\015\012Seattle WA 98103" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"United States" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"206-545-6877" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"206-545-7321" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"tech@mcneel.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.rhino3d.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.rhino3d.com" );

// The one and only CHippoPlugInPlugIn object
static CHippoPlugInPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CHippoPlugInPlugIn definition

CHippoPlugInPlugIn& HippoPlugInPlugIn()
{ 
  // Return a reference to the one and only CHippoPlugInPlugIn object
  return thePlugIn; 
}

CHippoPlugInPlugIn::CHippoPlugInPlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CHippoPlugInPlugIn::~CHippoPlugInPlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CHippoPlugInPlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return L"Hippopotamus";
}

const wchar_t* CHippoPlugInPlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CHippoPlugInPlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {9C56BFFC-A5F7-40D9-952D-3ECDB6C666AB}
  static const GUID HippoPlugInPlugIn_UUID =
  { 0x9C56BFFC, 0xA5F7, 0x40D9, { 0x95, 0x2D, 0x3E, 0xCD, 0xB6, 0xC6, 0x66, 0xAB } };
  return HippoPlugInPlugIn_UUID;
}

BOOL CHippoPlugInPlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CHippoPlugInPlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

/////////////////////////////////////////////////////////////////////////////
// Online help overrides

BOOL CHippoPlugInPlugIn::AddToPlugInHelpMenu() const
{
  return TRUE;
}

BOOL CHippoPlugInPlugIn::OnDisplayPlugInHelp( HWND hWnd ) const
{
  // TODO: Add support for online help here.
  ::RhinoMessageBox( L"TODO: Add support for online help here.", PlugInName(), MB_OK );
  return CRhinoUtilityPlugIn::OnDisplayPlugInHelp( hWnd );
}

/////////////////////////////////////////////////////////////////////////////
// Additional overrides required for skinning

CRhinoPlugIn::plugin_load_time CHippoPlugInPlugIn::PlugInLoadTime()
{
  // Override to change load time to "at startup"
  return CRhinoPlugIn::load_plugin_at_startup;
}
