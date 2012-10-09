/////////////////////////////////////////////////////////////////////////////
// TestBlockViewDialog.cpp

#include "StdAfx.h"
#include "TestBlockViewDialog.h"

IMPLEMENT_DYNAMIC(CTestBlockViewDialog, CRhinoDialog)

CTestBlockViewDialog::CTestBlockViewDialog(CWnd* pParent, CRhinoDoc& doc )
: CRhinoDialog(CTestBlockViewDialog::IDD, pParent),
  m_doc(doc),
  m_idef(0)
{
}

CTestBlockViewDialog::~CTestBlockViewDialog()
{
}

void CTestBlockViewDialog::DoDataExchange(CDataExchange* pDX)
{
  CRhinoDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LISTBOX, m_listbox);
  DDX_Control(pDX, IDC_PREVIEW, m_preview);
}

BEGIN_MESSAGE_MAP(CTestBlockViewDialog, CRhinoDialog)
  ON_WM_PAINT()
  ON_LBN_SELCHANGE(IDC_LISTBOX, OnSelChangeListBox)
END_MESSAGE_MAP()

BOOL CTestBlockViewDialog::OnInitDialog()
{
  CRhinoDialog::OnInitDialog();

  const CRhinoInstanceDefinitionTable& idef_table = m_doc.m_instance_definition_table;
  int i;
  for( i = 0; i < idef_table.InstanceDefinitionCount(); i++ )
  {
    const CRhinoInstanceDefinition* idef = idef_table[i];
    if( idef && !idef->IsDeleted() )
      m_listbox.AddString( idef->Name() );
  }

  m_listbox.SetCurSel(0);
  OnSelChangeListBox();

  return TRUE;
}

CRect CTestBlockViewDialog::GetPaintRect()
{
  CRect rect;
  m_preview.GetWindowRect( rect );
  ScreenToClient( rect );
  rect.DeflateRect( 4, 20, 4, 4 );
  return rect;
}

void CTestBlockViewDialog::CreateTopViewport( CRhinoViewport& vp )
{
  CRect rect = GetPaintRect();

  double def_size = 15.0;
  ON_BoundingBox bbox;
  bbox.m_min.Set( -def_size, -def_size, -def_size );
  bbox.m_max.Set(  def_size, def_size, def_size );
  ON_3dVector dir;
  dir.Set(0.0,0.0,-100.0);

  ON_3dmView view_info;
  view_info.m_name = L"Top";
  view_info.m_target = ON_origin;
  view_info.m_vp.SetCameraLocation( view_info.m_target - dir );
  view_info.m_vp.SetCameraDirection( dir );
  view_info.m_vp.SetCameraUp( ON_yaxis );
  view_info.m_vp.SetProjection( ON::parallel_view );
  view_info.m_vp.SetScreenPort( 0, 100, 100, 0, 0, 1 );
  view_info.m_cplane.m_plane = ON_xy_plane;
  view_info.m_vp.Extents( atan(12.0/50.0), bbox );
  view_info.m_position.m_wnd_left = 0.0;
  view_info.m_position.m_wnd_right = 0.5;
  view_info.m_position.m_wnd_top = 0.0;
  view_info.m_position.m_wnd_bottom = 0.5;

  vp.SetView( view_info );  
  vp.SetScreenSize( rect.Width(), rect.Height() );
  vp.SetDisplayMode( ON::wireframe_display );
  vp.EnableGhostedShade( false );
  vp.EnableFlatShade( false );
  vp.EnableXrayShade( false );
}

