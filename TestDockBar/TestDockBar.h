////////////////////////////////////////////////////////////////////////////////////
// TestDockBar.h

#pragma once

#include "Resource.h"
#include "TestDockBarDialog.h"

// CTestDockBar

class CTestDockBar : public CRhinoUiDockBar
{
	DECLARE_SERIAL( CTestDockBar )

public:
	CTestDockBar();
	~CTestDockBar();

  static ON_UUID Id(); 
	UUID DockBarID() const;
	const wchar_t* DockBarName( int language_id = 1033 ) const;

  void OnDockBarPositionChanged( DWORD dwNewLocation );
  void OnShowDockBar( bool bShowDockBar );

protected:
	bool CreateDockBarControls();
	DECLARE_MESSAGE_MAP();
};
