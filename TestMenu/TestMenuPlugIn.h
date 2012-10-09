/////////////////////////////////////////////////////////////////////////////
// TestMenuPlugIn.h : main header file for the TestMenu plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestMenuPlugIn
// See TestMenuPlugIn.cpp for the implementation of this class
//

class CTestMenuPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestMenuPlugIn();
  ~CTestMenuPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // Online help overrides
  BOOL AddToPlugInHelpMenu() const;
  BOOL OnDisplayPlugInHelp( HWND hWnd ) const;

  // Additional overrides
  void OnInitPlugInMenuPopups( WPARAM wParam, LPARAM lParam );
  BOOL OnPlugInMenuCommand( WPARAM wParam );

private:
  ON_wString m_plugin_version;

  CMenu m_menu;
  bool m_script_mode;
};

CTestMenuPlugIn& TestMenuPlugIn();



