/////////////////////////////////////////////////////////////////////////////
// SculptedPrimsPlugIn.h : main header file for the SculptedPrims plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CSculptedPrimsPlugIn
// See SculptedPrimsPlugIn.cpp for the implementation of this class
//

class CSculptedPrimsPlugIn : public CRhinoUtilityPlugIn
{
public:
  CSculptedPrimsPlugIn();
  ~CSculptedPrimsPlugIn();

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

CSculptedPrimsPlugIn& SculptedPrimsPlugIn();



