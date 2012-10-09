/////////////////////////////////////////////////////////////////////////////
// export_MeshApp.h

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

class Cexport_MeshApp : public CWinApp
{
public:
	Cexport_MeshApp();

// Overrides
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};
