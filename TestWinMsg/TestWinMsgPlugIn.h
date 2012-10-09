/////////////////////////////////////////////////////////////////////////////
// TestWinMsgPlugIn.h

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestWinMsgPlugIn

class CTestWinMsgPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestWinMsgPlugIn();
  ~CTestWinMsgPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

private:
  ON_wString m_plugin_version;
};

// Return a reference to the one and only CTestWinMsgPlugIn object
CTestWinMsgPlugIn& TestWinMsgPlugIn();



