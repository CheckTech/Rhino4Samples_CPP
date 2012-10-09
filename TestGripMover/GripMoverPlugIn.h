/////////////////////////////////////////////////////////////////////////////
// GripMoverPlugIn.h : main header file for the GripMover plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CGripMoverPlugIn
// See GripMoverPlugIn.cpp for the implementation of this class
//

class CGripMoverPlugIn : public CRhinoUtilityPlugIn
{
public:
  CGripMoverPlugIn();
  ~CGripMoverPlugIn();

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

CGripMoverPlugIn& GripMoverPlugIn();



