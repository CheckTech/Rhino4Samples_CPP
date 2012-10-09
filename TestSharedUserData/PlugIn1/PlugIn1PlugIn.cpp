/////////////////////////////////////////////////////////////////////////////
// PlugIn1PlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "PlugIn1PlugIn.h"

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

// The one and only CPlugIn1PlugIn object
static CPlugIn1PlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CPlugIn1PlugIn definition

CPlugIn1PlugIn& PlugIn1PlugIn()
{ 
  // Return a reference to the one and only CPlugIn1PlugIn object
  return thePlugIn; 
}

CPlugIn1PlugIn::CPlugIn1PlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CPlugIn1PlugIn::~CPlugIn1PlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CPlugIn1PlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return L"PlugIn1";
}

const wchar_t* CPlugIn1PlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CPlugIn1PlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {F8B054CD-19A3-4D46-AB7E-DB3E8EF8CF5B}
  static const GUID PlugIn1PlugIn_UUID =
  { 0xF8B054CD, 0x19A3, 0x4D46, { 0xAB, 0x7E, 0xDB, 0x3E, 0x8E, 0xF8, 0xCF, 0x5B } };
  return PlugIn1PlugIn_UUID;
}

BOOL CPlugIn1PlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CPlugIn1PlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

