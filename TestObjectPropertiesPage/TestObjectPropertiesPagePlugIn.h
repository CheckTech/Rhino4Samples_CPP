/////////////////////////////////////////////////////////////////////////////
// TestObjectPropertiesPagePlugIn.h

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestObjectPropertiesPagePlugIn

class CTestObjectPropertiesPagePlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestObjectPropertiesPagePlugIn();
  ~CTestObjectPropertiesPagePlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // Optional overrides
  CRhinoPlugIn::plugin_load_time PlugInLoadTime();
  void AddPagesToObjectPropertiesDialog( ON_SimpleArray<class CRhinoObjectPropertiesDialogPage*>& pages );

private:
  ON_wString m_plugin_version;
};

CTestObjectPropertiesPagePlugIn& TestObjectPropertiesPagePlugIn();



