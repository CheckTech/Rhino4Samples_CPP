/////////////////////////////////////////////////////////////////////////////
// GripMoverApp.h : main header file for the GripMover DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGripMoverApp
// See GripMoverApp.cpp for the implementation of this class
//

class CGripMoverApp : public CWinApp
{
public:
	CGripMoverApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
