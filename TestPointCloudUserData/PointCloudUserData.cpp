/////////////////////////////////////////////////////////////////////////////
// PointCloudUserData.cpp

#include "stdafx.h"
#include "PointCloudUserData.h"
#include "TestPointCloudUserDataPlugIn.h"

ON_OBJECT_IMPLEMENT( CPointCloudUserData, ON_UserData, "189C157D-A950-4A56-AC69-AC9B0BB7A17B" );

ON_UUID CPointCloudUserData::Id()
{
  return CPointCloudUserData::m_CPointCloudUserData_class_id.Uuid();
}

ON_UUID CPointCloudUserData::PlugInId()
{
  return ThePlugIn().PlugInID();
}

CPointCloudUserData::CPointCloudUserData()
{
  m_userdata_uuid = CPointCloudUserData::Id();
  m_application_uuid = CPointCloudUserData::PlugInId();
  m_userdata_copycount = 1;
}

CPointCloudUserData::~CPointCloudUserData()
{
}

CPointCloudUserData::CPointCloudUserData( const CPointCloudUserData& src )
: ON_UserData(src)
{
  m_userdata_uuid = CPointCloudUserData::Id();
  m_application_uuid = CPointCloudUserData::PlugInId();
}

CPointCloudUserData& CPointCloudUserData::operator=( const CPointCloudUserData& src )
{
  if( this != &src )
  {
    m_I.Destroy();
    ON_UserData::operator=( src );
    m_I = src.m_I;
  }
  return *this;
}

BOOL CPointCloudUserData::GetDescription( ON_wString& description )
{
  description = L"PointCloudUserData";
  return true;
}

BOOL CPointCloudUserData::Archive() const 
{
  return true;
}

