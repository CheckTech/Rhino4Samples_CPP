/////////////////////////////////////////////////////////////////////////////
// TestOptionsListCtrlPlugIn.h : main header file for the TestOptionsListCtrl plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestOptionsListCtrlPlugIn
// See TestOptionsListCtrlPlugIn.cpp for the implementation of this class
//

class CTestOptionsListCtrlPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestOptionsListCtrlPlugIn();
  ~CTestOptionsListCtrlPlugIn();

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

CTestOptionsListCtrlPlugIn& TestOptionsListCtrlPlugIn();



