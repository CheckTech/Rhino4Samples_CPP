/////////////////////////////////////////////////////////////////////////////
// TestOptionsListCtrlPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "TestOptionsListCtrlPlugIn.h"
#include "TestOptionsListCtrlDockBar.h"

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

// The one and only CTestOptionsListCtrlPlugIn object
static CTestOptionsListCtrlPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestOptionsListCtrlPlugIn definition

CTestOptionsListCtrlPlugIn& TestOptionsListCtrlPlugIn()
{ 
  // Return a reference to the one and only CTestOptionsListCtrlPlugIn object
  return thePlugIn; 
}

CTestOptionsListCtrlPlugIn::CTestOptionsListCtrlPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestOptionsListCtrlPlugIn::~CTestOptionsListCtrlPlugIn()
{
}

const wchar_t* CTestOptionsListCtrlPlugIn::PlugInName() const
{
  return L"TestOptionsListCtrl";
}

const wchar_t* CTestOptionsListCtrlPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestOptionsListCtrlPlugIn::PlugInID() const
{
  // {43126A4A-0AFF-47DC-9C60-ACED0D1956E4}
  static const GUID TestOptionsListCtrlPlugIn_UUID =
  { 0x43126A4A, 0xAFF, 0x47DC, { 0x9C, 0x60, 0xAC, 0xED, 0xD, 0x19, 0x56, 0xE4 } };
  return TestOptionsListCtrlPlugIn_UUID;
}

BOOL CTestOptionsListCtrlPlugIn::OnLoadPlugIn()
{
	::RhinoUiDockBarManager().CreateRhinoDockBar(
        RUNTIME_CLASS(CTestOptionsListCtrlDockBar), 
        PlugInID(), 
        false, 
        AFX_IDW_DOCKBAR_FLOAT,
        CBRS_ALIGN_ANY,
        NULL,
        CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_LEFT 
        );

  return TRUE;
}

void CTestOptionsListCtrlPlugIn::OnUnloadPlugIn()
{
}

