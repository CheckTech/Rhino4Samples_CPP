#pragma once

#include "resource.h"
#include "RhinoObjectList.h"


/////////////////////////////////////////////////////////////////////////////
// CTestMoveControlPointConduit

class CTestMoveControlPointConduit : public CRhinoDisplayConduit
{
public:
  CTestMoveControlPointConduit();
  ~CTestMoveControlPointConduit() {}
  bool ExecConduit( CRhinoDisplayPipeline& dp, UINT nChannel, bool& bTerminate );

public:
  void AppendObjects( const CRhinoObjectList& list );
  void SetXform( const ON_Xform& xform );

private:
  CRhinoObjectList m_list;
  ON_Xform m_xform;
};


/////////////////////////////////////////////////////////////////////////////
// CTestMoveControlPointDialog

class CTestMoveControlPointDialog : public CRhinoDialog
{
	DECLARE_DYNAMIC(CTestMoveControlPointDialog)

public:
	CTestMoveControlPointDialog(CRhinoDoc& doc, CWnd* pParent = NULL);
	virtual ~CTestMoveControlPointDialog();

  // Dialog Data
	enum { IDD = IDD_TESTMOVECONTROLPOINT_DIALOG };
	CRhinoUiEditInt	m_distance_edit;
	CSpinButtonCtrl	m_distance_spin;
	int m_distance;

public:
  void AppendObjects( const CRhinoObjectList& list );
  void SetPoint( const ON_3dPoint& point );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
  virtual void OnOK();
  virtual void OnCancel();
  afx_msg void OnChangeDistanceEdit();
	DECLARE_MESSAGE_MAP()

private:
  CRhinoDoc& m_doc;
  CTestMoveControlPointConduit m_conduit;
  ON_3dPoint m_point;
};
