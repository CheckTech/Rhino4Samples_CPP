/////////////////////////////////////////////////////////////////////////////
// TestRhinoCommandsPlugIn.h : main header file for the TestRhinoCommands plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestRhinoCommandsPlugIn
// See TestRhinoCommandsPlugIn.cpp for the implementation of this class
//

class CTestRhinoCommandsPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestRhinoCommandsPlugIn();
  ~CTestRhinoCommandsPlugIn();

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

CTestRhinoCommandsPlugIn& TestRhinoCommandsPlugIn();



