/////////////////////////////////////////////////////////////////////////////
// FalseColorAnalysisExamplePlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "FalseColorAnalysisExamplePlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
// TODO: fill in the following developer declarations 
// with your company information. When completed,
// delete the following #error directive.
//#error Developer declarations block is incomplete!
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

// The one and only CFalseColorAnalysisExamplePlugIn object
static CFalseColorAnalysisExamplePlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CFalseColorAnalysisExamplePlugIn definition

CFalseColorAnalysisExamplePlugIn& FalseColorAnalysisExamplePlugIn()
{ 
  // Return a reference to the one and only CFalseColorAnalysisExamplePlugIn object
  return thePlugIn; 
}

CFalseColorAnalysisExamplePlugIn::CFalseColorAnalysisExamplePlugIn()
{
  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CFalseColorAnalysisExamplePlugIn::~CFalseColorAnalysisExamplePlugIn()
{
  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CFalseColorAnalysisExamplePlugIn::PlugInName() const
{
  // TODO: Return a short, friendly name for the plug-in.
  return L"FalseColorAnalysisExample";
}

const wchar_t* CFalseColorAnalysisExamplePlugIn::PlugInVersion() const
{
  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CFalseColorAnalysisExamplePlugIn::PlugInID() const
{
  // TODO: Return a unique identifier for the plug-in.
  // {418A8C0D-AB44-4127-A7FC-C64B347006B8}
  static const GUID FalseColorAnalysisExamplePlugIn_UUID =
  { 0x418A8C0D, 0xAB44, 0x4127, { 0xA7, 0xFC, 0xC6, 0x4B, 0x34, 0x70, 0x6, 0xB8 } };
  return FalseColorAnalysisExamplePlugIn_UUID;
}

BOOL CFalseColorAnalysisExamplePlugIn::OnLoadPlugIn()
{
  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CFalseColorAnalysisExamplePlugIn::OnUnloadPlugIn()
{
  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

