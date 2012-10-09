/////////////////////////////////////////////////////////////////////////////
// TestDigitizerPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "TestDigitizerPlugIn.h"

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
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

// The one and only CTestDigitizerPlugIn object
static CTestDigitizerPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestDigitizerPlugIn definition

CTestDigitizerPlugIn& TestDigitizerPlugIn()
{ 
  // Return a reference to the one and only CTestDigitizerPlugIn object
  return thePlugIn; 
}

CTestDigitizerPlugIn::CTestDigitizerPlugIn()
{
  // Description:
  //   CTestDigitizerPlugIn constructor. The constructor is called when the
  //   plug-in is loaded and "thePlugIn" is constructed. Once the plug-in
  //   is loaded, CTestDigitizerPlugIn::OnLoadPlugIn() is called. The 
  //   constructor should be simple and solid. Do anything that might fail in
  //   CTestDigitizerPlugIn::OnLoadPlugIn().

  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;

	m_hThread = 0;
	m_dwThreadID = 0;
	m_bDigitizerConnected = false;
}

CTestDigitizerPlugIn::~CTestDigitizerPlugIn()
{
  // Description:
  //   CTestDigitizerPlugIn destructor. The destructor is called to destroy
  //   "thePlugIn" when the plug-in is unloaded. Immediately before the
  //   DLL is unloaded, CTestDigitizerPlugIn::OnUnloadPlugin() is called. Do
  //   not do too much here. Be sure to clean up any memory you have allocated
  //   with onmalloc(), onrealloc(), oncalloc(), or onstrdup().

  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestDigitizerPlugIn::PlugInName() const
{
  // Description:
  //   Plug-in name display string.  This name is displayed by Rhino when
  //   loading the plug-in, in the plug-in help menu, and in the Rhino 
  //   interface for managing plug-ins.

  // TODO: Return a short, friendly name for the plug-in.
  return L"TestDigitizer";
}

const wchar_t* CTestDigitizerPlugIn::PlugInVersion() const
{
  // Description:
  //   Plug-in version display string. This name is displayed by Rhino 
  //   when loading the plug-in and in the Rhino interface for managing
  //   plug-ins.

  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CTestDigitizerPlugIn::PlugInID() const
{
  // Description:
  //   Plug-in unique identifier. The identifier is used by Rhino to
  //   manage the plug-ins.

  // TODO: Return a unique identifier for the plug-in.
  // {359E99D2-5733-42C1-908E-E72263648728}
  static const GUID TestDigitizerPlugIn_UUID =
  { 0x359E99D2, 0x5733, 0x42C1, { 0x90, 0x8E, 0xE7, 0x22, 0x63, 0x64, 0x87, 0x28 } };
  return TestDigitizerPlugIn_UUID;
}

BOOL CTestDigitizerPlugIn::OnLoadPlugIn()
{
  // Description:
  //   Called after the plug-in is loaded and the constructor has been
  //   run. This is a good place to perform any significant initialization,
  //   license checking, and so on.  This function must return TRUE for
  //   the plug-in to continue to load.

  // NOTE: DO NOT enable your digitizer here!

  // TODO: Add plug-in initialization code here.
  return CRhinoDigitizerPlugIn::OnLoadPlugIn();
}

void CTestDigitizerPlugIn::OnUnloadPlugIn()
{
  // Description:
  //   Called when the plug-in is about to be unloaded.  After
  //   this function is called, the destructor will be called.

  // TODO: Add plug-in cleanup code here.
  EnableDigitizer( false );
}

/////////////////////////////////////////////////////////////////////////////
// Digitizer overrides

ON::unit_system CTestDigitizerPlugIn::UnitSystem() const
{
  // TODO: Return the digitizer's unit system.
  return ON::millimeters;
}

double CTestDigitizerPlugIn::PointTolerance() const
{
  // Description:
  //   Precision of the digitizer in the unit system
  //   returned by CTestDigitizerPlugIn::UnitSystem().
  //   If this number is too small, digitizer noise will
  //   cause GetPoint() to jitter.

  // TODO: Return the digitizer's point tolerance.
  return 0.01;
}

static DWORD WINAPI ThreadProc( LPVOID pVoid )
{
  CTestDigitizerPlugIn* pPlugIn = (CTestDigitizerPlugIn*)pVoid;
  ASSERT( pPlugIn );

  ON_3dPoint pt;
  while( 1 )
  {
    /*
    Do whatever you need to do to query the digitizer here
    so you can call CRhinoPlugIn::SendPoint().

    DWORD dwResult = WaitForSingleObject( ... );
    if( WAIT_OBJECT_0 == dwResult )
    {
      ON_3dPoint = ?
      UINT uFlags = ?
      pPlugIn->SendPoint( pt, nFlags );
    }
    */
  }
  
  // Should never get here
  return 0;
}

bool CTestDigitizerPlugIn::EnableDigitizer( bool bEnable )
{
  // In case we need to access our resources...
	AFX_MANAGE_STATE( AfxGetStaticModuleState() ); 

  // In case we need Rhino main window handle...
  HWND hwndRhino = RhinoApp().MainWnd();

	bool rc = false;

	if( bEnable )
	{
    for( ;; )
    {
      if( m_bDigitizerConnected ) 
      {
        ::RhinoApp().Print( L"Digitizer already connected.\n" );
        rc = true;
        break;
      }

      ::RhinoApp().Print( L"Connecting to digitizer ...\n" );

      /*
      Do whatever it takes to connnect to and initialize
      your digitizer here. If you need to call LoadLibrary()
      to load some communication DLL, do it here. Once you 
      have connected and initialized your digitizer, you can
      create the polling thread.
      */

      // Start up the polling thread
      m_hThread = ::CreateThread( NULL, 0, ThreadProc, this, 0, &m_dwThreadID );
      m_bDigitizerConnected = true;
      rc = true;
      break;
    }
  }
  else 
  {
    if( !m_bDigitizerConnected )
      return true;
  
    if( m_hThread ) 
    {
      ::TerminateThread( m_hThread, 0 );
      ::CloseHandle( m_hThread );
      m_hThread = 0;
    }
  
  	/*
    Shut down communications with the digitizer here. If 
    you need to call FreeLibrary to release a communications
    DLL, do it here.
    */

    m_dwThreadID = 0;
    m_bDigitizerConnected = false;
    rc = true;
  }

  return rc;
}
