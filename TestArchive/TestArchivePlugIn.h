/////////////////////////////////////////////////////////////////////////////
// TestArchivePlugIn.h

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestArchivePlugIn

class CTestArchiveWatcher : public CRhinoEventWatcher
{
  // Called when Rhino closes the active document
  void OnCloseDocument( CRhinoDoc& doc );

  // Called when Rhino is creating a new document
  void OnNewDocument( CRhinoDoc& doc );

  // Called when Rhino has finished opening a document
  void OnEndOpenDocument( CRhinoDoc& doc, const wchar_t* filename, BOOL bMerge, BOOL bReference );

  // Called when Rhino has finished saving a document
  void OnEndSaveDocument( CRhinoDoc& doc, const wchar_t* filename, BOOL bExport );
};

/////////////////////////////////////////////////////////////////////////////
// CTestArchivePlugIn

class CTestArchivePlugIn : public CRhinoUtilityPlugIn
{
public:
  CTestArchivePlugIn();
  ~CTestArchivePlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

public:
  // Plug-in test data and archiving methods
  void InitTestData();
  void PrintTestData();
  void PurgeTestData();
  bool ReadTestArchive( const wchar_t* filename );
  bool WriteTestArchive( const wchar_t* filename );

private:
  ON_wString m_plugin_version;

  // Plug-in event watcher
  CTestArchiveWatcher m_watcher;

  // Plug-in test data
  CList<int, int> m_list;
};

CTestArchivePlugIn& TestArchivePlugIn();



