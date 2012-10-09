/////////////////////////////////////////////////////////////////////////////
// RhinoMarkApp.h

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"

class CRhinoMarkApp : public CWinApp
{
public:
	CRhinoMarkApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
