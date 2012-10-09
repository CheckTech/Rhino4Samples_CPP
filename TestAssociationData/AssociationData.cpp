/////////////////////////////////////////////////////////////////////////////
// AssociationData.cpp


#include "StdAfx.h"
#include "TestAssociationDataPlugIn.h"
#include "AssociationData.h"

///////////////////////////////////////////////////////////////////////////////////////////
// Opennurbs classes that are saved in .3dm files require
// an ON_OBJECT_IMPLEMENT() call in their implmentation.
// Use Microsoft's guidgen to create the id.
ON_OBJECT_IMPLEMENT( AssociationData, ON_UserData, "CCC07EFC-85DB-4ec1-B414-420C533346BA" );

ON_UUID AssociationData::Id()
{
  return AssociationData::m_AssociationData_class_id.Uuid();
}

AssociationData::AssociationData()
{
  // This uuid is the value that must be passed to 
  // ON_Object::GetUserData() to retrieve 
  // this piece of user data.
  m_userdata_uuid = AssociationData::Id();

  // This uuid is used to identify the application that
  // created this piece of user data.  In the case of
  // Rhino, this is the id of the plug-in that created
  // the user data. User data with a nil application id
  // will not be saved in 3dm archives.
  m_application_uuid = TestAssociationDataPlugIn().PlugInID();

  // If m_userdata_copycount is 0, user data is not copied when 
  // object is copied.  If > 0, user data is copied and m_copycount
  // is incremented when parent object is copied. The user data's 
  // operator=() is used to copy.  
  // The default ON_UserData::ON_UserData() constructor sets 
  // m_userdata_copycount to zero.
  m_userdata_copycount = 1; // enable copying

  // initialize data members
  m_first_object_uuid = ON_nil_uuid;
  m_second_object_uuid = ON_nil_uuid;
}

AssociationData::~AssociationData()
{
}

AssociationData::AssociationData( const AssociationData& src )
: ON_UserData(src)
{
  m_userdata_uuid = AssociationData::Id();
  m_application_uuid = TestAssociationDataPlugIn().PlugInID();
	// ON_UserData(src) will copy m_userdata_copycount

  // All other ON_UserData fields are correctly initialized by 
  // the ON_UserData(src) call. In fact, if src is 
  // a AssociationData class, then ALL ON_UserData fields are 
  // correctly initialized by ON_UserData(src).  
  // The next lines are here to handle the rare case 
  // when a class derived from AssociationData is passed as src.

  // copy data members
  m_first_object_uuid = src.m_first_object_uuid;
  m_second_object_uuid = src.m_second_object_uuid;
}

AssociationData& AssociationData::operator=( const AssociationData& src )
{
  // NEVER set m_userdata_uuid or m_application_uuid
  // in an operator=.  These values are set when the
  // class is constructed and should not be changed.
  if ( this != &src )
  {
    // Use the base class to copy all appropriate ON_UserData fields.
    ON_UserData::operator=(src);

    // Explictly copy ONLY members added to the AssociationData class.
    m_first_object_uuid = src.m_first_object_uuid;
    m_second_object_uuid = src.m_second_object_uuid;
  }
  return *this;
}

BOOL AssociationData::GetDescription( ON_wString& description )
{
  description = L"Rhino Metrology - Association Data";
  return true;
}

BOOL AssociationData::Archive() const 
{
  // If false is returned, nothing will be saved in
  // 3dm archives.
  return TRUE;
}

