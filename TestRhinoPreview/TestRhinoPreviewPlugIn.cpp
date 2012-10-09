/////////////////////////////////////////////////////////////////////////////
// TestRhinoPreviewPlugIn.cpp

#include "StdAfx.h"
#include "TestRhinoPreviewPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in name
RHINO_PLUG_IN_NAME( L"TestRhinoPreview" );

// Rhino plug-in id
RHINO_PLUG_IN_ID( L"1FAA6605-11C2-4ECC-9DE0-258A66B4B3FA" );

// Rhino plug-in version
// Provide a version number string for this plug-in
RHINO_PLUG_IN_VERSION( __DATE__"  "__TIME__ )

// Rhino plug-in developer declarations
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"Robert McNeel & Associates" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"3670 Woodland Park Avenue North\015\012Seattle WA 98103" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"United States" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"206-545-6877" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"206-545-7321" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"tech@mcneel.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.rhino3d.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www2.rhino3d.com/sr/plugin.asp?id=1FAA6605-11C2-4ECC-9DE0-258A66B4B3FA" );

// The one and only CTestRhinoPreviewPlugIn object
static CTestRhinoPreviewPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestRhinoPreviewPlugIn definition

CTestRhinoPreviewPlugIn& TestRhinoPreviewPlugIn()
{ 
  // Return a reference to the one and only CTestRhinoPreviewPlugIn object
  return thePlugIn; 
}

CTestRhinoPreviewPlugIn::CTestRhinoPreviewPlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = RhinoPlugInVersion();
}

CTestRhinoPreviewPlugIn::~CTestRhinoPreviewPlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestRhinoPreviewPlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return RhinoPlugInName();
}

const wchar_t* CTestRhinoPreviewPlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CTestRhinoPreviewPlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {1FAA6605-11C2-4ECC-9DE0-258A66B4B3FA}
  return ON_UuidFromString( RhinoPlugInId() );
}

BOOL CTestRhinoPreviewPlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestRhinoPreviewPlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}
