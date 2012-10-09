/////////////////////////////////////////////////////////////////////////////
// FalseColorAnalysisExampleApp.h : main header file for the FalseColorAnalysisExample DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFalseColorAnalysisExampleApp
// See FalseColorAnalysisExampleApp.cpp for the implementation of this class
//

class CFalseColorAnalysisExampleApp : public CWinApp
{
public:
	CFalseColorAnalysisExampleApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
