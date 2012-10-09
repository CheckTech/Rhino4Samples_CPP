/////////////////////////////////////////////////////////////////////////////
// TestDocUserTextPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "TestDocUserTextPlugIn.h"

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
// with your company information. 
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"My Company Name" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"123 Developer Street\r\nCity State 12345-6789" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"My Country" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"123.456.7890" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"123.456.7891" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"support@mycompany.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.mycompany.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.mycompany.com/support" );

// The one and only CTestDocUserTextPlugIn object
static CTestDocUserTextPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestDocUserTextPlugIn definition

CTestDocUserTextPlugIn& TestDocUserTextPlugIn()
{ 
  // Return a reference to the one and only CTestDocUserTextPlugIn object
  return thePlugIn; 
}

CTestDocUserTextPlugIn::CTestDocUserTextPlugIn()
{
  // Description:
  //   CTestDocUserTextPlugIn constructor. The constructor is called when the
  //   plug-in is loaded and "thePlugIn" is constructed. Once the plug-in
  //   is loaded, CTestDocUserTextPlugIn::OnLoadPlugIn() is called. The 
  //   constructor should be simple and solid. Do anything that might fail in
  //   CTestDocUserTextPlugIn::OnLoadPlugIn().

  // TODO: Add construction code here
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestDocUserTextPlugIn::~CTestDocUserTextPlugIn()
{
  // Description:
  //   CTestDocUserTextPlugIn destructor. The destructor is called to destroy
  //   "thePlugIn" when the plug-in is unloaded. Immediately before the
  //   DLL is unloaded, CTestDocUserTextPlugIn::OnUnloadPlugin() is called. Do
  //   not do too much here. Be sure to clean up any memory you have allocated
  //   with onmalloc(), onrealloc(), oncalloc(), or onstrdup().

  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestDocUserTextPlugIn::PlugInName() const
{
  // Description:
  //   Plug-in name display string.  This name is displayed by Rhino when
  //   loading the plug-in, in the plug-in help menu, and in the Rhino 
  //   interface for managing plug-ins.

  // TODO: Return a short, friendly name for the plug-in.
  return L"TestDocUserText";
}

const wchar_t* CTestDocUserTextPlugIn::PlugInVersion() const
{
  // Description:
  //   Plug-in version display string. This name is displayed by Rhino 
  //   when loading the plug-in and in the Rhino interface for managing
  //   plug-ins.

  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CTestDocUserTextPlugIn::PlugInID() const
{
  // Description:
  //   Plug-in unique identifier. The identifier is used by Rhino to
  //   manage the plug-ins.

  // TODO: Return a unique identifier for the plug-in.
  // {83F1E51B-0046-44A2-BC6F-5739D191307F}
  static const GUID TestDocUserTextPlugIn_UUID =
  { 0x83F1E51B, 0x46, 0x44A2, { 0xBC, 0x6F, 0x57, 0x39, 0xD1, 0x91, 0x30, 0x7F } };
  return TestDocUserTextPlugIn_UUID;
}

BOOL CTestDocUserTextPlugIn::OnLoadPlugIn()
{
  // Description:
  //   Called after the plug-in is loaded and the constructor has been
  //   run. This is a good place to perform any significant initialization,
  //   license checking, and so on.  This function must return TRUE for
  //   the plug-in to continue to load.

  // TODO: Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestDocUserTextPlugIn::OnUnloadPlugIn()
{
  // Description:
  //   Called when the plug-in is about to be unloaded.  After
  //   this function is called, the destructor will be called.

  // TODO: Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

// Optional overrides

BOOL CTestDocUserTextPlugIn::CallWriteDocument( const CRhinoFileWriteOptions& options )
{
  // Save document data if not exported selected objects.
  BOOL bExporting = options.Mode( CRhinoFileWriteOptions::SelectedMode );
  if( bExporting )
    return false;

  // Save document data if we have document data to save...
  return ( m_user_strings.m_e.Count() ) ? TRUE : FALSE;
}

BOOL CTestDocUserTextPlugIn::WriteDocument( CRhinoDoc& doc, ON_BinaryArchive& archive, const CRhinoFileWriteOptions& options)
{
  int minor_version = 0;
  bool rc = archive.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 1, minor_version );
  if( !rc )
    return false;

  for(;;)
  {
    rc = ( m_user_strings.Write(archive) ) ? true : false;
    if( !rc ) break;

    // TODO...

    break;
  }

  if( !archive.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

BOOL CTestDocUserTextPlugIn::ReadDocument( CRhinoDoc& doc, ON_BinaryArchive& archive, const CRhinoFileReadOptions& options )
{
  BOOL bImporting = options.Mode( CRhinoFileReadOptions::ImportMode) || options.Mode( CRhinoFileReadOptions::ImportReferenceMode );

  // If we are not importing, we must be opening a new document. 
  // So, we need to purge our user string list of previous data.
  if( !bImporting )
    m_user_strings.m_e.Empty();

  int major_version = 0;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk( TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version );
  if( !rc )
    return false;

  for(;;)
  {
    rc = ( 1 == major_version );
    if( !rc ) break;

    // Even if we do not plan on using the data, we still must read it.
    ON_UserStringList user_strings;
    rc = ( user_strings.Read(archive) ) ? true : false;
    if( !rc ) break;

    // If we are not importing, append the user strings to our data member
    if( rc && !bImporting )
      m_user_strings.m_e.Append( user_strings.m_e.Count(), user_strings.m_e.Array() );

    // TODO...

    break;
  }

  if( !archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}

bool CTestDocUserTextPlugIn::SetDocUserString( const wchar_t* key, const wchar_t* string_value )
{
  return m_user_strings.SetUserString( key, string_value );
}

bool CTestDocUserTextPlugIn::GetDocUserString( const wchar_t* key, ON_wString& string_value ) const
{
  return m_user_strings.GetUserString( key, string_value );
}

int CTestDocUserTextPlugIn::GetDocUserStrings( ON_ClassArray<ON_UserString>& user_strings ) const
{
  const int count0 = user_strings.Count();
  user_strings.Append( m_user_strings.m_e.Count(), m_user_strings.m_e.Array() );
  return user_strings.Count() - count0;
}
