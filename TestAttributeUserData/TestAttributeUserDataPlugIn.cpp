/////////////////////////////////////////////////////////////////////////////
// TestAttributeUserDataPlugIn.cpp

#include "StdAfx.h"
#include "TestAttributeUserDataPlugIn.h"

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

// The one and only CTestAttributeUserDataPlugIn object
static CTestAttributeUserDataPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestAttributeUserDataPlugIn definition

CTestAttributeUserDataPlugIn& TestAttributeUserDataPlugIn()
{ 
  // Return a reference to the one and only CTestAttributeUserDataPlugIn object
  return thePlugIn; 
}

CTestAttributeUserDataPlugIn::CTestAttributeUserDataPlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestAttributeUserDataPlugIn::~CTestAttributeUserDataPlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestAttributeUserDataPlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return L"TestAttributeUserData";
}

const wchar_t* CTestAttributeUserDataPlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CTestAttributeUserDataPlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {1E8F5784-EFC5-4EDF-BA41-94F3DC53305D}
  static const GUID TestAttributeUserDataPlugIn_UUID =
  { 0x1E8F5784, 0xEFC5, 0x4EDF, { 0xBA, 0x41, 0x94, 0xF3, 0xDC, 0x53, 0x30, 0x5D } };
  return TestAttributeUserDataPlugIn_UUID;
}

BOOL CTestAttributeUserDataPlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestAttributeUserDataPlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

