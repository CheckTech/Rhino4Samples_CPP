/////////////////////////////////////////////////////////////////////////////
// TestDockBarPlugIn.h

#pragma once

// CTestDockBarPlugIn

class CTestDockBarPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestDockBarPlugIn();
  ~CTestDockBarPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

private:
  ON_wString m_plugin_version;
};

CTestDockBarPlugIn& TestDockBarPlugIn();



