/////////////////////////////////////////////////////////////////////////////
// RhinoMarkerObject.cpp
//

#include "StdAfx.h"
#include "RhinoMarkerObject.h"

ON_OBJECT_IMPLEMENT(CRhinoMarkerObject, CRhinoPointObject, "FCE929CC-B7B3-410C-A9A3-F2E8F509A9D9")

CRhinoMarkerObject::CRhinoMarkerObject()
: CRhinoPointObject()
{
}

CRhinoMarkerObject::CRhinoMarkerObject(const ON_3dmObjectAttributes& att)
: CRhinoPointObject(att)
{
}

CRhinoMarkerObject::~CRhinoMarkerObject()
{
}

CRhinoMarkerObject::CRhinoMarkerObject(const CRhinoMarkerObject& src) 
: CRhinoPointObject(src)
{
}

CRhinoMarkerObject::CRhinoMarkerObject(const CRhinoPointObject& src) 
: CRhinoPointObject(src)
{
}

CRhinoMarkerObject& CRhinoMarkerObject::operator=(const CRhinoMarkerObject& src)
{
  if( &src != this ) 
    CRhinoPointObject::operator=(src);
  return *this;
}

CRhinoMarkerObject& CRhinoMarkerObject::operator=(const CRhinoPointObject& src)
{
  if( &src != this ) 
    CRhinoPointObject::operator=(src);
  return *this;
}

CRhinoMarkerObject& CRhinoMarkerObject::operator=(const ON_3dPoint& pt)
{
  CRhinoPointObject::operator=(pt);
  return *this;
}

void CRhinoMarkerObject::Draw(CRhinoDisplayPipeline& dp) const
{
  int size_in_pixels = 5;
  CRhinoViewport& vp = dp.GetRhinoVP();
  double pixels_per_unit = 0.0;
  if( vp.m_v.m_vp.GetWorldToScreenScale(vp.m_v.m_target, &pixels_per_unit) )
  {
    double units_per_pixel = 1.0 / pixels_per_unit;
    const ON_Plane& plane = vp.ConstructionPlane().m_plane;
    ON_3dVector vx = units_per_pixel * size_in_pixels * plane.xaxis;
    ON_3dVector vy = units_per_pixel * size_in_pixels * plane.yaxis;
    dp.DrawLine( m_point.point - vx, m_point.point + vx );
    dp.DrawLine( m_point.point - vy, m_point.point + vy );
  }
}

void CRhinoMarkerObject::Draw(CRhinoViewport& vp) const
{
  CRhinoDisplayPipeline* dp = vp.DisplayPipeline();
  if( dp )
    dp->DrawObject( this );
}

const wchar_t* CRhinoMarkerObject::ShortDescription(bool bPlural) const
{
  return bPlural ? L"marker objects" : L"marker object";
}
