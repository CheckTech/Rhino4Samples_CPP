/////////////////////////////////////////////////////////////////////////////
// ToolBarTestPlugInPlugIn.h : main header file for the ToolBarTestPlugIn plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CToolBarTestPlugInPlugIn
// See ToolBarTestPlugInPlugIn.cpp for the implementation of this class
//

class CToolBarTestPlugInPlugIn : public CRhinoUtilityPlugIn
{
public:
  CToolBarTestPlugInPlugIn();
  ~CToolBarTestPlugInPlugIn();

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

CToolBarTestPlugInPlugIn& ToolBarTestPlugInPlugIn();



