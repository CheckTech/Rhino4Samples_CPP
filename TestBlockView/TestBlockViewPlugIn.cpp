/////////////////////////////////////////////////////////////////////////////
// TestBlockViewPlugIn.cpp

#include "StdAfx.h"
#include "TestBlockViewPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

RHINO_PLUG_IN_DECLARE
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

// The one and only CTestBlockViewPlugIn object
static CTestBlockViewPlugIn thePlugIn;

CTestBlockViewPlugIn& TestBlockViewPlugIn()
{ 
  return thePlugIn; 
}

CTestBlockViewPlugIn::CTestBlockViewPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestBlockViewPlugIn::~CTestBlockViewPlugIn()
{
}

const wchar_t* CTestBlockViewPlugIn::PlugInName() const
{
  return L"TestBlockView";
}

const wchar_t* CTestBlockViewPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestBlockViewPlugIn::PlugInID() const
{
  // {5BF5E2F7-4BAB-4A72-9BCD-B137322EA5A5}
  static const GUID TestBlockViewPlugIn_UUID =
  { 0x5BF5E2F7, 0x4BAB, 0x4A72, { 0x9B, 0xCD, 0xB1, 0x37, 0x32, 0x2E, 0xA5, 0xA5 } };
  return TestBlockViewPlugIn_UUID;
}

BOOL CTestBlockViewPlugIn::OnLoadPlugIn()
{
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestBlockViewPlugIn::OnUnloadPlugIn()
{
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

