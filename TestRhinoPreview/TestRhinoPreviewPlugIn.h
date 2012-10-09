/////////////////////////////////////////////////////////////////////////////
// TestRhinoPreviewPlugIn.h

#pragma once

class CTestRhinoPreviewPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestRhinoPreviewPlugIn();
  ~CTestRhinoPreviewPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

private:
  ON_wString m_plugin_version;
};

CTestRhinoPreviewPlugIn& TestRhinoPreviewPlugIn();



