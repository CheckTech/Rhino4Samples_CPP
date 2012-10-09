/////////////////////////////////////////////////////////////////////////////
// TestMoveControlPointPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "TestMoveControlPointPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in name
// Provide a short, friendly name for this plug-in.
RHINO_PLUG_IN_NAME( L"TestMoveControlPoint" );

// Rhino plug-in id
// Provide a unique uuid for this plug-in
RHINO_PLUG_IN_ID( L"F554CC1F-A47B-4D78-BF80-3F1B4866F308" );

// Rhino plug-in version
// Provide a version number string for this plug-in
RHINO_PLUG_IN_VERSION( __DATE__"  "__TIME__ )

// Rhino plug-in developer declarations
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

// The one and only CTestMoveControlPointPlugIn object
static CTestMoveControlPointPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestMoveControlPointPlugIn definition

CTestMoveControlPointPlugIn& TestMoveControlPointPlugIn()
{ 
  // Return a reference to the one and only CTestMoveControlPointPlugIn object
  return thePlugIn; 
}

CTestMoveControlPointPlugIn::CTestMoveControlPointPlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = RhinoPlugInVersion();
}

CTestMoveControlPointPlugIn::~CTestMoveControlPointPlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestMoveControlPointPlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return RhinoPlugInName();
}

const wchar_t* CTestMoveControlPointPlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CTestMoveControlPointPlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {F554CC1F-A47B-4D78-BF80-3F1B4866F308}
  return ON_UuidFromString( RhinoPlugInId() );
}

BOOL CTestMoveControlPointPlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestMoveControlPointPlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

