/////////////////////////////////////////////////////////////////////////////
// MarkerPlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "StdAfx.h"
#include "MarkerPlugIn.h"
#include "RhinoMarkerObject.h"

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

/////////////////////////////////////////////////////////////////////////////
// CMarkerPlugIn definition

CMarkerPlugIn::CMarkerPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CMarkerPlugIn::~CMarkerPlugIn()
{
}

// The one and only CMarkerPlugIn object
static CMarkerPlugIn thePlugIn;

CMarkerPlugIn& MarkerPlugIn()
{ 
  return thePlugIn; 
}

const wchar_t* CMarkerPlugIn::PlugInName() const
{
  return L"Marker";
}

const wchar_t* CMarkerPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CMarkerPlugIn::PlugInID() const
{
  // {EAC08E4B-2C8D-46C6-9515-F3AA430F4998}
  static const GUID MarkerPlugIn_UUID =
  { 0xEAC08E4B, 0x2C8D, 0x46C6, { 0x95, 0x15, 0xF3, 0xAA, 0x43, 0xF, 0x49, 0x98 } };
  return MarkerPlugIn_UUID;
}

BOOL CMarkerPlugIn::OnLoadPlugIn()
{
  return TRUE;
}

void CMarkerPlugIn::OnUnloadPlugIn()
{
}

BOOL CMarkerPlugIn::CallWriteDocument(const CRhinoFileWriteOptions& options)
{
  m_markers.Empty();

  CRhinoObjectIterator it( CRhinoObjectIterator::undeleted_objects, CRhinoObjectIterator::active_objects  );
  CRhinoObject* obj = 0;
  for( obj = it.First(); obj; obj = it.Next() )
  {
    CRhinoMarkerObject* marker = CRhinoMarkerObject::Cast( obj );
    if( marker )
      m_markers.AddUuid( marker->Attributes().m_uuid );
  }
  return (m_markers.Count() > 0) ? true : false;
}

BOOL CMarkerPlugIn::WriteDocument(CRhinoDoc& doc, ON_BinaryArchive& archive, const CRhinoFileWriteOptions& options)
{
  int minor_version = 0;
  bool rc = archive.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 1, minor_version );
  if( !rc )
    return false;

  for(;;)
  {
    rc = m_markers.Write( archive );
    if( !rc ) break;

    // TODO...

    break;
  }

  if( !archive.EndWrite3dmChunk() )
    rc = false;

  m_markers.Empty();

  return rc;
}

BOOL CMarkerPlugIn::ReadDocument(CRhinoDoc& doc, ON_BinaryArchive& archive, const CRhinoFileReadOptions& options)
{
  m_markers.Empty();

  int major_version = 0;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk( TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version );
  if( !rc )
    return false;

  // Read class members like this
  for(;;)
  {
    rc = ( 1 == major_version );
    if( !rc ) break;

    rc = m_markers.Read( archive );
    if( !rc ) break;

    // TODO...

    break;
  }

  if( !archive.EndRead3dmChunk() )
    rc = false;

  if( m_markers.Count() )
  {
    // Convert points to markers
    CRhinoObjectIterator it( CRhinoObjectIterator::undeleted_objects, CRhinoObjectIterator::active_objects  );
    CRhinoObject* obj = 0;
    for( obj = it.First(); obj; obj = it.Next() )
    {
      CRhinoPointObject* point = CRhinoPointObject::Cast( obj );
      if( point && m_markers.FindUuid(point->Attributes().m_uuid) )
      {
        CRhinoMarkerObject* marker = new CRhinoMarkerObject(*point);
        doc.ReplaceObject( CRhinoObjRef(point), marker, true );
      }
    }

    m_markers.Empty();
    doc.Redraw();
  }

  return rc;
}
