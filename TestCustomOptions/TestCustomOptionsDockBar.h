////////////////////////////////////////////////////////////////////////////////////
// TestCustomOptionsDockBar.h

#pragma once

#include "Resource.h"
#include "TestCustomOptionsDialog.h"

////////////////////////////////////////////////////////////////////////////////////
// CTestCustomOptionsDockBar

class CTestCustomOptionsDockBar : public CRhinoUiDockBar
{
	DECLARE_SERIAL( CTestCustomOptionsDockBar )

public:
	CTestCustomOptionsDockBar();
	~CTestCustomOptionsDockBar();

  static ON_UUID Id(); 
	UUID DockBarID() const;
	const wchar_t* DockBarName( int language_id = 1033 ) const;

  void OnShowDockBar( bool bShowDockBar );

protected:
	bool CreateDockBarControls();
	DECLARE_MESSAGE_MAP();
};
