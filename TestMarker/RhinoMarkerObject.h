////////////////////////////////////////////////////////////////////////////////////////
// RhinoMarkerObject.h
//

#pragma once

class CRhinoMarkerObject : public CRhinoPointObject
{
  ON_OBJECT_DECLARE(CRhinoMarkerObject);

public:
  CRhinoMarkerObject();                                     // assigns a new object UUID
  CRhinoMarkerObject(const ON_3dmObjectAttributes&);        // assigns a new object UUID
  ~CRhinoMarkerObject();
  CRhinoMarkerObject(const CRhinoMarkerObject&);            // copies source object UUID
  CRhinoMarkerObject(const CRhinoPointObject&);             // copies source object UUID
  CRhinoMarkerObject& operator=(const CRhinoMarkerObject&); // copies source object UUID
  CRhinoMarkerObject& operator=(const CRhinoPointObject&);  // copies source object UUID
  CRhinoMarkerObject& operator=(const ON_3dPoint&);         // leave attributes unchanged.

  // virtual CRhinoObject::Draw override
  void Draw(CRhinoDisplayPipeline&) const;

  // virtual CRhinoObject::Draw override
  void Draw(CRhinoViewport&) const;

  // virtual CRhinoObject::ShortDescription override
  const wchar_t* ShortDescription( bool bPlural ) const;
};