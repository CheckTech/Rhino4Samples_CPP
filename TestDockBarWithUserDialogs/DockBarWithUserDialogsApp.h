/////////////////////////////////////////////////////////////////////////////
// DockBarWithUserDialogsApp.h

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDockBarWithUserDialogsApp

class CDockBarWithUserDialogsApp : public CWinApp
{
public:
	CDockBarWithUserDialogsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
