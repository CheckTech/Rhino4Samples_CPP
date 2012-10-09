/////////////////////////////////////////////////////////////////////////////
// TestMoveControlPointPlugIn.h : main header file for the TestMoveControlPoint plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestMoveControlPointPlugIn
// See TestMoveControlPointPlugIn.cpp for the implementation of this class
//

class CTestMoveControlPointPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestMoveControlPointPlugIn();
  ~CTestMoveControlPointPlugIn();

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

CTestMoveControlPointPlugIn& TestMoveControlPointPlugIn();



