////////////////////////////////////////////////////////////////////////////////////
// TestOptionsListCtrlDockBar.h

#pragma once

#include "Resource.h"
#include "TestOptionsListCtrlDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CTestOptionsListCtrlDockBar

class CTestOptionsListCtrlDockBar : public CRhinoUiDockBar
{
	DECLARE_SERIAL( CTestOptionsListCtrlDockBar )

public:
	CTestOptionsListCtrlDockBar();
	~CTestOptionsListCtrlDockBar();

  static ON_UUID Id(); 
	UUID DockBarID() const;
	const wchar_t* DockBarName( int language_id = 1033 ) const;

  void OnShowDockBar( bool bShowDockBar );

protected:
	bool CreateDockBarControls();
	DECLARE_MESSAGE_MAP();
};
