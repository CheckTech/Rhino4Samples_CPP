/////////////////////////////////////////////////////////////////////////////
// TestDocumentDataPlugIn.cpp
//

#include "StdAfx.h"
#include "Resource.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// The one and only CTestDocumentDataPlugIn object
static CTestDocumentDataPlugIn thePlugIn;
  
// Returns reference to the plug-in object
CTestDocumentDataPlugIn& TestDocumentDataPlugIn() { return thePlugIn; }

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in developer declarations
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"Robert McNeel & Associates" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"3670 Woodland Park Ave N\r\nSeattle WA  98103" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"United States" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"206-545-7000" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"206-545-7321" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"tech@mcneel.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.rhino3d.com" );
RHINO_PLUG_IN_UPDATE_URL( L"ftp://ftp.mcneel.com/updateme.cab" );

/////////////////////////////////////////////////////////////////////////////
// CTestDocumentDataPlugIn definition

CTestDocumentDataPlugIn::CTestDocumentDataPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
  m_string_table.Empty();

  // Put all complex initialization in OnLoadPlugIn().
}

CTestDocumentDataPlugIn::~CTestDocumentDataPlugIn()
{
  // Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// General plug-in overrides

const wchar_t* CTestDocumentDataPlugIn::PlugInName() const
{
  // Return a short user-friendly name of your plug-in.
  return L"TestDocumentData";
}

const wchar_t* CTestDocumentDataPlugIn::PlugInVersion() const
{
  // Return the version number of your plug-in.
  return m_plugin_version;
}

GUID CTestDocumentDataPlugIn::PlugInID() const
{
  // {BBC32CA7-CF69-4E49-BE0F-CF601DDF656F}
  static const GUID TestDocumentDataPlugIn_GUID =
  { 0xBBC32CA7, 0xCF69, 0x4E49, { 0xBE, 0x0F, 0xCF, 0x60, 0x1D, 0xDF, 0x65, 0x6F } };
  return TestDocumentDataPlugIn_GUID;
}

BOOL CTestDocumentDataPlugIn::OnLoadPlugIn()
{
  // Add plug-in initialization code here.
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CTestDocumentDataPlugIn::OnUnloadPlugIn()
{
  // Add plug-in cleanup code here.
  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

int CTestDocumentDataPlugIn::FindStringTableItem( const wchar_t* str )
{
  // Utility function to find a string item index in
  // our string table
  for( int i = 0; i < m_string_table.Count(); i++ )
  {
    ON_wString item = m_string_table[i];
    if( item.CompareNoCase(str) == 0 )
      return i;
  }
  return -1;
}

BOOL CTestDocumentDataPlugIn::CallWriteDocument( const CRhinoFileWriteOptions& options )
{
  // Only write document data if there is something to write
  return ( m_string_table.Count() > 0 ) ? TRUE : FALSE;
}

BOOL CTestDocumentDataPlugIn::WriteDocument( CRhinoDoc& doc, ON_BinaryArchive& archive, const CRhinoFileWriteOptions& options )
{
  // Write plug-in document data.  See rhinoSdkPlugIn.h details.

  BOOL bSelectedMode = options.Mode( CRhinoFileWriteOptions::SelectedMode );
  BOOL bAsVersion2 = options.Mode( CRhinoFileWriteOptions::AsVersion2 );

  // If the user is exporting selected geometry,
  // or if the user is saving as a V2 3DM file,
  // just return.
  if( bSelectedMode || bAsVersion2 )
    return TRUE;

  // If the file archive version is not 3,
  // just return.
  if( archive.Archive3dmVersion() != 3 )
    return TRUE;

  // Write the major and minor version of document
  // as document data
  if( !archive.Write3dmChunkVersion(1, 0) )
    return FALSE;

  // Write the number of string we intend to write
  // as document data
  if( !archive.WriteInt(m_string_table.Count()) )
    return FALSE;
  
  // Write our string table as document data
  int i = 0;
  for( i = 0; i < m_string_table.Count(); i++ )
  {
    if( !archive.WriteString(m_string_table[i]) )
      return FALSE;
  }

  return TRUE;
}

BOOL CTestDocumentDataPlugIn::ReadDocument( CRhinoDoc& doc, ON_BinaryArchive& archive, const CRhinoFileReadOptions& options )
{
  // Read plug-in document data.  See rhinoSdkPlugIn.h details.

  // If our document data is found in a 3DM file, we are 
  // required to read it. But, we don't necessarily want
  // to use it.

  BOOL bKeepData = FALSE;
  BOOL bNewMode = options.Mode( CRhinoFileReadOptions::NewMode );
  BOOL bOpenMode = options.Mode( CRhinoFileReadOptions::OpenMode );

  // If the user is creating a new model, or opening an existing
  // model, we'll want to keep the document data that we read.
  // Otherwise, we'll read the data, but not use it.  This way,
  // we won't overwrite out data if the user is importing geometry,
  // from another 3DM file.
  if( bNewMode || bOpenMode )
    bKeepData = TRUE;

  if( bKeepData )
    m_string_table.Empty();

  // If the file archive version is not 3,
  // just return.
  if( archive.Archive3dmVersion() != 3 )
    return TRUE;

  // Read the major and minor version of the
  // document data
  int major = 0, minor = 0;
  if( !archive.Read3dmChunkVersion(&major, &minor) )
    return FALSE;

  // At this point, if we've changed the format of
  // our document data, we'll want to compare the
  // major and minor revision numbers and read our
  // data accordingly.

  // Read the number of string we intend to read
  // as document data
  int count = 0;
  if( !archive.ReadInt(&count) )
    return FALSE;

  // Read our string table as document data
  ON_wString str;
  for( int i = 0; i < count; i++ )
  {
    if( !archive.ReadString(str) )
      return FALSE;
    
    // Only append the string if we are
    // supposed to
    if( bKeepData )
      m_string_table.Append(str);
  }

  return TRUE;
}


