/////////////////////////////////////////////////////////////////////////////
// import_OFFApp.h : main header file for the import_OFF DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// Cimport_OFFApp
// See import_OFFApp.cpp for the implementation of this class
//

class Cimport_OFFApp : public CWinApp
{
public:
	Cimport_OFFApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