BOOL CPointCloudUserData::Write( ON_BinaryArchive& archive ) const
{
  int major_version = 1;
  int minor_version = 0;

  bool rc = archive.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, major_version, minor_version );
  if( !rc )
    return false;

  for(;;)
  {
    rc = CPointCloudUserData::WriteArray( archive, m_I );
    if( !rc ) break;

    // TODO

    break;
  }

  if( !archive.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

BOOL CPointCloudUserData::Read( ON_BinaryArchive& archive )
{
  int major_version = 0;
  int minor_version = 0;

  bool rc = archive.BeginRead3dmChunk( TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version );
  if( !rc )
    return false;

  for(;;)
  {
    rc = ( 1 == major_version );
    if( !rc ) break;

    rc = CPointCloudUserData::ReadArray( archive, m_I );
    if( !rc ) break;

    // TODO

    break;
  }

  if( !archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}

bool CPointCloudUserData::WriteArray( ON_BinaryArchive& archive, const ON_SimpleArray<unsigned short>& a )
{
  int count = a.Count();
  if( count < 0 )
    count = 0;
  bool rc = archive.WriteInt( count );
  if( rc && count > 0 )
    rc = archive.WriteShort( count, a.Array() );
  return rc;
}

bool CPointCloudUserData::ReadArray( ON_BinaryArchive& archive, ON_SimpleArray<unsigned short>& a )
{
  a.Empty();
  int count = 0;
  bool rc = archive.ReadInt( &count );
  if( rc && count > 0 )
  {
    a.SetCapacity( count );
    rc = archive.ReadShort( count, a.Array() );
    if( rc )
      a.SetCount( count );
  }
  return rc;
}

/////////////////////////////////////////////////////////////////////////////

bool CPointCloudUserData::HasPointCloudUserData( const CRhinoPointCloudObject* object )
{
  // Validate the object
  if( 0 == object )
    return false;

  // Validate the geometry
  const ON_Geometry* geometry = object->Geometry();
  if( 0 == geometry )
    return false;

  // Get our user data
  CPointCloudUserData* user_data = CPointCloudUserData::Cast( geometry->GetUserData(CPointCloudUserData::Id()) );
  if( 0 == user_data )
    return false;

  return true;
}

bool CPointCloudUserData::AddPointCloudUserData( CRhinoDoc& doc, const CRhinoPointCloudObject* object, const ON_SimpleArray<unsigned short>& data )
{
  return CPointCloudUserData::AddPointCloudUserData( doc, object, data.Count(), data.Array() );
}

bool CPointCloudUserData::AddPointCloudUserData( CRhinoDoc& doc, const CRhinoPointCloudObject* object, int data_count, const unsigned short* data )
{
  // Validate the object and data
  if( 0 == object || 0 == data_count || 0 == data )
    return false;

  // Data count and point cloud count must be the same
  if( data_count != object->PointCloud().PointCount() )
    return false;

  // Validate the geometry
  const ON_Geometry* geometry = object->Geometry();
  if( 0 == geometry )
    return false;

  // Get our user data
  CPointCloudUserData* user_data = CPointCloudUserData::Cast( geometry->GetUserData(CPointCloudUserData::Id()) );
  if( user_data )
    return SetPointCloudUserData( doc, object, data_count, data );

  // Duplicate the object
  CRhinoObject* dupe_object = object->DuplicateRhinoObject();
  if( 0 == dupe_object )
    return false;

  // Get the duplicated geometry
  ON_Geometry* dupe_geometry = const_cast<ON_Geometry*>( dupe_object->Geometry() );
  if( 0 == dupe_geometry )
  {
    delete dupe_object;
    return false;
  }

  // New user data
  user_data = new CPointCloudUserData();
  if( 0 == user_data )
  {
    delete dupe_object;
    return false;
  }

  // Set member variables
  user_data->m_I.Append( data_count, data );

  // Attach user data
  if( 0 == dupe_geometry->AttachUserData(user_data) )
  {
    delete user_data;
    delete dupe_object;
    return false;
  }

  // Replace the object
	if( !doc.ReplaceObject(CRhinoObjRef(object), dupe_object) )
	{
    // user_data will be deleted by dupe_object
    delete dupe_object;
    return false;
  }

  return true;
}

bool CPointCloudUserData::SetPointCloudUserData( CRhinoDoc& doc, const CRhinoPointCloudObject* object, const ON_SimpleArray<unsigned short>& data )
{
  return CPointCloudUserData::SetPointCloudUserData( doc, object, data.Count(), data.Array() );
}

bool CPointCloudUserData::SetPointCloudUserData( CRhinoDoc& doc, const CRhinoPointCloudObject* object, int data_count, const unsigned short* data )
{
  // Validate the object and data
  if( 0 == object || 0 == data_count || 0 == data )
    return false;

  // Data count and point cloud count must be the same
  if( data_count != object->PointCloud().PointCount() )
    return false;

  // Validate the geometry
  const ON_Geometry* geometry = object->Geometry();
  if( 0 == geometry )
    return false;

  // Get our user data
  CPointCloudUserData* user_data = CPointCloudUserData::Cast( geometry->GetUserData(CPointCloudUserData::Id()) );
  if( 0 == user_data )
    return false;

  // Reset pointer
  user_data = 0;

  // Duplicate the object
  CRhinoObject* dupe_object = object->DuplicateRhinoObject();
  if( 0 == dupe_object )
    return false;

  // Get the duplicated geometry
  ON_Geometry* dupe_geometry = const_cast<ON_Geometry*>( dupe_object->Geometry() );
  if( 0 == dupe_geometry )
  {
    delete dupe_object;
    return false;
  }

  // Get the duplicated user data
  user_data = CPointCloudUserData::Cast( dupe_geometry->GetUserData(CPointCloudUserData::Id()) );
  if( 0 == user_data )
  {
    delete dupe_object;
    return false;
  }

  // Set member variables
  user_data->m_I.Empty();
  user_data->m_I.Append( data_count, data );

  // Replace the object
	if( !doc.ReplaceObject(CRhinoObjRef(object), dupe_object) )
	{
    delete dupe_object;
    return false;
  }

  return true;
}

bool CPointCloudUserData::GetPointCloudUserData( const CRhinoPointCloudObject* object, ON_SimpleArray<unsigned short>& data )
{
  // Validate the document and the object
  if( 0 == object )
    return false;

  // Validate the geometry
  const ON_Geometry* geometry = object->Geometry();
  if( 0 == geometry )
    return false;

  // Query the geometry
  CPointCloudUserData* user_data = CPointCloudUserData::Cast( geometry->GetUserData(CPointCloudUserData::Id()) );
  if( 0 == user_data )
    return false;

  data.Empty();
  data.Append( user_data->m_I.Count(), user_data->m_I.Array() );

  return true;
}

bool CPointCloudUserData::RemovePointCloudUserData( CRhinoDoc& doc, const CRhinoPointCloudObject* object )
{
  // Validate the document and the object
  if( 0 == object )
    return false;

  // Validate the geometry
  const ON_Geometry* geometry = object->Geometry();
  if( 0 == geometry )
    return false;

  // Query the geometry
  CPointCloudUserData* user_data = CPointCloudUserData::Cast( geometry->GetUserData(CPointCloudUserData::Id()) );
  if( 0 == user_data )
    return false;

  // Reset pointer
  user_data = 0;

  // Duplicate the object
  CRhinoObject* dupe_object = object->DuplicateRhinoObject();
  if( 0 == dupe_object )
    return false;

  // Get the duplicated geometry
  ON_Geometry* dupe_geometry = const_cast<ON_Geometry*>( dupe_object->Geometry() );
  if( 0 == dupe_geometry )
  {
    delete dupe_object;
    return false;
  }

  // Get the duplicated user data
  user_data = CPointCloudUserData::Cast( dupe_geometry->GetUserData(CPointCloudUserData::Id()) );
  if( 0 == user_data )
  {
    delete dupe_object;
    return false;
  }

  // Detach and delete the user data
  dupe_geometry->DetachUserData( user_data );
  delete user_data;
  user_data = 0;

  // Replace the object
  if( !doc.ReplaceObject(CRhinoObjRef(object), dupe_object) )
  {
    delete dupe_object;
    return false;
  }

  return true;
}
