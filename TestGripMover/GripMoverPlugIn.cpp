/////////////////////////////////////////////////////////////////////////////
// GripMoverPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "GripMoverPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
// TODO: fill in the following developer declarations with
// your company information. Note, all of these declarations
// must be present or your plug-in will not load.
//
// When completed, delete the following #error directive.
//#error Developer declarations block is incomplete!
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

// The one and only CGripMoverPlugIn object
static CGripMoverPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CGripMoverPlugIn definition

CGripMoverPlugIn& GripMoverPlugIn()
{ 
  // Return a reference to the one and only CGripMoverPlugIn object
  return thePlugIn; 
}

CGripMoverPlugIn::CGripMoverPlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CGripMoverPlugIn::~CGripMoverPlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CGripMoverPlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return L"GripMover";
}

const wchar_t* CGripMoverPlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CGripMoverPlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {56C167A9-D6E3-4250-9C90-D8162A594BC0}
  static const GUID GripMoverPlugIn_UUID =
  { 0x56C167A9, 0xD6E3, 0x4250, { 0x9C, 0x90, 0xD8, 0x16, 0x2A, 0x59, 0x4B, 0xC0 } };
  return GripMoverPlugIn_UUID;
}

BOOL CGripMoverPlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CGripMoverPlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

