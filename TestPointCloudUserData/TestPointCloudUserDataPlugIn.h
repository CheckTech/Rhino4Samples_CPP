/////////////////////////////////////////////////////////////////////////////
// TestPointCloudUserDataPlugIn.h

#pragma once

class CTestPointCloudUserDataPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestPointCloudUserDataPlugIn();
  ~CTestPointCloudUserDataPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

private:
  ON_wString m_plugin_version;
};

CTestPointCloudUserDataPlugIn& ThePlugIn();



