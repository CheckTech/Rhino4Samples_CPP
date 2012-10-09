/////////////////////////////////////////////////////////////////////////////
// RhinoDockBarPlugIn.cpp : defines the initialization routines for the plug-in.
//


#include "StdAfx.h"
#include "RhinoDockBarPlugIn.h"
#include "MyRhinoDockBar.h"


// The plug-in object must be constructed before any plug-in classes
// derived from CRhinoCommand. The #pragma init_seg(lib) ensures that
// this happens.

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
// comment out the preceding error line after you've supplied
// the plug-in information below
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

// The one and only CRhinoDockBarPlugIn object
static CRhinoDockBarPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CRhinoDockBarPlugIn definition

CRhinoDockBarPlugIn& RhinoDockBarPlugIn()
{ 
  // Return a reference to the one and only CRhinoDockBarPlugIn object
  return thePlugIn; 
}

CRhinoDockBarPlugIn::CRhinoDockBarPlugIn()
{
  // Description:
  //   CRhinoDockBarPlugIn constructor. The constructor is called when the
  //   plug-in is loaded and "thePlugIn" is constructed. Once the plug-in
  //   is loaded, CRhinoDockBarPlugIn::OnLoadPlugIn() is called. The 
  //   constructor should be simple and solid. Do anything that might fail in
  //   CRhinoDockBarPlugIn::OnLoadPlugIn().

  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CRhinoDockBarPlugIn::~CRhinoDockBarPlugIn()
{
  // Description:
  //   CRhinoDockBarPlugIn destructor. The destructor is called to destroy
  //   "thePlugIn" when the plug-in is unloaded. Immediately before the
  //   DLL is unloaded, CRhinoDockBarPlugIn::OnUnloadPlugin() is called. Do
  //   not do too much here. Be sure to clean up any memory you have allocated
  //   with onmalloc(), onrealloc(), oncalloc(), or onstrdup().

  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CRhinoDockBarPlugIn::PlugInName() const
{
  // Description:
  //   Plug-in name display string.  This name is displayed by Rhino when
  //   loading the plug-in, in the plug-in help menu, and in the Rhino 
  //   interface for managing plug-ins.

  // TODO: Return a short, friendly name for the plug-in.
  return L"RhinoDockBar";
}

const wchar_t* CRhinoDockBarPlugIn::PlugInVersion() const
{
  // Description:
  //   Plug-in version display string. This name is displayed by Rhino 
  //   when loading the plug-in and in the Rhino interface for managing
  //   plug-ins.

  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CRhinoDockBarPlugIn::PlugInID() const
{
  // Description:
  //   Plug-in unique identifier. The identifier is used by Rhino to
  //   manage the plug-ins.

  // TODO: Return a unique identifier for the plug-in.
  static const GUID RhinoDockBarPlugIn_UUID =
  { 0x2FE549B7, 0xE7BA, 0x43AA, { 0x86, 0xE2, 0x41, 0x63, 0x63, 0x84, 0xE2, 0xE0 } };
  return RhinoDockBarPlugIn_UUID;
}

BOOL CRhinoDockBarPlugIn::OnLoadPlugIn()
{
  // Description:
  //   Called after the plug-in is loaded and the constructor has been
  //   run. This is a good place to perform any significant initialization,
  //   license checking, and so on.  This function must return TRUE for
  //   the plug-in to continue to load.

  // TODO: Add plug-in initialization code here.



////////////////////////////////////////////////////////////////////////////////////
//  create our dockbar
//
	//ask Rhino's DockBarManager to create our dockbar, show_control_bar=false -> we'll use our ShowMyDockBar command to show the dockbar
	::RhinoUiDockBarManager().CreateRhinoDockBar(RUNTIME_CLASS(CMyRhinoDockBar), CRhinoDockBarPlugIn().PlugInID(), false, AFX_IDW_DOCKBAR_FLOAT,CBRS_ALIGN_ANY,NULL,CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_LEFT);
//
// 
////////////////////////////////////////////////////////////////////////////////////



  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CRhinoDockBarPlugIn::OnUnloadPlugIn()
{
  // Description:
  //   Called when the plug-in is about to be unloaded.  After
  //   this function is called, the destructor will be called.

  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

/////////////////////////////////////////////////////////////////////////////
// Online help overrides

BOOL CRhinoDockBarPlugIn::AddToPlugInHelpMenu() const
{
  // Description:
  //   Return true to have your plug-in name added to the Rhino help menu.
  //   OnDisplayPlugInHelp will be called when to activate your plug-in help.

  return TRUE;
}

BOOL CRhinoDockBarPlugIn::OnDisplayPlugInHelp( HWND hWnd ) const
{
  // Description:
  //   Called when the user requests help about your plug-in.
  //   It should display a standard Windows Help file (.hlp or .chm).

  // TODO: Add support for online help here.
  return CRhinoUtilityPlugIn::OnDisplayPlugInHelp( hWnd );
}

