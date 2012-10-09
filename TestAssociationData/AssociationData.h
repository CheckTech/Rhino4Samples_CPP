/////////////////////////////////////////////////////////////////////////////
// AssociationData.h

#pragma once

/////////////////////////////////////////////////////////////////////////////
// AssociationData

class AssociationData : public ON_UserData
{
  // Opennurbs classes that are saved in .3dm files require
  // an ON_OBJECT_DECLARE call in their declaration.
  ON_OBJECT_DECLARE( AssociationData );

public:
  // Static helper functions
  static bool HasData( const CRhinoObject* object );
  static bool AddData( CRhinoDoc& doc, const CRhinoObject* object, ON_UUID first_object_uuid, ON_UUID second_object_uuid );
  static bool SetData( CRhinoDoc& doc, const CRhinoObject* object, ON_UUID first_object_uuid, ON_UUID second_object_uuid );
  static bool GetData( const CRhinoObject* object, ON_UUID& first_object_uuid, ON_UUID& second_object_uuid );
  static bool RemoveData( CRhinoDoc& doc, const CRhinoObject* object );

public:

  /*
  Returns:
    Uuid used to identify this type of user data.
    This is the value saved in m_userdata_uuid and
    passed to ON_Object::GetUserData().
  */
  static ON_UUID Id();

  AssociationData();
  ~AssociationData();

  // NOTE WELL:
  //   Because the members of this class are class are types 
  //   that have fully functional copy constructors and 
  //   operator=s, it is NOT necessary to provide an explicit
  //   a copy constructor and operator=.  In fact, it would 
  //   be best to use the ones C++ generates. 
  //   They are included in this example to demonstrate the
  //   correct way to implement a copy constructor and
  //   operator= because this is a task that trips up
  //   many people that attempt to implement them.
  AssociationData( const AssociationData& src );
  AssociationData& operator=( const AssociationData& src );

  // override virtual ON_UserData::GetDescription()
  BOOL GetDescription( ON_wString& description );

  // override virtual ON_UserData::Archive()
  BOOL Archive() const; 

  // override virtual ON_UserData::Write()
  BOOL Write( ON_BinaryArchive& binary_archive ) const;

  // override virtual ON_UserData::Read()
  BOOL Read( ON_BinaryArchive& binary_archive );

public:
 ON_UUID m_first_object_uuid;
 ON_UUID m_second_object_uuid;
};