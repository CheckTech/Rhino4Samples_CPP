/////////////////////////////////////////////////////////////////////////////
// TestDockBarPlugIn.cpp

#include "StdAfx.h"
#include "TestDockBarPlugIn.h"
#include "TestDockBar.h"

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
RHINO_PLUG_IN_UPDATE_URL( L"http://www2.rhino3d.com/sr/plugin.asp?id=6F849C40-B241-4443-AAC3-FD9267CD996C" );

// The one and only CTestDockBarPlugIn object
static CTestDockBarPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestDockBarPlugIn definition

CTestDockBarPlugIn& TestDockBarPlugIn()
{ 
  return thePlugIn; 
}

CTestDockBarPlugIn::CTestDockBarPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestDockBarPlugIn::~CTestDockBarPlugIn()
{
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestDockBarPlugIn::PlugInName() const
{
  return L"TestDockBar";
}

const wchar_t* CTestDockBarPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestDockBarPlugIn::PlugInID() const
{
  // {6F849C40-B241-4443-AAC3-FD9267CD996C}
  static const GUID TestDockBarPlugIn_UUID =
  { 0x6F849C40, 0xB241, 0x4443, { 0xAA, 0xC3, 0xFD, 0x92, 0x67, 0xCD, 0x99, 0x6C } };
  return TestDockBarPlugIn_UUID;
}

BOOL CTestDockBarPlugIn::OnLoadPlugIn()
{
	::RhinoUiDockBarManager().CreateRhinoDockBar(
        RUNTIME_CLASS(CTestDockBar), 
        PlugInID(), 
        false, 
        AFX_IDW_DOCKBAR_RIGHT,
        CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT,
        NULL,
        CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_LEFT 
        );

  
  return TRUE;
}

void CTestDockBarPlugIn::OnUnloadPlugIn()
{
}

