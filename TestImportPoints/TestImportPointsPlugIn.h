/////////////////////////////////////////////////////////////////////////////
// TestImportPointsPlugIn.h : main header file for the TestImportPoints plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestImportPointsPlugIn
// See TestImportPointsPlugIn.cpp for the implementation of this class
//

class CTestImportPointsPlugIn : public CRhinoFileImportPlugIn
{
public:
  CTestImportPointsPlugIn();
  ~CTestImportPointsPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // File import overrides
  void AddFileType( ON_ClassArray<CRhinoFileType>& extensions, const CRhinoFileReadOptions& options );
  BOOL ReadFile( const wchar_t* filename, int index, CRhinoDoc& doc, const CRhinoFileReadOptions& options );

private:
  BOOL ParsePointValue( const wchar_t* string, wchar_t delimiter, ON_3dPoint& pt );
  BOOL ParseRealValue( const wchar_t* string, double& value );

private:
  ON_wString m_plugin_version;
};



