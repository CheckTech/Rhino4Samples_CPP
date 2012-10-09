/////////////////////////////////////////////////////////////////////////////
// TestAttributeUserDataPlugIn.h

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestAttributeUserDataPlugIn

class CTestAttributeUserDataPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestAttributeUserDataPlugIn();
  ~CTestAttributeUserDataPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

private:
  ON_wString m_plugin_version;
};

CTestAttributeUserDataPlugIn& TestAttributeUserDataPlugIn();



