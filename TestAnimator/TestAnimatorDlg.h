/////////////////////////////////////////////////////////////////////////////
// TestAnimatorDlg.h

#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTestAnimatorConduit declaration

class CTestAnimatorConduit : public CRhinoDisplayConduit
{
public:
  CTestAnimatorConduit();
  bool ExecConduit( CRhinoDisplayPipeline& dp, UINT nChannel, bool& bTerminate );

public:
  ON_SimpleArray<const CRhinoObject*> m_objects;
  ON_Xform m_xform;
};

/////////////////////////////////////////////////////////////////////////////
// CTestAnimatorDlg declaration

class CTestAnimatorDlg : public CRhinoDialog
{
public:
	CTestAnimatorDlg( CWnd* pParent );

	enum { IDD = IDD_TEST_ANIMATOR_DLG };
	CSliderCtrl	m_slider;

public:
  void RedrawDocument();

  int m_max_steps;
  ON_3dPoint m_start;
  ON_3dPointArray m_points;
  CTestAnimatorConduit m_conduit;

protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	DECLARE_MESSAGE_MAP()
};
