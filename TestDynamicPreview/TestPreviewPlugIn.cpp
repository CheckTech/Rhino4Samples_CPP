/////////////////////////////////////////////////////////////////////////////
// TestPreviewPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "TestPreviewPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"Robert McNeel & Associates" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"3670 Woodland Park Avenue North\r\nSeattle, WA 98103" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"United States" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"206.545.6877" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"206.545.7321" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"tech@mcneel.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.rhino3d.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.rhino3d.com" );

// The one and only CTestPreviewPlugIn object
static CTestPreviewPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewPlugIn definition

CTestPreviewPlugIn& TestPreviewPlugIn()
{ 
  // Return a reference to the one and only CTestPreviewPlugIn object
  return thePlugIn; 
}

CTestPreviewPlugIn::CTestPreviewPlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestPreviewPlugIn::~CTestPreviewPlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestPreviewPlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return L"TestPreview";
}

const wchar_t* CTestPreviewPlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CTestPreviewPlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {ED6480A8-8274-4C2A-B823-06053312845E}
  static const GUID TestPreviewPlugIn_UUID =
  { 0xED6480A8, 0x8274, 0x4C2A, { 0xB8, 0x23, 0x6, 0x5, 0x33, 0x12, 0x84, 0x5E } };
  return TestPreviewPlugIn_UUID;
}

BOOL CTestPreviewPlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestPreviewPlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

