/////////////////////////////////////////////////////////////////////////////
// TestScriptPlugIn.cpp
//

#include "StdAfx.h"
#include "TestScriptPlugIn.h"

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

// The one and only CTestScriptPlugIn object
static CTestScriptPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestScriptPlugIn definition

CTestScriptPlugIn& TestScriptPlugIn()
{ 
  // Return a reference to the one and only CTestScriptPlugIn object
  return thePlugIn; 
}

CTestScriptPlugIn::CTestScriptPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestScriptPlugIn::~CTestScriptPlugIn()
{
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestScriptPlugIn::PlugInName() const
{
  return L"TestScript";
}

const wchar_t* CTestScriptPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestScriptPlugIn::PlugInID() const
{
  // {4B5B3183-00C5-446B-8151-BF40F0768424}
  static const GUID TestScriptPlugIn_UUID =
  { 0x4B5B3183, 0xC5, 0x446B, { 0x81, 0x51, 0xBF, 0x40, 0xF0, 0x76, 0x84, 0x24 } };
  return TestScriptPlugIn_UUID;
}

BOOL CTestScriptPlugIn::OnLoadPlugIn()
{
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestScriptPlugIn::OnUnloadPlugIn()
{
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

/////////////////////////////////////////////////////////////////////////////
// Optional overrides

LPUNKNOWN CTestScriptPlugIn::GetPlugInObjectInterface( const ON_UUID& iid )
{
  LPUNKNOWN lpUnknown = 0;
 
  if( iid == IID_IUnknown )
    lpUnknown = m_object.GetInterface( &IID_IUnknown );

  else if( iid == IID_IDispatch )
    lpUnknown = m_object.GetInterface( &IID_IDispatch );
  
  /*
  It is the responsibility of the application calling this function to
  increment and decrement the object's reference count using AddRef() and Release().
  If the plug-in object being request is a stack variable, then you will
  also want to increment the reference counter yourself so the object will not
  be destroyed when released by the calling application.
  */
  if( lpUnknown )
    m_object.ExternalAddRef();

  return lpUnknown;
}
