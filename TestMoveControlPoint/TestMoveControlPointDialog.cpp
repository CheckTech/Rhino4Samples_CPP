#include "stdafx.h"
#include "TestMoveControlPointDialog.h"
#include "RhinoObjectList.h"


/////////////////////////////////////////////////////////////////////////////
// CTestMoveControlPointConduit

CTestMoveControlPointConduit::CTestMoveControlPointConduit()
: CRhinoDisplayConduit(CSupportChannels::SC_DRAWOVERLAY)
{
  m_xform.Identity();
}

bool CTestMoveControlPointConduit::ExecConduit( CRhinoDisplayPipeline& dp, UINT nChannel, bool& bTerminate )
{
  switch( nChannel )
  {
  case CSupportChannels::SC_DRAWOVERLAY:
    {
      dp.PushObjectColor( 0 );
      dp.DrawObjects( m_list.m_objects, &m_xform );
      dp.DrawObjects( m_list.m_grip_owners );
      dp.DrawObjects( m_list.m_grip_captives );
      dp.PopObjectColor();
    }
    break;
  }

  return true;
}

void CTestMoveControlPointConduit::AppendObjects( const CRhinoObjectList& list )
{
  m_list = list;
}

void CTestMoveControlPointConduit::SetXform( const ON_Xform& xform  )
{
  m_xform = xform;

  for( int i = 0; i < m_list.m_grips.Count(); i++ )
    m_list.m_grips[i]->MoveGrip( xform );
}


/////////////////////////////////////////////////////////////////////////////
// CTestMoveControlPointDialog

IMPLEMENT_DYNAMIC(CTestMoveControlPointDialog, CRhinoDialog)

CTestMoveControlPointDialog::CTestMoveControlPointDialog(CRhinoDoc& doc, CWnd* pParent /*=NULL*/)
: CRhinoDialog(CTestMoveControlPointDialog::IDD, pParent)
, m_doc(doc)
{
  SetEnableDisplayCommands( TRUE );
  m_point = ON_UNSET_POINT;
  m_distance = 0;
}

CTestMoveControlPointDialog::~CTestMoveControlPointDialog()
{
}

void CTestMoveControlPointDialog::DoDataExchange(CDataExchange* pDX)
{
	CRhinoDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISTANCE_EDIT, m_distance_edit);
	DDX_Control(pDX, IDC_DISTANCE_SPIN, m_distance_spin);
  m_distance_edit.DDX_Text(pDX, IDC_DISTANCE_EDIT, m_distance);
}

BEGIN_MESSAGE_MAP(CTestMoveControlPointDialog, CRhinoDialog)
  ON_EN_CHANGE(IDC_DISTANCE_EDIT, &CTestMoveControlPointDialog::OnChangeDistanceEdit)
END_MESSAGE_MAP()

BOOL CTestMoveControlPointDialog::OnInitDialog() 
{
  SetAllowEscapeAndEnter( true );

  CRhinoDialog::OnInitDialog();

  m_distance_spin.SetRange( -100, 100 );
  m_conduit.Enable();

  return TRUE;
}

void CTestMoveControlPointDialog::OnChangeDistanceEdit()
{
  UpdateData( TRUE );

  ON_Xform xform(1);

  if( m_distance != 0 )
  {
    ON_3dPoint point = m_point;
    point.z += m_distance;

    xform.Translation( point - m_point );
  }

  m_conduit.SetXform( xform );
  m_doc.Redraw();
}

void CTestMoveControlPointDialog::AppendObjects( const CRhinoObjectList& list )
{
  m_conduit.AppendObjects( list );
}

void CTestMoveControlPointDialog::SetPoint( const ON_3dPoint& point )
{
  m_point = point;
}

void CTestMoveControlPointDialog::OnOK()
{
  m_conduit.Disable();
  CRhinoDialog::OnOK();
}

void CTestMoveControlPointDialog::OnCancel()
{
  m_conduit.Disable();
  CRhinoDialog::OnCancel();
}
