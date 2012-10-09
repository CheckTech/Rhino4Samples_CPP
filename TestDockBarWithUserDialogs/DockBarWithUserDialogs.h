/////////////////////////////////////////////////////////////////////////////
// DockBarWithUserDialogs.h

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDockBarWithUserDialogs

class CDockBarWithUserDialogs : public CRhinoUiDockBar
{
	DECLARE_SERIAL( CDockBarWithUserDialogs )

public:
	CDockBarWithUserDialogs();
	virtual ~CDockBarWithUserDialogs();
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );

public:
  // Required CRhinoUiDockBar overrides
  UUID DockBarID() const;
  const wchar_t* DockBarName( int language_id = 1033 /*English*/) const;
  bool CreateDockBarControls();

  void ShowDialog(int iDialog);

private:
  CDialog* ComputeClientDialog();

private:
  CDialog* m_CurrentDialog;
  int m_iCurrentDialog;

protected:
	DECLARE_MESSAGE_MAP()
};


