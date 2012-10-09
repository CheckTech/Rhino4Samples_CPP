/////////////////////////////////////////////////////////////////////////////
// TestPointCloudUserDataPlugIn.cpp

#include "StdAfx.h"
#include "TestPointCloudUserDataPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"Robert McNeel & Associates" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"3670 Woodland Park Avenue North\015\012Seattle WA 98103" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"United States" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"206-545-6877" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"206-545-7321" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"tech@mcneel.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.rhino3d.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.rhino3d.com" );

// The one and only CTestPointCloudUserDataPlugIn object
static CTestPointCloudUserDataPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestPointCloudUserDataPlugIn definition

CTestPointCloudUserDataPlugIn& ThePlugIn()
{ 
  return thePlugIn; 
}

CTestPointCloudUserDataPlugIn::CTestPointCloudUserDataPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestPointCloudUserDataPlugIn::~CTestPointCloudUserDataPlugIn()
{
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestPointCloudUserDataPlugIn::PlugInName() const
{
  return L"TestPointCloudUserData";
}

const wchar_t* CTestPointCloudUserDataPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestPointCloudUserDataPlugIn::PlugInID() const
{
  // {05D95021-436A-4C12-AFF5-1BF057511EBB}
  static const GUID TestPointCloudUserDataPlugIn_UUID =
  { 0x5D95021, 0x436A, 0x4C12, { 0xAF, 0xF5, 0x1B, 0xF0, 0x57, 0x51, 0x1E, 0xBB } };
  return TestPointCloudUserDataPlugIn_UUID;
}

BOOL CTestPointCloudUserDataPlugIn::OnLoadPlugIn()
{
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestPointCloudUserDataPlugIn::OnUnloadPlugIn()
{
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

