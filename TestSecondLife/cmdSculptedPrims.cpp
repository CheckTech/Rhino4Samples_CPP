/////////////////////////////////////////////////////////////////////////////
// cmdSculptedPrims.cpp

#include "StdAfx.h"

CRhinoObjectAttributes Attribs( CRhinoDoc& doc, const wchar_t* texture_name )
{
  CRhinoObjectAttributes attribs;
  
  if( 0 == texture_name || 0 == texture_name[0] )
    return attribs;

  ON_Material mat;
  mat.AddTexture( texture_name, ON_Texture::bitmap_texture );
  attribs.m_material_index = doc.m_material_table.AddMaterial( mat );
  attribs.SetMaterialSource( ON::material_from_object );

  return attribs;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN SculptedPrimSurf command
//

class CCommandSculptedPrimSurf : public CRhinoCommand
{
public:
  UUID CommandUUID()
  {
    // {F218D4A5-C866-408e-B604-1D213947D1BE}
    static const GUID SculptedPrimSurfCommand_UUID = 
    { 0xf218d4a5, 0xc866, 0x408e, { 0xb6, 0x4, 0x1d, 0x21, 0x39, 0x47, 0xd1, 0xbe } };
    return SculptedPrimSurfCommand_UUID;
  }
  const wchar_t* EnglishCommandName() { return L"SculptedPrimSurf"; }
  CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

private:
  void SetUniformKnotVector( double* knots, int order, int cv_count );
  ON_wString m_bitmapdir;
};

static class CCommandSculptedPrimSurf theSculptedPrimSurfCommand;

void CCommandSculptedPrimSurf::SetUniformKnotVector( double *knots, int order, int cv_count)
{
  if( cv_count < order )
    return;
 
  int degree = order - 1;
  int numknots = ON_KnotCount( order, cv_count);
  double knotvalue = 0.0;
  
  int i;
  for( i = 0; i < degree; i++ )
  {
    knots[i] = knotvalue;
  }
 
  for( i = degree; i < numknots - degree; i++ )
  {
    knotvalue += 1.0;
    knots[i] = knotvalue;
  }
  
  // set the last degree many knots to the next value.
  
  knotvalue += 1.0;
  
  for( i = numknots - degree; i < numknots; i++)
    knots[i] = knotvalue;
}

CRhinoCommand::result CCommandSculptedPrimSurf::RunCommand( const CRhinoCommandContext& context )
{
  ON_NurbsSurface* pSrf = ON_NurbsSurface::New();
  if( 0 == pSrf )
    return CRhinoCommand::failure;

  CRhinoDib dib;
  if( !dib.ReadFromFile() )
    return CRhinoCommand::cancel;

  int u, width = dib.Width();
  int v, height = dib.Height();

	pSrf->Create( 3, 0, 4, 4, width, height );

	pSrf->ReserveKnotCapacity( 0, 4*(width-2) );
	pSrf->ReserveKnotCapacity( 1, 4*(height-2) );

  SetUniformKnotVector( pSrf->m_knot[0], pSrf->m_order[0], pSrf->m_cv_count[0] );
  SetUniformKnotVector( pSrf->m_knot[1], pSrf->m_order[1], pSrf->m_cv_count[1] );

  ON_3dPoint pt;
  int r, g, b;
  for( v = 0; v < height; v++ )
  {
    for( u = 0; u < width; u++ )
    {	
      if( dib.GetPixel(u, v, r, g, b) )
      {
        pt.x = (float)( (r - 128.0) / 256.0 );
        pt.y = (float)( (g - 128.0) / 256.0 );
        pt.z = (float)( (b - 128.0) / 256.0 );
      }

      pSrf->SetCV( u, v, pt );
    }
  }

  CRhinoObjectAttributes attribs = Attribs( context.m_doc, dib.LastSaveName() );
  CRhinoSurfaceObject* pSrfObj = new CRhinoSurfaceObject( attribs );
  if( pSrfObj )
  {
    pSrfObj->SetSurface( pSrf );
    context.m_doc.AddObject( pSrfObj );
  }
  else
  {
    delete pSrf;
    pSrf = 0;
  }

  context.m_doc.Redraw();
  return CRhinoCommand::success;
}

//
// BEGIN SculptedPrimSurf command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN SculptedPrimMesh command
//

class CCommandSculptedPrimMesh : public CRhinoCommand
{
public:
  UUID CommandUUID()
  {
    // {6F6E1FCC-4A4C-47c5-9527-69F359743B78}
    static const GUID SculptedPrimMeshCommand_UUID = 
    { 0x6f6e1fcc, 0x4a4c, 0x47c5, { 0x95, 0x27, 0x69, 0xf3, 0x59, 0x74, 0x3b, 0x78 } };
    return SculptedPrimMeshCommand_UUID;
  }
  const wchar_t* EnglishCommandName() { return L"SculptedPrimMesh"; }
  CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

private:
  ON_wString m_bitmapdir;
};

static class CCommandSculptedPrimMesh theSculptedPrimMeshCommand;

CRhinoCommand::result CCommandSculptedPrimMesh::RunCommand( const CRhinoCommandContext& context )
{
  ON_Mesh* pMesh = new ON_Mesh;
  if (0 == pMesh)
    return CRhinoCommand::failure;

  CRhinoDib dib;
  if (!dib.ReadFromFile())
    return CRhinoCommand::cancel;

  int i, width = dib.Width();
  int j, height = dib.Height();
  pMesh->m_V.Reserve(width*height);
  pMesh->m_V.SetCount(width*height);
  pMesh->m_T.Reserve(width*height);
  pMesh->m_T.SetCount(width*height);
  pMesh->m_F.Reserve(width*height);
  
  int r, g, b;
  for (j=0; j<height; j++)
  {
    for (i=0; i<width; i++)
    {
      ON_3fPoint& pt = pMesh->m_V[j*width + i];
      if (dib.GetPixel(i, j, r, g, b))
      {
        pt.x = (float)((r-128.0)/256.0);
        pt.y = (float)((g-128.0)/256.0);
        pt.z = (float)((b-128.0)/256.0);
      }

      ON_2fPoint& pt2 = pMesh->m_T[j*width + i];
      pt2.x = (float)i/width;
      pt2.y = (float)j/height;
    }
  }

  ON_MeshFace face;
  for (j=0; j<(height-1); j++)
  {
    for (i=0; i<width; i++)
    {
      face.vi[0] = j*width + i;
      face.vi[1] = j*width + (i+1)%width;
      face.vi[2] = face.vi[3] = (j+1)*width + i;
      pMesh->m_F.Append(face);

      face.vi[0] = (j+1)*width + i;
      face.vi[1] = j*width + (i+1)%width;
      face.vi[2] = face.vi[3] = (j+1)*width + (i+1)%width;
      pMesh->m_F.Append(face);
    }
  }

  CRhinoObjectAttributes attribs = Attribs(context.m_doc, dib.LastSaveName());
  pMesh->ComputeVertexNormals();
  pMesh->Compact();

  CRhinoMeshObject* pMeshObj = new CRhinoMeshObject(attribs);
  if (0 == pMeshObj)
  {
    delete pMesh;
    return CRhinoCommand::failure;
  }

  pMeshObj->SetMesh(pMesh);
  context.m_doc.AddObject(pMeshObj);

  context.m_doc.Redraw();
  return CRhinoCommand::success;
}
//
// BEGIN SculptedPrimMesh command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN MakeSculptedPrim command
//

class CCommandMakeSculptedPrim : public CRhinoCommand
{
public:
  CCommandMakeSculptedPrim();

  UUID CommandUUID()
  {
    // {5964B884-7CF0-49be-A43D-7543FCE5545A}
    static const GUID MakeSculptedPrimCommand_UUID = 
    { 0x5964b884, 0x7cf0, 0x49be, { 0xa4, 0x3d, 0x75, 0x43, 0xfc, 0xe5, 0x54, 0x5a } };
    return MakeSculptedPrimCommand_UUID;
  }
  const wchar_t* EnglishCommandName() { return L"MakeSculptedPrim"; }
  CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

private:
  int m_Width;
  int m_Height;
  ON_wString m_bitmapdir;
};

CCommandMakeSculptedPrim::CCommandMakeSculptedPrim()
{
  m_Width = 64;
  m_Height = 64;
}

static class CCommandMakeSculptedPrim theMakeSculptedPrimCommand;

CRhinoCommand::result CCommandMakeSculptedPrim::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.AddCommandOptionInteger( RHCMDOPTNAME(L"Width"), &m_Width );
  go.AddCommandOptionInteger( RHCMDOPTNAME(L"Height"), &m_Height );
  go.SetGeometryFilter( CRhinoGetObject::surface_object );

  CRhinoGet::result rs = CRhinoGet::option;
  
  while( rs == CRhinoGet::option )
    rs = go.GetObjects(1,1);

  if( rs != CRhinoGet::object || 1 != go.ObjectCount() )
    return CRhinoCommand::cancel; 

  const ON_Surface* pSurf = go.Object(0).Surface();
  if( 0 == pSurf )
    return CRhinoCommand::failure; 

  // get a transform that will moved evaluated point to center around origin
  ON_Xform translate;
  translate.Translation( ON_3dPoint(0.0,0.0,0.0) - pSurf->BoundingBox().Center() );

  // determine scale factor to make sure all points are within a unit centered at the origin
  double dMax = pSurf->BoundingBox().m_max.x - pSurf->BoundingBox().m_min.x;
  if( dMax < pSurf->BoundingBox().m_max.y - pSurf->BoundingBox().m_min.y )
    dMax = pSurf->BoundingBox().m_max.y - pSurf->BoundingBox().m_min.y;
  if( dMax < pSurf->BoundingBox().m_max.z - pSurf->BoundingBox().m_min.z )
    dMax = pSurf->BoundingBox().m_max.z - pSurf->BoundingBox().m_min.z;

  CRhinoDib dib( m_Width, m_Height, 16 );
  int u, v, r, g, b;
  double s, t;
  double ustart = pSurf->Domain(0).m_t[0];
  double vstart = pSurf->Domain(1).m_t[0];
  double udiff = (pSurf->Domain(0).m_t[1]-pSurf->Domain(0).m_t[0])/m_Width;
  double vdiff = (pSurf->Domain(1).m_t[1]-pSurf->Domain(1).m_t[0])/m_Height;
  bool bAddPoints = false;
  for (v=0; v<m_Height; v++)
  {
    t = vstart + v*vdiff;
    for (u=0; u<m_Width; u++)
    {
      s = ustart + u*udiff;
      ON_3dPoint& pt = pSurf->PointAt(s, t);

      //move and scale result to fit within a unit cubed centered at the origin
      pt.Transform(translate);
      pt /= dMax;

      r = (int)(pt.x*256+128);
      g = (int)(pt.y*256+128);
      b = (int)(pt.z*256+128);
      dib.SetPixel(u, v, r, g, b);

#ifdef _DEBUG
      if (true == bAddPoints)
        context.m_doc.AddPointObject(ON_3dPoint(r, g, b));
#endif
    }
  }

  //context.m_doc.Redraw();

  if( dib.WriteToFile() )
    return CRhinoCommand::success;

  return CRhinoCommand::failure;
}

//
// BEGIN MakeSculptedPrim command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
