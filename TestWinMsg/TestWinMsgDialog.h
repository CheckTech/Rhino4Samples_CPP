/////////////////////////////////////////////////////////////////////////////
// TestWinMsgDialog.h

#pragma once

#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTestWinMsgDialog dialog

class CTestWinMsgDialog : public CRhinoDialog
{
	DECLARE_DYNAMIC( CTestWinMsgDialog )

public:
	CTestWinMsgDialog( bool m_bAutoDelete = true );

	BOOL Create( LPCTSTR lpszTemplateName, CWnd* pParentWnd = 0 );
	BOOL Create( UINT nIDTemplate, CWnd* pParentWnd = 0 );

	virtual ~CTestWinMsgDialog();

// Dialog Data
	enum { IDD = IDD_TESTWINMSG_DIALOG };

public:
  // Registered window message ids
  static UINT TestWinMsgOk();
  static UINT TestWinMsgCancel();

public:
  virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	DECLARE_MESSAGE_MAP()

private:
  bool m_bAutoDelete;
};
