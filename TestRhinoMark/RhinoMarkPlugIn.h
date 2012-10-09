/////////////////////////////////////////////////////////////////////////////
// RhinoMarkPlugIn.h

#pragma once

#include "RhinoMarkObject.h"

class CRhinoMarkPlugIn : public CRhinoUtilityPlugIn
{
public:
  CRhinoMarkPlugIn();
  ~CRhinoMarkPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // Additional overrides
  LPUNKNOWN GetPlugInObjectInterface( const ON_UUID& iid );

private:
  ON_wString m_plugin_version;
  CRhinoMarkObject m_object;
};

// Returns the one and only CRhinoMarkPlugIn object
CRhinoMarkPlugIn& RhinoMarkPlugIn();

// Function used by the RhinoMark command
bool RhinoRegenBenchMark( 
    CRhinoView* view, 
    DWORD& delta_time, 
    int frame_count = 100, 
    bool bFreeze = true 
    );

