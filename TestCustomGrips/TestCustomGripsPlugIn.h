/////////////////////////////////////////////////////////////////////////////
// TestCustomGripsPlugIn.h : main header file for the TestCustomGrips plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestCustomGripsPlugIn
// See TestCustomGripsPlugIn.cpp for the implementation of this class
//

class CTestCustomGripsPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestCustomGripsPlugIn();
  ~CTestCustomGripsPlugIn();

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

CTestCustomGripsPlugIn& TestCustomGripsPlugIn();



