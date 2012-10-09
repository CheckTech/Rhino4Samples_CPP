/////////////////////////////////////////////////////////////////////////////
// MarkerPlugIn.h : main header file for the Marker plug-in
//

#pragma once

class CMarkerPlugIn : public CRhinoUtilityPlugIn
{
public:
  CMarkerPlugIn();
  ~CMarkerPlugIn();

  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  BOOL CallWriteDocument(const CRhinoFileWriteOptions& options);
  BOOL WriteDocument(CRhinoDoc& doc, ON_BinaryArchive& archive, const CRhinoFileWriteOptions& options);
  BOOL ReadDocument(CRhinoDoc& doc, ON_BinaryArchive& archive, const CRhinoFileReadOptions& options);

private:
  ON_wString m_plugin_version;
  ON_UuidList m_markers;
};

CMarkerPlugIn& MarkerPlugIn();



