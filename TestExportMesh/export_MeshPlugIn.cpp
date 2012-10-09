/////////////////////////////////////////////////////////////////////////////
// export_MeshPlugIn.cpp

#include "StdAfx.h"
#include "export_MeshPlugIn.h"

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

// The one and only Cexport_MeshPlugIn object
static Cexport_MeshPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// Cexport_MeshPlugIn definition

Cexport_MeshPlugIn::Cexport_MeshPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
  m_mesh_ui_style = 0;
}

Cexport_MeshPlugIn::~Cexport_MeshPlugIn()
{
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* Cexport_MeshPlugIn::PlugInName() const
{
  return L"Sample Mesh Export Plug-in";
}

const wchar_t* Cexport_MeshPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID Cexport_MeshPlugIn::PlugInID() const
{
  // {4A27409A-7287-419D-A557-5A2E59FBE665}
  static const GUID export_MeshPlugIn_UUID =
  { 0x4A27409A, 0x7287, 0x419D, { 0xA5, 0x57, 0x5A, 0x2E, 0x59, 0xFB, 0xE6, 0x65 } };
  return export_MeshPlugIn_UUID;
}

BOOL Cexport_MeshPlugIn::OnLoadPlugIn()
{
  return CRhinoFileExportPlugIn::OnLoadPlugIn();
}

void Cexport_MeshPlugIn::OnUnloadPlugIn()
{
  CRhinoFileExportPlugIn::OnUnloadPlugIn();
}

/////////////////////////////////////////////////////////////////////////////
// Optional overrides
  
void Cexport_MeshPlugIn::LoadProfile( LPCTSTR lpszSection, CRhinoProfileContext& pc )
{
  pc.LoadProfileMeshParameters( lpszSection, L"mesh_parameters", &m_mesh_parameters );
  pc.LoadProfileInt( lpszSection, L"mesh_ui_simple", &m_mesh_ui_style );
}

void Cexport_MeshPlugIn::SaveProfile( LPCTSTR lpszSection, CRhinoProfileContext& pc )
{
  pc.SaveProfileMeshParameters( lpszSection, L"mesh_parameters", m_mesh_parameters );
  pc.SaveProfileInt( lpszSection, L"mesh_ui_simple", m_mesh_ui_style );
}

/////////////////////////////////////////////////////////////////////////////
// File export overrides

void Cexport_MeshPlugIn::AddFileType( ON_ClassArray<CRhinoFileType>& extensions, const CRhinoFileWriteOptions& options )
{
  extensions.Append( CRhinoFileType(PlugInID(), L"Sample Mesh (*.mesh)", L"mesh") );
}

BOOL Cexport_MeshPlugIn::WriteFile( const wchar_t* filename, int index, CRhinoDoc& doc, const CRhinoFileWriteOptions& options )
{
  // Are we saving or exporting?
  bool bExport = options.Mode( CRhinoFileWriteOptions::SelectedMode );
  // Are we in interactive or scripted mode?
  bool bScript = options.Mode( CRhinoFileWriteOptions::BatchMode );

  ON_SimpleArray<const CRhinoObject*> objects( 256 );

  // Get objects to save/export
  CRhinoObjectIterator it( doc, CRhinoObjectIterator::undeleted_objects );
  if( bExport )
  {
    it.EnableSelectedFilter();
    it.EnableVisibleFilter();
  }

  // Do the iteration...
  const CRhinoObject* obj = 0;
  for( obj = it.First(); obj; obj = it.Next() )
    objects.Append( obj );

  ON_ClassArray<CRhinoObjectMesh> meshes( objects.Count() );
  ON_MeshParameters mesh_parameters = m_mesh_parameters;
  int mesh_ui_style = ( bScript ) ? 2 : m_mesh_ui_style;

  // Get the meshes to save/export
  CRhinoCommand::result res = RhinoMeshObjects( objects, mesh_parameters, mesh_ui_style, meshes );
  if( res == CRhinoCommand::success )
  {
    if( mesh_ui_style >= 0 && mesh_ui_style <= 1 )
      m_mesh_ui_style = mesh_ui_style;
    m_mesh_parameters = mesh_parameters;
  }
  else 
  {
    if( bExport )
      RhinoApp().Print( L"\nNo meshes to export.\n" );
    else
      RhinoApp().Print( L"\nNo meshes to save.\n" );
    return FALSE;
  }

  // Write the mesh file
  FILE* fp = 0;
  errno_t err = _wfopen_s( &fp, filename, L"w" );
  bool rc = ( 0 == err || 0 != fp );
  if( !rc )
  {
    RhinoApp().Print( L"\nUnable to open \"%s\" for writing.\n", filename );
    return FALSE;
  }

  // Write mesh count
  ON_wString s;
  s.Format( L"meshcount=%d\n", meshes.Count() );
  rc = ( fputws(s, fp) >= 0 );

  int i, j;
  for( i = 0; rc && i < meshes.Count(); i++ )
  {
    const CRhinoObjectMesh& obj_mesh = meshes[i];
    const ON_Mesh* mesh = obj_mesh.m_mesh;
    rc = ( 0 != mesh );

    // Write mesh number
    if( rc )
    {
      s.Format( L"mesh=%d\n", i );
      rc = ( fputws(s, fp) >= 0 );
    }

    // Write mesh vertex count
    if( rc )
    {
      s.Format( L"vertexcount=%d\n", mesh->m_V.Count() );
      rc = ( fputws(s, fp) >= 0 );
    }

    // Write mesh face count
    if( rc )
    {
      s.Format( L"facecount=%d\n", mesh->m_F.Count() );
      rc = ( fputws(s, fp) >= 0 );
    }

    // Write mesh vertices
    if( rc )
    {
      for( j = 0; rc && j < mesh->m_V.Count(); j++ )
      {
        const ON_3fPoint& p = mesh->m_V[j];
        s.Format( L"vertex=(%.16f,%.16f,%.16f)\n", p.x, p.y, p.z );
        rc = ( fputws(s, fp) >= 0 );
      }
    }

    // Write mesh faces
    if( rc )
    {
      for( j = 0; rc && j < mesh->m_F.Count(); j++ )
      {
        const ON_MeshFace& f = mesh->m_F[j];
        s.Format( L"face=(%d,%d,%d,%d)\n", f.vi[0], f.vi[1], f.vi[2], f.vi[3] );
        rc = ( fputws(s, fp) >= 0 );
      }
    }
  }

  fclose( fp );
  
  return ( rc ) ? TRUE : FALSE;
}

