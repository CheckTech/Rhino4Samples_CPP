/////////////////////////////////////////////////////////////////////////////
// TestCustomGripsPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "TestCustomGripsPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
// TODO: fill in the following developer declarations 
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

// The one and only CTestCustomGripsPlugIn object
static CTestCustomGripsPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestCustomGripsPlugIn definition

CTestCustomGripsPlugIn& TestCustomGripsPlugIn()
{ 
  // Return a reference to the one and only CTestCustomGripsPlugIn object
  return thePlugIn; 
}

CTestCustomGripsPlugIn::CTestCustomGripsPlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestCustomGripsPlugIn::~CTestCustomGripsPlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestCustomGripsPlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return L"TestCustomGrips";
}

const wchar_t* CTestCustomGripsPlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CTestCustomGripsPlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {E22ACC4E-DF4C-43BB-8A15-380942437E04}
  static const GUID TestCustomGripsPlugIn_UUID =
  { 0xE22ACC4E, 0xDF4C, 0x43BB, { 0x8A, 0x15, 0x38, 0x9, 0x42, 0x43, 0x7E, 0x4 } };
  return TestCustomGripsPlugIn_UUID;
}

BOOL CTestCustomGripsPlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestCustomGripsPlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

