/////////////////////////////////////////////////////////////////////////////
// DockBarWithUserDialogsPlugIn.cpp

#include "StdAfx.h"
#include "DockBarWithUserDialogsPlugIn.h"
#include "DockBarWithUserDialogs.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"Sample Application Org" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"Sample address, state zip" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"United States" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"555-555-5555" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"555-555-5555" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"tech@myorg.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.myorg.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.myorg.com" );

// The one and only CDockBarWithUserDialogsPlugIn object
static CDockBarWithUserDialogsPlugIn thePlugIn;
  
// Return a reference to the one and only CDockBarWithUserDialogsPlugIn object
CDockBarWithUserDialogsPlugIn& DockBarWithUserDialogsPlugIn() { return thePlugIn; }

/////////////////////////////////////////////////////////////////////////////
// CDockBarWithUserDialogsPlugIn definition

CDockBarWithUserDialogsPlugIn::CDockBarWithUserDialogsPlugIn()
: m_pDockBar(NULL)
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CDockBarWithUserDialogsPlugIn::~CDockBarWithUserDialogsPlugIn()
{
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CDockBarWithUserDialogsPlugIn::PlugInName() const
{
  return L"DockBarWithUserDialogs";
}

const wchar_t* CDockBarWithUserDialogsPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CDockBarWithUserDialogsPlugIn::PlugInID() const
{
  // {FA378768-5DA7-4BCA-87EB-404734BFB84C}
  static const GUID DockBarWithUserDialogsPlugIn_UUID =
  { 0xFA378768, 0x5DA7, 0x4BCA, { 0x87, 0xEB, 0x40, 0x47, 0x34, 0xBF, 0xB8, 0x4C } };
  return DockBarWithUserDialogsPlugIn_UUID;
}

BOOL CDockBarWithUserDialogsPlugIn::OnLoadPlugIn()
{
  m_pDockBar = static_cast<CDockBarWithUserDialogs*>(
    RhinoApp().RhinoUiDockBarManager().CreateRhinoDockBar(
      RUNTIME_CLASS(CDockBarWithUserDialogs), 
      this->PlugInID(), 
      false
      )
    );

  return ( m_pDockBar ) ? TRUE : FALSE;
}

void CDockBarWithUserDialogsPlugIn::OnUnloadPlugIn()
{
}
