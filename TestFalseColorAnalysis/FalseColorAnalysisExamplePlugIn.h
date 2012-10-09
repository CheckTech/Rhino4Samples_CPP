/////////////////////////////////////////////////////////////////////////////
// FalseColorAnalysisExamplePlugIn.h : main header file for the FalseColorAnalysisExample plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CFalseColorAnalysisExamplePlugIn
// See FalseColorAnalysisExamplePlugIn.cpp for the implementation of this class
//

class CFalseColorAnalysisExamplePlugIn : public CRhinoUtilityPlugIn
{
public:
  CFalseColorAnalysisExamplePlugIn();
  ~CFalseColorAnalysisExamplePlugIn();

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

CFalseColorAnalysisExamplePlugIn& FalseColorAnalysisExamplePlugIn();



