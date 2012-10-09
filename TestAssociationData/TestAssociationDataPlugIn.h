/////////////////////////////////////////////////////////////////////////////
// TestAssociationDataPlugIn.h

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestAssociationDataPlugIn

class CTestAssociationDataPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestAssociationDataPlugIn();
  ~CTestAssociationDataPlugIn();

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

CTestAssociationDataPlugIn& TestAssociationDataPlugIn();



