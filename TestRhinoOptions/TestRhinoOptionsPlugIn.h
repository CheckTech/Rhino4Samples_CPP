#pragma once

class CTestRhinoOptionsPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestRhinoOptionsPlugIn();
  ~CTestRhinoOptionsPlugIn();

  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  BOOL AddToPlugInHelpMenu() const;
  BOOL OnDisplayPlugInHelp( HWND hWnd ) const;

  CRhinoPlugIn::plugin_load_time PlugInLoadTime();
  void AddPagesToOptionsDialog( HWND hWnd, ON_SimpleArray<CRhinoOptionsDialogPage*>& pages );
  void AddPagesToDocumentPropertiesDialog( CRhinoDoc& doc, HWND hWnd, ON_SimpleArray<CRhinoOptionsDialogPage*>& pages );

private:
  ON_wString m_plugin_version;
};

CTestRhinoOptionsPlugIn& TestRhinoOptionsPlugIn();