BOOL AssociationData::Write( ON_BinaryArchive& binary_archive ) const
{
  int minor_version = 0;
  bool rc = binary_archive.BeginWrite3dmChunk( TCODE_ANONYMOUS_CHUNK, 1, minor_version );
  if( !rc )
    return false;

  // Write class members like this
  for (;;)
  {
    // version 1.0 fields
    rc = binary_archive.WriteUuid( m_first_object_uuid );
    if (!rc) 
      break;

    rc = binary_archive.WriteUuid( m_second_object_uuid );
    if (!rc) 
      break;

    // If you add data members to AssociationData after you 
    // have released a product, simply increment minor_version
    // by one, and write the new information.  This way you
    // can enhance your user data over several versions of
    // your product without breaking file IO.  It is CRITICAL
    // that once you write something to a customer's .3dm
    // file, you continue to write it the same way for all
    // future versions.
    
    // version 1.1 fields added DD MMM YYYY
    // rc = binary_archive.WriteSomethingNew( ... );
    // if (!rc) 
    //  break;
    // rc = binary_archive.WriteSomethingElseNew( ... );
    // if (!rc) 
    //  break;

    // version 1.2 fields added DD MMM YYYY
    // rc = binary_archive.WriteAnotherSomethingNew( ... );
    // if (!rc) 
    //  break;
    // rc = binary_archive.WriteAnotherSomethingElseNew( ... );
    // if (!rc) 
    //  break;

    break;
  }

  // If BeginWrite3dmChunk() returns true,
  // then EndWrite3dmChunk() must be called, 
  // even if a write operation failed.
  if ( !binary_archive.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

BOOL AssociationData::Read( ON_BinaryArchive& binary_archive )
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = binary_archive.BeginRead3dmChunk( TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version );
  if (!rc)
    return false;

  // Read class members like this
  for (;;)
  {
    rc = ( 1 == major_version );
    if (!rc) 
      break;

    // version 1.0 fields
    rc = binary_archive.ReadUuid( m_first_object_uuid );
    if (!rc) 
      break;

    rc = binary_archive.ReadUuid( m_second_object_uuid );
    if (!rc) 
      break;

    // The code in the comment below demonstrates how to
    // correctly read information added in later releases
    // of your product.
    //if ( minor_version >= 1 )
    //{
    //  // version 1.1 fields added DD MMM YYYY
    //  rc = binary_archive.ReadSomethingNew( ... );
    //  if (!rc) 
    //    break;
    //  rc = binary_archive.ReadSomethingElseNew( ... );
    //  if (!rc)
    //    break;
    //  
    //  if ( minor_version >= 2 )
    //  {
    //    // version 1.2 fields added DD MMM YYYY
    //    rc = binary_archive.ReadAnotherSomethingNew( ... );
    //    if (!rc) 
    //        break;
    //    rc = binary_archive.ReadAnotherSomethingElseNew( ... );
    //    if (!rc) 
    //        break;
    //  }
    //}

    break;
  }

  // If BeginRead3dmChunk() returns true,
  // then EndRead3dmChunk() must be called, 
  // even if a read operation failed.
  if ( !binary_archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}


/////////////////////////////////////////////////////////////////////////////
// Static helper functions

bool AssociationData::HasData( const CRhinoObject* object )
{
  bool rc = false;
  if( object )
  {
    const CRhinoObjectAttributes& attributes = object->Attributes();
    AssociationData* user_data = AssociationData::Cast( attributes.GetUserData(AssociationData::Id()) );
    if( user_data )
      rc = true;
  }
  return rc;
}

bool AssociationData::AddData( CRhinoDoc& doc, const CRhinoObject* object, ON_UUID first_object_uuid, ON_UUID second_object_uuid )
{
  bool rc = false;

  if( 0 == object )
    return rc;

  const CRhinoObjectAttributes& attributes = object->Attributes();
  AssociationData* user_data = AssociationData::Cast( attributes.GetUserData(AssociationData::Id()) );
  if( user_data )
    return SetData( doc, object, first_object_uuid, second_object_uuid );

  user_data = new AssociationData();
  if( user_data )
  {
    user_data->m_first_object_uuid = first_object_uuid;
    user_data->m_second_object_uuid = second_object_uuid;

    ON_3dmObjectAttributes new_attributes( object->Attributes() );
    if( new_attributes.AttachUserData(user_data) )
    {
      if( doc.ModifyObjectAttributes( CRhinoObjRef(object), new_attributes) )
        rc = true;
    }
    else
    {
      delete user_data;
      user_data = 0;
    }
  }

  return rc;
}

bool AssociationData::SetData( CRhinoDoc& doc, const CRhinoObject* object, ON_UUID first_object_uuid, ON_UUID second_object_uuid )
{
  bool rc = false;

  if( 0 == object )
    return rc;

  const CRhinoObjectAttributes& attributes = object->Attributes();
  AssociationData* user_data = AssociationData::Cast( attributes.GetUserData(AssociationData::Id()) );
  if( user_data )
  {
    ON_3dmObjectAttributes new_attributes( object->Attributes() );
    user_data = AssociationData::Cast( new_attributes.GetUserData(AssociationData::Id()) );
    if( user_data )
    {
      user_data->m_first_object_uuid = first_object_uuid;
      user_data->m_second_object_uuid = second_object_uuid;

      if( doc.ModifyObjectAttributes( CRhinoObjRef(object), new_attributes) )
        rc = true;
    }
  }

  return rc;
}

bool AssociationData::GetData( const CRhinoObject* object, ON_UUID& first_object_uuid, ON_UUID& second_object_uuid )
{
  bool rc = false;
  if( object )
  {
    const CRhinoObjectAttributes& attributes = object->Attributes();
    AssociationData* user_data = AssociationData::Cast( attributes.GetUserData(AssociationData::Id()) );
    if( user_data )
    {
      first_object_uuid = user_data->m_first_object_uuid;
      second_object_uuid = user_data->m_second_object_uuid;
      rc = true;
    }
  }
  return rc;
}

bool AssociationData::RemoveData( CRhinoDoc& doc, const CRhinoObject* object )
{
  bool rc = false;
  if( object )
  {
    const CRhinoObjectAttributes& attributes = object->Attributes();
    AssociationData* user_data = AssociationData::Cast( attributes.GetUserData(AssociationData::Id()) );
    if( user_data )
    {
      ON_3dmObjectAttributes new_attributes( object->Attributes() );
      user_data = AssociationData::Cast( new_attributes.GetUserData(AssociationData::Id()) );
      if( user_data && new_attributes.DetachUserData(user_data) )
      {
        delete user_data;
        user_data = 0;
        doc.ModifyObjectAttributes( CRhinoObjRef(object), new_attributes );
        rc = true;
      }
    }
  }
 
  return rc;
}
