#pragma once
#include "Resource.h"

// CMoveDialog dialog

class CMoveDialog : public CRhinoUiDialog
{
	DECLARE_DYNAMIC(CMoveDialog)

public:
	CMoveDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMoveDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMove();
};
