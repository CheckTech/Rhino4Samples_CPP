/////////////////////////////////////////////////////////////////////////////
// TestScriptPlugIn.h
//

#pragma once

#include "TestScriptObject.h"

class CTestScriptPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestScriptPlugIn();
  ~CTestScriptPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // Optional overrides
  LPUNKNOWN GetPlugInObjectInterface( const ON_UUID& iid );

private:
  ON_wString m_plugin_version;
  CTestScriptObject m_object;
};

CTestScriptPlugIn& TestScriptPlugIn();



