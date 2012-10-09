/////////////////////////////////////////////////////////////////////////////
// DialogB.h

#pragma once

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogB

class CDialogB : public CDialog
{
	DECLARE_DYNCREATE(CDialogB)

public:
	CDialogB(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogB();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };
  CStatic m_Static;

public:
  afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
};
