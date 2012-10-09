/////////////////////////////////////////////////////////////////////////////
// DockBarWithUserDialogsPlugIn.h

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDockBarWithUserDialogsPlugIn

class CDockBarWithUserDialogsPlugIn : public CRhinoUtilityPlugIn
{
public:
  CDockBarWithUserDialogsPlugIn();
  ~CDockBarWithUserDialogsPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // TODO: Override additional members here

public:
  class CDockBarWithUserDialogs* m_pDockBar;

private:
  ON_wString m_plugin_version;

  // TODO: Add additional class information here
};

CDockBarWithUserDialogsPlugIn& DockBarWithUserDialogsPlugIn();



