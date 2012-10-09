/////////////////////////////////////////////////////////////////////////////
// TestAssociationDataPlugIn.cpp

#include "StdAfx.h"
#include "TestAssociationDataPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in name
// Provide a short, friendly name for this plug-in.
RHINO_PLUG_IN_NAME( L"TestAssociationData" );

// Rhino plug-in id
// Provide a unique uuid for this plug-in
RHINO_PLUG_IN_ID( L"A963C09F-6183-4A54-9589-0799ABFD924A" );

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

// The one and only CTestAssociationDataPlugIn object
static CTestAssociationDataPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestAssociationDataPlugIn definition

CTestAssociationDataPlugIn& TestAssociationDataPlugIn()
{ 
  return thePlugIn; 
}

CTestAssociationDataPlugIn::CTestAssociationDataPlugIn()
{
  m_plugin_version = RhinoPlugInVersion();
}

CTestAssociationDataPlugIn::~CTestAssociationDataPlugIn()
{
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestAssociationDataPlugIn::PlugInName() const
{
  return RhinoPlugInName();
}

const wchar_t* CTestAssociationDataPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestAssociationDataPlugIn::PlugInID() const
{
  // {A963C09F-6183-4A54-9589-0799ABFD924A}
  return ON_UuidFromString( RhinoPlugInId() );
}

BOOL CTestAssociationDataPlugIn::OnLoadPlugIn()
{
  return TRUE;
}

void CTestAssociationDataPlugIn::OnUnloadPlugIn()
{
}

