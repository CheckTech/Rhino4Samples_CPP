/////////////////////////////////////////////////////////////////////////////
// import_OFFPlugIn.h : main header file for the import_OFF plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// Cimport_OFFPlugIn
// See import_OFFPlugIn.cpp for the implementation of this class
//

class Cimport_OFFPlugIn : public CRhinoFileImportPlugIn
{
public:
  Cimport_OFFPlugIn();
  ~Cimport_OFFPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // File import overrides
  void AddFileType( ON_ClassArray<CRhinoFileType>& extensions, const CRhinoFileReadOptions& options );
  BOOL ReadFile( const wchar_t* filename, int index, CRhinoDoc& dox, const CRhinoFileReadOptions& options );

private:
  BOOL ReadOffFile( const wchar_t* file_name, CRhinoDoc& doc );

private:
  ON_wString m_plugin_version;
};

Cimport_OFFPlugIn& import_OFFPlugIn();



