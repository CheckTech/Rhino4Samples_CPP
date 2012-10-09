#pragma once

#include "resource.h"
#include "afxcmn.h"

class CDialog1ListCtrl : public CRhinoUiGridListCtrl
{
	DECLARE_DYNAMIC(CDialog1ListCtrl)

public:
  CDialog1ListCtrl( CRhinoDoc& doc);
  virtual ~CDialog1ListCtrl();

  // CRhinoUiGridListCtrl overrides
	BOOL DoneEditing( long nItem, int nSubItem, LPCTSTR lpszText);
	BOOL ModifyGridItem( long nItem, int nSubItem); 

protected:
  CRhinoDoc& m_doc;
  ON_wString m_wOriginalString;
protected:
  DECLARE_MESSAGE_MAP()
};

// CDialog1 dialog

class CDialog1 : public CRhinoDialog
{
	DECLARE_DYNAMIC(CDialog1)

public:
	CDialog1( CRhinoDoc& doc, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialog1();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
  CRhinoDoc& m_doc;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  CDialog1ListCtrl m_ListCtrl;
};