void CTestBlockViewDialog::ZoomExtentsViewport( CRhinoViewport& vp )
{
  if( m_idef )
  {
    const ON_Viewport& current_vp = vp.VP();
    ON_Viewport zoomed_vp;
    
    double border = 1.1;

    ON_Xform w2c, c2w(1.0);
    current_vp.GetXform( ON::world_cs, ON::camera_cs, w2c );

    ON_BoundingBox camcoord_bbox;
    bool bGrowBox = false;

    int i;
    for( i = 0; i < m_idef->ObjectCount(); i++ )
    {
      const CRhinoObject* obj = m_idef->Object(i);
      if( obj )
      {
        obj->GetTightBoundingBox( camcoord_bbox, bGrowBox, &w2c );
        if( !bGrowBox )
          bGrowBox = camcoord_bbox.IsValid();
      }
    }

    if( bGrowBox )
    {
      ON_3dPoint world_target = c2w * camcoord_bbox.Center();
      if( ON_IsValid(border) && border > 1.0 )
      {
        double dx = camcoord_bbox.m_max.x - camcoord_bbox.m_min.x;
        dx *= 0.5 * (border - 1.0);
        camcoord_bbox.m_max.x += dx;
        camcoord_bbox.m_min.x -= dx;

        double dy = camcoord_bbox.m_max.y - camcoord_bbox.m_min.y;
        dy *= 0.5 * (border - 1.0);
        camcoord_bbox.m_max.y += dy;
        camcoord_bbox.m_min.y -= dy;
      }

      if( RhinoDollyExtents(current_vp, camcoord_bbox, zoomed_vp) )
        vp.SetVP( zoomed_vp, true );
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// CTestBlockViewConduit

class CTestBlockViewConduit : public CRhinoDisplayConduit
{
public:
  CTestBlockViewConduit( const CRhinoInstanceDefinition* idef );
  bool ExecConduit( CRhinoDisplayPipeline&, UINT, bool& );   
private:
  const CRhinoInstanceDefinition* m_idef;
};

CTestBlockViewConduit::CTestBlockViewConduit( const CRhinoInstanceDefinition* idef )
: CRhinoDisplayConduit( CSupportChannels::SC_DRAWOBJECT | CSupportChannels::SC_PREDRAWOBJECTS, false),
  m_idef(idef)
{
}

bool CTestBlockViewConduit::ExecConduit( CRhinoDisplayPipeline& dp, UINT nActiveChannel, bool& bTerminateChannel )
{
  if( nActiveChannel == CSupportChannels::SC_PREDRAWOBJECTS )
  {
    if( m_idef )
      dp.DrawObject( m_idef ); // draw the instance definition
    return true;
  }

  if( nActiveChannel == CSupportChannels::SC_DRAWOBJECT )
  {
    if( m_idef )
    {
      const CRhinoObject* obj = m_pChannelAttrs->m_pObject;
      if( obj )
      {
        if( !obj->IsInstanceDefinitionGeometry() )
          m_pChannelAttrs->m_bDrawObject = false;
        if( dp.ObjectHasTransform(m_pChannelAttrs->m_nObjectIndex) )
          m_pChannelAttrs->m_bDrawObject = false;
      }
    }
    return true;
  }

  return true;
}

/////////////////////////////////////////////////////////////////////////////

void CTestBlockViewDialog::OnPaint()
{
  CPaintDC dc( this );

  if( m_idef )
  {
    CRect rect = GetPaintRect();
    CRhinoDib dib;
    if( dib.CreateDib(rect.Width(), rect.Height(), 24, true) )
    {
      CRhinoViewport vp;
      CreateTopViewport( vp );
      ZoomExtentsViewport( vp );

      CRhinoDisplayPipeline_OGL dp( &dc, vp );
      CDisplayPipelineAttributes da;
      
      //da = *CRhinoDisplayAttrsMgr::StdRenderedAttrs(); 
      da = *CRhinoDisplayAttrsMgr::StdWireframeAttrs();
      da.m_bUseDocumentGrid = false;
      da.m_bDrawGrid = false;
      da.m_bDrawAxes = da.m_bDrawGrid;
      da.m_bDrawWorldAxes = false;
      da.m_bIgnoreHighlights = false;

      CTestBlockViewConduit conduit( m_idef );
      conduit.Enable();
      bool rc = dp.DrawToDib( dib, rect.Width(), rect.Height(), &da );
      conduit.Disable();

      if( rc )
        dib.Draw( &dc, rect );
    }
  }
}

void CTestBlockViewDialog::OnSelChangeListBox()
{
  m_idef = 0;

  int index = m_listbox.GetCurSel();
  if( index != LB_ERR )
  {
    CString str;
    m_listbox.GetText( index, str );
    const CRhinoInstanceDefinitionTable& idef_table = m_doc.m_instance_definition_table;
    int i;
    for( i = 0; i < idef_table.InstanceDefinitionCount(); i++ )
    {
      const CRhinoInstanceDefinition* idef = idef_table[i];
      if( idef && str.CompareNoCase(idef->Name()) == 0 )
      {
        m_idef = idef;
        break;
      }
    }
  }

  InvalidateRect( GetPaintRect(), 0 );
}
