/////////////////////////////////////////////////////////////////////////////
// TestDocUserTextPlugIn.h : main header file for the TestDocUserText plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestDocUserTextPlugIn
// See TestDocUserTextPlugIn.cpp for the implementation of this class
//

class CTestDocUserTextPlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestDocUserTextPlugIn();
  ~CTestDocUserTextPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // Optional overrides
  BOOL CallWriteDocument( const CRhinoFileWriteOptions& options );
  BOOL WriteDocument( CRhinoDoc& doc, ON_BinaryArchive& archive, const CRhinoFileWriteOptions& options);
  BOOL ReadDocument( CRhinoDoc& doc, ON_BinaryArchive& archive, const CRhinoFileReadOptions& options);

  bool SetDocUserString( const wchar_t* key, const wchar_t* string_value );
  bool GetDocUserString( const wchar_t* key, ON_wString& string_value ) const;
  int GetDocUserStrings( ON_ClassArray<ON_UserString>& user_strings ) const;

private:
  ON_wString m_plugin_version;
  ON_UserStringList m_user_strings;
};

CTestDocUserTextPlugIn& TestDocUserTextPlugIn();



