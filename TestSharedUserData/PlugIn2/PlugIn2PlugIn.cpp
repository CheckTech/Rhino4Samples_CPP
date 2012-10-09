/////////////////////////////////////////////////////////////////////////////
// PlugIn2PlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "PlugIn2PlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
// TODO: fill in the following developer declarations 
// with your company information.
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

// The one and only CPlugIn2PlugIn object
static CPlugIn2PlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CPlugIn2PlugIn definition

CPlugIn2PlugIn& PlugIn2PlugIn()
{ 
  // Return a reference to the one and only CPlugIn2PlugIn object
  return thePlugIn; 
}

CPlugIn2PlugIn::CPlugIn2PlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CPlugIn2PlugIn::~CPlugIn2PlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CPlugIn2PlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return L"PlugIn2";
}

const wchar_t* CPlugIn2PlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CPlugIn2PlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {61F48E42-1AB7-4BF2-BCE9-44BAF4215AE0}
  static const GUID PlugIn2PlugIn_UUID =
  { 0x61F48E42, 0x1AB7, 0x4BF2, { 0xBC, 0xE9, 0x44, 0xBA, 0xF4, 0x21, 0x5A, 0xE0 } };
  return PlugIn2PlugIn_UUID;
}

BOOL CPlugIn2PlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CPlugIn2PlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

