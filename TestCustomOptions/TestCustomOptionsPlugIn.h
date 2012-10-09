/////////////////////////////////////////////////////////////////////////////
// TestCustomOptionsPlugIn.h

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestCustomOptionsPlugIn

class CTestCustomOptionsPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestCustomOptionsPlugIn();
  ~CTestCustomOptionsPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

private:
  ON_wString m_plugin_version;

  // TODO: Add additional class information here
};

CTestCustomOptionsPlugIn& TestCustomOptionsPlugIn();



