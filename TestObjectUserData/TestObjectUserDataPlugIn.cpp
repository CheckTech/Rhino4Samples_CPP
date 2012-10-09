/////////////////////////////////////////////////////////////////////////////
// TestObjectUserDataPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "TestObjectUserDataPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
// TODO: fill in the following developer declarations with
// your company information. Note, all of these declarations
// must be present or your plug-in will not load.
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

// The one and only CTestObjectUserDataPlugIn object
static CTestObjectUserDataPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestObjectUserDataPlugIn definition

CTestObjectUserDataPlugIn& TestObjectUserDataPlugIn()
{ 
  // Return a reference to the one and only CTestObjectUserDataPlugIn object
  return thePlugIn; 
}

CTestObjectUserDataPlugIn::CTestObjectUserDataPlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestObjectUserDataPlugIn::~CTestObjectUserDataPlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestObjectUserDataPlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return L"TestObjectUserData";
}

const wchar_t* CTestObjectUserDataPlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CTestObjectUserDataPlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {85453D99-4DCE-4407-AF47-40CAC1C285E7}
  static const GUID TestObjectUserDataPlugIn_UUID =
  { 0x85453D99, 0x4DCE, 0x4407, { 0xAF, 0x47, 0x40, 0xCA, 0xC1, 0xC2, 0x85, 0xE7 } };
  return TestObjectUserDataPlugIn_UUID;
}

BOOL CTestObjectUserDataPlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestObjectUserDataPlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

