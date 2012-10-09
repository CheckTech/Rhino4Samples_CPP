/////////////////////////////////////////////////////////////////////////////
// TestWinMsgPlugIn.cpp

#include "StdAfx.h"
#include "TestWinMsgPlugIn.h"

// The plug-in object must be constructed before any plug-in classes
// derived from CRhinoCommand. The #pragma init_seg(lib) ensures that
// this happens.

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in name
RHINO_PLUG_IN_NAME( L"TestWinMsg" );

// Rhino plug-in id
RHINO_PLUG_IN_ID( L"EDDECB87-14FB-4CA1-8428-E80078539A66" );

// Rhino plug-in version
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

// The one and only CTestWinMsgPlugIn object
static CTestWinMsgPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestWinMsgPlugIn definition

CTestWinMsgPlugIn& TestWinMsgPlugIn()
{ 
  // Return a reference to the one and only CTestWinMsgPlugIn object
  return thePlugIn; 
}

CTestWinMsgPlugIn::CTestWinMsgPlugIn()
{
  m_plugin_version = RhinoPlugInVersion();
}

CTestWinMsgPlugIn::~CTestWinMsgPlugIn()
{
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestWinMsgPlugIn::PlugInName() const
{
  return RhinoPlugInName();
}

const wchar_t* CTestWinMsgPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestWinMsgPlugIn::PlugInID() const
{
   // {EDDECB87-14FB-4CA1-8428-E80078539A66}
  return ON_UuidFromString( RhinoPlugInId() );
}

BOOL CTestWinMsgPlugIn::OnLoadPlugIn()
{
  return TRUE;
}

void CTestWinMsgPlugIn::OnUnloadPlugIn()
{
}
