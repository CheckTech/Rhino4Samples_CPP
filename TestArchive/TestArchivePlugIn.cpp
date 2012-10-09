/////////////////////////////////////////////////////////////////////////////
// TestArchivePlugIn.cpp

#include "StdAfx.h"
#include "TestArchivePlugIn.h"

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
RHINO_PLUG_IN_UPDATE_URL( L"http://www2.rhino3d.com/sr/plugin.asp?id=67991B7A-BFD7-4029-9B3A-7F10205B596E" );

// The one and only CTestArchivePlugIn object
static CTestArchivePlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestArchivePlugIn definition

CTestArchivePlugIn& TestArchivePlugIn()
{ 
  // Return a reference to the one and only CTestArchivePlugIn object
  return thePlugIn; 
}

CTestArchivePlugIn::CTestArchivePlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestArchivePlugIn::~CTestArchivePlugIn()
{
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestArchivePlugIn::PlugInName() const
{
  return L"TestArchive";
}

const wchar_t* CTestArchivePlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestArchivePlugIn::PlugInID() const
{
  // {67991B7A-BFD7-4029-9B3A-7F10205B596E}
  static const GUID TestArchivePlugIn_UUID =
  { 0x67991B7A, 0xBFD7, 0x4029, { 0x9B, 0x3A, 0x7F, 0x10, 0x20, 0x5B, 0x59, 0x6E } };
  return TestArchivePlugIn_UUID;
}

BOOL CTestArchivePlugIn::OnLoadPlugIn()
{
  // Register and enable our event watcher
  m_watcher.Register();
  m_watcher.Enable();

  // Seed the random-number generator with the current time so that
  // the numbers will be different every time we run.
  srand( (unsigned int)time(0) );

  return TRUE;
}

void CTestArchivePlugIn::OnUnloadPlugIn()
{
}

void CTestArchivePlugIn::InitTestData()
{
  for( int i = 0; i < 10; i++ )
    m_list.AddTail( rand() );
}

void CTestArchivePlugIn::PrintTestData()
{
  POSITION pos = m_list.GetHeadPosition();
  if( pos )
  {
    RhinoApp().Print( L"Test data:\n" );

    int count = 0;
    while( pos )
    {
      int n = m_list.GetNext( pos );
      RhinoApp().Print( L"  %Position %d = %d\n", count++, n );
    }
  }
  else
  {
    RhinoApp().Print( L"No test data\n" );
  }
}

void CTestArchivePlugIn::PurgeTestData()
{
  m_list.RemoveAll();
}

bool CTestArchivePlugIn::ReadTestArchive( const wchar_t* filename )
{
  if( 0 == filename || 0 == filename[0] )
    return false;

  ON_wString path = filename;
  PathRenameExtension( path.Array(), L".dat" );

  if( !PathFileExists(path) )
  {
    //RhinoApp().Print( L"Error reading test archive - File not found.\n" );
    return false;
  }

  CFile f;
  CFileException e;
  if( !f.Open(path, CFile::modeRead, &e) )
  {
    wchar_t msg[255];
  	memset( msg, 0, sizeof(wchar_t) * 255);
    e.GetErrorMessage( msg, 255 );
    RhinoApp().Print( L"Error reading test archive - %s\n", msg );
    return false;
  }

  try
  {
    CArchive ar( &f, CArchive::load );
    m_list.Serialize( ar );
    ar.Close();
    f.Close();
  }
  catch( CFileException* ex )
  {
    wchar_t msg[255];
  	memset( msg, 0, sizeof(wchar_t) * 255);
    ex->GetErrorMessage( msg, 255 );
    RhinoApp().Print( L"Error reading test archive - %s\n", msg );
    ex->Delete();
  }

  return true;
}

bool CTestArchivePlugIn::WriteTestArchive( const wchar_t* filename )
{
  if( 0 == filename || 0 == filename[0] )
    return false;

  ON_wString path = filename;
  PathRenameExtension( path.Array(), L".dat" );

  CFile f;
  CFileException e;
  if( !f.Open(path, CFile::modeCreate | CFile::modeWrite, &e) )
  {
    wchar_t msg[255];
  	memset( msg, 0, sizeof(wchar_t) * 255);
    e.GetErrorMessage( msg, 255 );
    RhinoApp().Print( L"Error writing test archive - %s\n", msg );
    return false;
  }

  try
  {
    CArchive ar( &f, CArchive::store );
    m_list.Serialize( ar );
    ar.Close();
    f.Close();
  }
  catch( CFileException* ex )
  {
    wchar_t msg[255];
  	memset( msg, 0, sizeof(wchar_t) * 255);
    ex->GetErrorMessage( msg, 255 );
    RhinoApp().Print( L"Error writing test archive - %s\n", msg );
    ex->Delete();
  }

  return true;
}

/////////////////////////////////////////////////////////////////////////////

void CTestArchiveWatcher::OnCloseDocument( CRhinoDoc& doc )
{
  // Since the document is closing, purge our test data. This way,
  // we can start clean if the user opens another document.
   thePlugIn.PurgeTestData();
}

void CTestArchiveWatcher::OnNewDocument( CRhinoDoc& doc )
{
  // Since new documents won't have our test data, generate it.
  thePlugIn.InitTestData();
}

void CTestArchiveWatcher::OnEndOpenDocument( CRhinoDoc& doc, const wchar_t* filename, BOOL bMerge, BOOL bReference )
{
  // Only read our test archive if Rhino is opening a file, not importing a file
  // or attaching a worksession file.
  if( !bMerge && !bReference )
    thePlugIn.ReadTestArchive( filename );
}

void CTestArchiveWatcher::OnEndSaveDocument( CRhinoDoc& doc, const wchar_t* filename, BOOL bExport )
{
  // Only write our test archive if Rhino is saving a file, not exporting a file.
  if( !bExport )
    thePlugIn.WriteTestArchive( filename );
}