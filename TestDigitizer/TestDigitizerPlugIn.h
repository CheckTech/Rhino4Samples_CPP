/////////////////////////////////////////////////////////////////////////////
// TestDigitizerPlugIn.h : main header file for the TestDigitizer plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestDigitizerPlugIn
// See TestDigitizerPlugIn.cpp for the implementation of this class
//

class CTestDigitizerPlugIn : public CRhinoDigitizerPlugIn
{
public:
  CTestDigitizerPlugIn();
  ~CTestDigitizerPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // Digitizer overrides
  bool EnableDigitizer( bool bEnable );
  ON::unit_system UnitSystem() const;
  double PointTolerance() const;

private:
  ON_wString m_plugin_version;

  // TODO: Add additional class information here
	HANDLE m_hThread;
	DWORD m_dwThreadID;
	bool m_bDigitizerConnected;
};

CTestDigitizerPlugIn& TestDigitizerPlugIn();



