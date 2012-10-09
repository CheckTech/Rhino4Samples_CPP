/////////////////////////////////////////////////////////////////////////////
// PointCloudUserData.h

#pragma once

class CPointCloudUserData : public ON_UserData
{
	ON_OBJECT_DECLARE( CPointCloudUserData );

public:
	CPointCloudUserData();
  ~CPointCloudUserData();

	CPointCloudUserData( const CPointCloudUserData& src );
	CPointCloudUserData& operator=( const CPointCloudUserData& src );

  static ON_UUID Id();
  static ON_UUID PlugInId();

	BOOL GetDescription( ON_wString& description );
  BOOL Archive() const; 
	BOOL Read( ON_BinaryArchive& archive );
	BOOL Write( ON_BinaryArchive& archive ) const;

public:
  // Intensity, ranges from 0 to 65535 (0xffff)
  ON_SimpleArray<unsigned short> m_I;

public:
  // Helper functions
  static bool HasPointCloudUserData( const CRhinoPointCloudObject* object );
  static bool AddPointCloudUserData( CRhinoDoc& doc, const CRhinoPointCloudObject* object, const ON_SimpleArray<unsigned short>& data );
  static bool AddPointCloudUserData( CRhinoDoc& doc, const CRhinoPointCloudObject* object, int data_count, const unsigned short* data );
  static bool SetPointCloudUserData( CRhinoDoc& doc, const CRhinoPointCloudObject* object, const ON_SimpleArray<unsigned short>& data );
  static bool SetPointCloudUserData( CRhinoDoc& doc, const CRhinoPointCloudObject* object, int data_count, const unsigned short* data );
  static bool GetPointCloudUserData( const CRhinoPointCloudObject* object, ON_SimpleArray<unsigned short>& data );
  static bool RemovePointCloudUserData( CRhinoDoc& doc, const CRhinoPointCloudObject* object );

private:
  static bool WriteArray( ON_BinaryArchive& archive, const ON_SimpleArray<unsigned short>& a );
  static bool ReadArray( ON_BinaryArchive& archive, ON_SimpleArray<unsigned short>& a );
};
