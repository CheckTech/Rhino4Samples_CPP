/////////////////////////////////////////////////////////////////////////////
// DialogA.h

#pragma once

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogA

class CDialogA : public CDialog
{
	DECLARE_DYNCREATE(CDialogA)

public:
	CDialogA(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogA();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };
  CStatic m_Static;

public:
  afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
};
