/////////////////////////////////////////////////////////////////////////////
// TestPreviewPlugIn.h : main header file for the TestPreview plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewPlugIn
// See TestPreviewPlugIn.cpp for the implementation of this class
//

class CTestPreviewPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestPreviewPlugIn();
  ~CTestPreviewPlugIn();

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

CTestPreviewPlugIn& TestPreviewPlugIn();



