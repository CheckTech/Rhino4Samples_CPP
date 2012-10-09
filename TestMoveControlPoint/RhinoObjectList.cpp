#include "stdafx.h"
#include "RhinoObjectList.h"

static int CompareRhinoObjectPtr(CRhinoObject* const* a, CRhinoObject* const* b)
{
	if( *a < *b ) 
    return -1;
	if( *b < *a ) 
    return  1;
	return 0;
}

int CRhinoObjectList::AddObjects( const CRhinoGetObject& go )
{
  int rc = 0;
  int count = ( go.Result() == CRhinoGet::object ) ? go.ObjectCount() : 0;
  if( count < 1 )
    rc = 0;
  else
  {
    for( int i = 0; i < count; i++ )
    {
      if( AddObject(go.Object(i)) )
        rc++;
    }
  }
  return rc;
}

int CRhinoObjectList::AddObject( const CRhinoObjRef& object_ref )
{
  int rc = AddObject( object_ref.Object() );
  if( rc && object_ref.ProxyReferenceCount() > 0 )
    m_proxy_objref.Append( object_ref );
  return rc;
}

int CRhinoObjectList::AddObject( const CRhinoObject* object )
{
  int rc = 0;

  CRhinoObject* obj = const_cast<CRhinoObject*>(object);
  if( 0 == obj )
    return rc;

  if( obj->ObjectType() == ON::grip_object )
  {
    CRhinoGripObject* grip = CRhinoGripObject::Cast( obj );
    if( grip )
    {
      m_grips.Append( grip );
      rc = 2;
    }
  }
  else
  {
    if( m_objects.Search(obj) < 0 )
    {
      m_objects.Append( obj );
      rc = 1;
    }
  }

  int i, count = m_grips.Count();
  if( count > 0 )
  {
    CRhinoObject* grip_owner = 0;
    ON_SimpleArray<CRhinoObject*> owners( count );
    for( i = 0; i < count; i++ )
    {
      grip_owner = m_grips[i]->Owner();
      if( grip_owner && grip_owner->m_grips )
        owners.Append( m_grips[i]->Owner() );
    }
    owners.QuickSort( CompareRhinoObjectPtr );
    count = owners.Count();
    int j = count;
    for( i = 0; i < count; i = j)
    {
      if( owners[i] )
      {
        m_grip_owners.Append( owners[i] );
        owners[i]->m_grips->GetCaptives(m_grip_captives);
      }
      for( j = i + 1; j < count && owners[j] == owners[i]; j++ )
      {
        // empty...
      }
    }

    if( m_grip_owners.Count() < 1 )
    {
      m_grips.SetCount(0);
    }
    else
    {
      m_grip_captives.QuickSort( CompareRhinoObjectPtr );
      count = m_objects.Count();
      i = 0; 
      while( i < m_objects.Count() )
      {
        obj = m_objects[i];
        if(    m_grip_owners.BinarySearch(&obj, CompareRhinoObjectPtr) >= 0
            || m_grip_captives.BinarySearch(&obj, CompareRhinoObjectPtr) >= 0)
        {
          m_objects.Remove(i);
        }
        else
        {
          i++;
        }
      }
    }
  }

  return rc;
}

void CRhinoObjectList::Transform( CRhinoDoc& doc, const ON_Xform& xform, bool bCopy, bool bAutoHistory )
{
  int i = 0, j = 0;

  CRhinoKeepKinkySurfaces keep_kinky_srfs;
  ON_2dexMap group_map;

  for( i = 0; i < m_grips.Count(); i++ )
    m_grips[i]->MoveGrip( xform );

  m_objects.QuickSort( CompareRhinoObjectPtr );
  m_grip_owners.QuickSort( CompareRhinoObjectPtr );

  for( i = 0; i < m_objects.Count(); i++ )
  {
    CRhinoObject* old_object = m_objects[i];
    if( 0 == old_object )
      continue;

    CRhinoCopyGripsHelper gripshelper;
    gripshelper.SaveGripStatus( old_object );

    CRhinoObject* transformed_object = doc.TransformObject( CRhinoObjRef(old_object), xform, bCopy ? false : true, true, bAutoHistory ? true : false );
    if( 0 == transformed_object )
      continue;

    if( bCopy )
      RhinoUpdateObjectGroups( transformed_object, group_map );

    gripshelper.RestoreGripStatus( transformed_object );
  }

  for( i = 0; i < m_grip_owners.Count(); i++ )
    RhinoUpdateGripOwner( m_grip_owners[i], bCopy ? true : false, &group_map );
}

void CRhinoObjectList::ResetGrips()
{
  int i;

  for( i = 0; i < m_grip_owners.Count(); i++ )
  {
    CRhinoObject* owner = m_grip_owners[i];
    if( owner && owner->m_grips )
    {
      owner->m_grips->Reset();
    }
  }

  for( i = 0; i < m_grip_captives.Count(); i++ )
  {
    CRhinoObject* captive = m_grip_captives[i];
    if( captive && captive->m_grips )
      captive->m_grips->Reset();
  }
}