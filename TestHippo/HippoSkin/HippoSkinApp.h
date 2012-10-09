/////////////////////////////////////////////////////////////////////////////
// HippoSkinApp.h : main header file for the HippoSkin DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHippoSkinApp
// See HippoSkinApp.cpp for the implementation of this class
//

class CHippoSkinApp : public CWinApp
{
public:
	CHippoSkinApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CSplashWnd
// See HippoSkinApp.cpp for the implementation of this class
//

class CSplashWnd : public CWnd
{
	DECLARE_DYNAMIC( CSplashWnd )

public:
	CSplashWnd();
	virtual ~CSplashWnd();

protected:
  CBitmap m_splash_bitmap;

protected:
	DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnPaint();
  afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
};



