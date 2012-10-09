#pragma once

class CRhinoObjectList
{
public:
  CRhinoObjectList() {}
  ~CRhinoObjectList() {}

  // Returns: number of objects and grips added to lists
  int AddObjects( const CRhinoGetObject& go );

  // Returns: 0 = not added, 1 = added as object, 2 = added as grip
  int AddObject( const CRhinoObjRef& object_ref );

  // Returns: 0 = not added, 1 = added as object, 2 = added as grip
  int AddObject( const CRhinoObject* object );

  void Transform( CRhinoDoc& doc, const ON_Xform& xform, bool bCopy, bool bAutoHistory );
  void ResetGrips();

public:
  ON_SimpleArray<CRhinoObject*> m_objects;       // regular objects 
  ON_SimpleArray<CRhinoGripObject*> m_grips;     // grips
  ON_SimpleArray<CRhinoObject*> m_grip_owners;   // objects the grips will change
  ON_SimpleArray<CRhinoObject*> m_grip_captives; // grip captives (objects in cages with grips on)

private:
  ON_ClassArray<CRhinoObjRef> m_proxy_objref;
};