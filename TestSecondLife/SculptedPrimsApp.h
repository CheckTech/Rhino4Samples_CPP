/////////////////////////////////////////////////////////////////////////////
// SculptedPrimsApp.h : main header file for the SculptedPrims DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSculptedPrimsApp
// See SculptedPrimsApp.cpp for the implementation of this class
//

class CSculptedPrimsApp : public CWinApp
{
public:
	CSculptedPrimsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
