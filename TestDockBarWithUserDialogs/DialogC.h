/////////////////////////////////////////////////////////////////////////////
// DialogC.h

#pragma once

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogC

class CDialogC : public CDialog
{
	DECLARE_DYNCREATE(CDialogC)

public:
	CDialogC(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogC();

// Dialog Data
	enum { IDD = IDD_DIALOG3 };
  CStatic m_Static;

public:
  afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
};
