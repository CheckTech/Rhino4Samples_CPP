/////////////////////////////////////////////////////////////////////////////
// TestAnimatorDlg.cpp

#include "StdAfx.h"
#include "TestAnimatorDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CTestAnimatorConduit implementation

CTestAnimatorConduit::CTestAnimatorConduit() 
: CRhinoDisplayConduit( CSupportChannels::SC_PREDRAWOBJECTS | CSupportChannels::SC_CALCBOUNDINGBOX )
{
  m_xform.Identity();
}

bool CTestAnimatorConduit::ExecConduit( CRhinoDisplayPipeline& dp, UINT nChannel, bool& bTerminate )
{
  switch( nChannel )
  {
  case CSupportChannels::SC_CALCBOUNDINGBOX:
    {
      // If you are dynamically drawing objects, then we must implement the 
      // this channel to add to the overall scene bounding box. This will make
      // Rhino adjust its clipping planes to include our geometry.
      int i;
      for( i = 0; i < m_objects.Count(); i++)
      {
        const CRhinoObject* obj = m_objects[i];
        if( obj )
        {
          ON_BoundingBox bbox = obj->BoundingBox();
          bbox.Transform( m_xform );
          m_pChannelAttrs->m_BoundingBox.Union( bbox );
        }
      }
    }
    break;
    
  case CSupportChannels::SC_PREDRAWOBJECTS:
    {
      // Tis channel is where the drawing takes place.
      int i;
      for( i = 0; i < m_objects.Count(); i++)
      {
        const CRhinoObject* obj = m_objects[i];
        if( obj )
        {
          dp.SetObjectColor( obj->ObjectDrawColor(true) );
          dp.DrawObject( obj, &m_xform );
        }
      }
    }
    break;
  }
  
  return true;
}

/////////////////////////////////////////////////////////////////////////////
// CTestAnimatorDlg implementation

CTestAnimatorDlg::CTestAnimatorDlg( CWnd* pParent )
: CRhinoDialog( CTestAnimatorDlg::IDD, pParent )
{
  SetEnableDisplayCommands( true );
  m_max_steps = 100;
}

void CTestAnimatorDlg::DoDataExchange( CDataExchange* pDX )
{
	CRhinoDialog::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_SLIDER, m_slider );
}

BEGIN_MESSAGE_MAP( CTestAnimatorDlg, CRhinoDialog )
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

BOOL CTestAnimatorDlg::OnInitDialog() 
{
  EnableSaveDialogPositionAndSize();

	CRhinoDialog::OnInitDialog();

  // Setup slider control
  m_slider.SetRange( 0, m_max_steps - 1 );
  m_slider.SetTicFreq( 10 );
	m_slider.SetLineSize( 1 );
	m_slider.SetPageSize( 10 );

  // Enable drawing conduit
  m_conduit.Enable();

  // Draw first position
  ON_3dVector v = m_points[0] - m_start;
  m_conduit.m_xform.Translation( v );
  RedrawDocument();

	return TRUE;
}

void CTestAnimatorDlg::RedrawDocument()
{
  CRhinoDoc* doc = RhinoApp().ActiveDoc();
  if( doc )
    doc->Redraw( CRhinoView::regenerate_display_hint );
}

void CTestAnimatorDlg::OnOK() 
{
  m_conduit.Disable();
  CRhinoDialog::OnOK();
}

void CTestAnimatorDlg::OnCancel() 
{
  m_conduit.Disable();
  CRhinoDialog::OnCancel();
}

void CTestAnimatorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  switch( nSBCode )
  {
    case TB_LINEUP:
      break;
    case TB_LINEDOWN:
      break;
    case TB_PAGEUP:
      break;
    case TB_PAGEDOWN:
      break;
    case TB_THUMBPOSITION:
      return;
    case TB_THUMBTRACK:
      break;
    case TB_TOP:
      break;
    case TB_BOTTOM:
      break;
    case TB_ENDTRACK:
      return;
  }

  // Update positions
  int pos = m_slider.GetPos();
  if( pos >= m_slider.GetRangeMin() || pos <= m_slider.GetRangeMax() )
  {
    ON_3dVector v = m_points[pos] - m_start;
    m_conduit.m_xform.Translation( v );
    RedrawDocument();
  }
}
