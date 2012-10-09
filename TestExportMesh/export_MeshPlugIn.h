/////////////////////////////////////////////////////////////////////////////
// export_MeshPlugIn.h

#pragma once

class Cexport_MeshPlugIn : public CRhinoFileExportPlugIn
{
public:
  Cexport_MeshPlugIn();
  ~Cexport_MeshPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // Optional overrides
  void LoadProfile( LPCTSTR lpszSection, CRhinoProfileContext& pc );
  void SaveProfile( LPCTSTR lpszSection, CRhinoProfileContext& pc );

  // File export overrides
  void AddFileType( ON_ClassArray<CRhinoFileType>& extensions, const CRhinoFileWriteOptions& options );
  BOOL WriteFile( const wchar_t* filename, int index, CRhinoDoc& doc, const CRhinoFileWriteOptions& options );

private:
  ON_wString m_plugin_version;
  ON_MeshParameters m_mesh_parameters;
  int m_mesh_ui_style;
};



