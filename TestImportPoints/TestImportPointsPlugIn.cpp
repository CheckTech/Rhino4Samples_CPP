/////////////////////////////////////////////////////////////////////////////
// TestImportPointsPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "TestImportPointsPlugIn.h"

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

// The one and only CTestImportPointsPlugIn object
static CTestImportPointsPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CTestImportPointsPlugIn definition

CTestImportPointsPlugIn::CTestImportPointsPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CTestImportPointsPlugIn::~CTestImportPointsPlugIn()
{
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CTestImportPointsPlugIn::PlugInName() const
{
  return L"Test Import Points";
}

const wchar_t* CTestImportPointsPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CTestImportPointsPlugIn::PlugInID() const
{
  // {42568298-7860-411C-8A4A-78F9E4B21AB8}
  static const GUID TestImportPointsPlugIn_UUID =
  { 0x42568298, 0x7860, 0x411C, { 0x8A, 0x4A, 0x78, 0xF9, 0xE4, 0xB2, 0x1A, 0xB8 } };
  return TestImportPointsPlugIn_UUID;
}

BOOL CTestImportPointsPlugIn::OnLoadPlugIn()
{
  return CRhinoFileImportPlugIn::OnLoadPlugIn();
}

void CTestImportPointsPlugIn::OnUnloadPlugIn()
{
  CRhinoFileImportPlugIn::OnUnloadPlugIn();
}

/////////////////////////////////////////////////////////////////////////////
// File import overrides

void CTestImportPointsPlugIn::AddFileType( ON_ClassArray<CRhinoFileType>& extensions, const CRhinoFileReadOptions& options )
{
  CRhinoFileType ft( PlugInID(), L"Test Points File (*.pts)", L"pts" );
  extensions.Append( ft );
}

BOOL CTestImportPointsPlugIn::ReadFile( const wchar_t* filename, int index, CRhinoDoc& doc, const CRhinoFileReadOptions& options )
{
	CStdioFile* file = 0;

  TRY
  {
		file = new CStdioFile( filename, CFile::modeRead | CFile::shareDenyNone | CFile::typeText );
    if( !file )
      return FALSE;

    ON_3dPointArray point_list;
    CString string;
    wchar_t delimiter = ',';

    while( file->ReadString(string) )
    {
      string.TrimLeft();
      string.TrimRight();
      string.Remove( '\r' );
      string.Remove( '\n' );
      string.Remove( '"' );

      ON_3dPoint pt;
      if( ParsePointValue(string, delimiter, pt) )
        point_list.Append( pt );
    }

    if( point_list.Count() > 0 )
    {
      int i;
      for( i = 0; i < point_list.Count(); i++ )
        doc.AddPointObject( point_list[i] );
    }

    file->Close();
    delete file;
    file = 0;

    doc.Redraw();

    return TRUE;
  }

	CATCH( CFileException, e )
	{
		e->ReportError();
		if( file )
		{
			file->Close();
			delete file;
      file = 0;
		}
		return FALSE;
	}

	AND_CATCH( CMemoryException, pEx )
	{
		AfxAbort();
	}

	END_CATCH

	return FALSE;
}

BOOL CTestImportPointsPlugIn::ParsePointValue( const wchar_t* string, wchar_t delimiter, ON_3dPoint& pt )
{
  if( 0 == string || 0 == string[0] )
    return FALSE;

  ON_wString tag( delimiter );
  ON_3dPoint point;
  double d = 0.0;

  wchar_t* token = wcstok( (wchar_t*)string, tag );
  if( token && ParseRealValue(token, d) )
    point.x = d;
  else
    return FALSE;

  token = wcstok( 0, tag );
  if( token && ParseRealValue(token, d) )
    point.y = d;
  else
    return FALSE;

  token = wcstok( 0, tag );
  if( token )
  {
    if( ParseRealValue(token, d) )
      point.z = d;
    else
      return FALSE;
  }
  else
    point.z = 0.0;

  pt = point;

  return TRUE;
}

BOOL CTestImportPointsPlugIn::ParseRealValue( const wchar_t* string, double& value )
{
  if( 0 == string || 0 == string[0] )
    return FALSE;

	while( *string == ' ' || *string == '\t' )
		string++;

	wchar_t first = string[0];
	double d = wcstod( string, (wchar_t**)&string );
	if( d == 0.0 && first != '0' )
    return FALSE;
	
  while( *string == ' ' || *string == '\t' )
		string++;

	if( *string != '\0' )
    return FALSE;

  value = d;

  return TRUE;
}