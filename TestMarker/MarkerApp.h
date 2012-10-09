/////////////////////////////////////////////////////////////////////////////
// MarkerApp.h : main header file for the Marker DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"

class CMarkerApp : public CWinApp
{
public:
	CMarkerApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
