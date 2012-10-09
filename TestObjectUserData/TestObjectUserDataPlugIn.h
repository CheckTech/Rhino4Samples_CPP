/////////////////////////////////////////////////////////////////////////////
// TestObjectUserDataPlugIn.h : main header file for the TestObjectUserData plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestObjectUserDataPlugIn
// See TestObjectUserDataPlugIn.cpp for the implementation of this class
//

class CTestObjectUserDataPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestObjectUserDataPlugIn();
  ~CTestObjectUserDataPlugIn();

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

CTestObjectUserDataPlugIn& TestObjectUserDataPlugIn();



