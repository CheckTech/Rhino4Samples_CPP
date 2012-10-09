/////////////////////////////////////////////////////////////////////////////
// TestDocumentDataPlugIn.h
//

#if !defined(AFX_TESTDOCUMENTDATAPLUGIN_H__38B4BD40_43BF_4BCB_83F3_1AFF94F740C6__INCLUDED_)
#define AFX_TESTDOCUMENTDATAPLUGIN_H__38B4BD40_43BF_4BCB_83F3_1AFF94F740C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDocumentDataPlugIn
//

class CTestDocumentDataPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestDocumentDataPlugIn();
  ~CTestDocumentDataPlugIn();

  // General plug-in overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;

  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // Document user data overrides
  BOOL CallWriteDocument( const CRhinoFileWriteOptions& );
  BOOL WriteDocument( CRhinoDoc&, ON_BinaryArchive&, const CRhinoFileWriteOptions& );
  BOOL ReadDocument( CRhinoDoc&, ON_BinaryArchive&, const CRhinoFileReadOptions& );
  BOOL CanUnLoad() { return FALSE; }

  int FindStringTableItem( const wchar_t* name );

public:
  ON_wString m_plugin_version;
  ON_ClassArray<ON_wString> m_string_table;
};

CTestDocumentDataPlugIn& TestDocumentDataPlugIn();

#endif // !defined(AFX_TESTDOCUMENTDATAPLUGIN_H__38B4BD40_43BF_4BCB_83F3_1AFF94F740C6__INCLUDED_)


