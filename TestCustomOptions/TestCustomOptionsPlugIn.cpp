/////////////////////////////////////////////////////////////////////////////
// TestCustomOptionsPlugIn.cpp

#include "StdAfx.h"
#include "TestCustomOptionsPlugIn.h"
#include "TestCustomOptionsDockBar.h"

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
RHINO_PLUG_IN_UPDATE_URL( L"http://www.rhino3d.com" );

// The one and only CTestCustomOptionsPlugIn object
static CTestCustomOptionsPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestCustomOptionsPlugIn definition

CTestCustomOptionsPlugIn& TestCustomOptionsPlugIn()
{ 
  // Return a reference to the one and only CTestCustomOptionsPlugIn object
  return thePlugIn; 
}

CTestCustomOptionsPlugIn::CTestCustomOptionsPlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestCustomOptionsPlugIn::~CTestCustomOptionsPlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestCustomOptionsPlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return L"TestCustomOptions";
}

const wchar_t* CTestCustomOptionsPlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CTestCustomOptionsPlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {91031D6E-0562-4A60-8442-C3E45217E907}
  static const GUID TestCustomOptionsPlugIn_UUID =
  { 0x91031D6E, 0x562, 0x4A60, { 0x84, 0x42, 0xC3, 0xE4, 0x52, 0x17, 0xE9, 0x7 } };
  return TestCustomOptionsPlugIn_UUID;
}

BOOL CTestCustomOptionsPlugIn::OnLoadPlugIn()
{
	::RhinoUiDockBarManager().CreateRhinoDockBar(
        RUNTIME_CLASS(CTestCustomOptionsDockBar), 
        PlugInID(), 
        false, 
        AFX_IDW_DOCKBAR_FLOAT,
        CBRS_ALIGN_ANY,
        NULL,
        CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_LEFT 
        );

  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestCustomOptionsPlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

