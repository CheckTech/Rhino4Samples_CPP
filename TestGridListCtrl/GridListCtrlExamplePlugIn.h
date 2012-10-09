/////////////////////////////////////////////////////////////////////////////
// GridListCtrlExamplePlugIn.h : main header file for the GridListCtrlExample plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CGridListCtrlExamplePlugIn
// See GridListCtrlExamplePlugIn.cpp for the implementation of this class
//

class CGridListCtrlExamplePlugIn : public CRhinoUtilityPlugIn
{
public:
  CGridListCtrlExamplePlugIn();
  ~CGridListCtrlExamplePlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // Online help overrides
  BOOL AddToPlugInHelpMenu() const;
  BOOL OnDisplayPlugInHelp( HWND hWnd ) const;

private:
  ON_wString m_plugin_version;

  // TODO: Add additional class information here
};

CGridListCtrlExamplePlugIn& GridListCtrlExamplePlugIn();



