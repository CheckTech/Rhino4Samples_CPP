/////////////////////////////////////////////////////////////////////////////
// RhinoMarkPlugIn.cpp

#include "StdAfx.h"
#include "RhinoMarkPlugIn.h"

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"Robert McNeel & Associates" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"3670 Woodland Park Avenue North\015\012Seattle WA 98103" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"United States" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"206-545-6877" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"206-545-7321" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"tech@mcneel.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.rhino3d.com" );
RHINO_PLUG_IN_UPDATE_URL( L"http://www.rhino3d.com/download" );

// The one and only CRhinoMarkPlugIn object
static CRhinoMarkPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CRhinoMarkPlugIn definition

CRhinoMarkPlugIn& RhinoMarkPlugIn()
{ 
  return thePlugIn; 
}

CRhinoMarkPlugIn::CRhinoMarkPlugIn()
{
  m_plugin_version = __DATE__"  "__TIME__;
}

CRhinoMarkPlugIn::~CRhinoMarkPlugIn()
{
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CRhinoMarkPlugIn::PlugInName() const
{
  return L"RhinoMark";
}

const wchar_t* CRhinoMarkPlugIn::PlugInVersion() const
{
  return m_plugin_version;
}

GUID CRhinoMarkPlugIn::PlugInID() const
{
  // {04C05895-38A5-4879-87BB-0EC25E714058}
  static const GUID RhinoMarkPlugIn_UUID =
  { 0x4C05895, 0x38A5, 0x4879, { 0x87, 0xBB, 0xE, 0xC2, 0x5E, 0x71, 0x40, 0x58 } };
  return RhinoMarkPlugIn_UUID;
}

BOOL CRhinoMarkPlugIn::OnLoadPlugIn()
{
  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CRhinoMarkPlugIn::OnUnloadPlugIn()
{
}

LPUNKNOWN CRhinoMarkPlugIn::GetPlugInObjectInterface( const ON_UUID& iid )
{
  LPUNKNOWN lpUnknown = 0;

  if( iid == IID_IUnknown )
    lpUnknown = m_object.GetInterface( &IID_IUnknown );

  else if( iid == IID_IDispatch )
    lpUnknown = m_object.GetInterface( &IID_IDispatch );

   if( lpUnknown )
    m_object.ExternalAddRef();

  return lpUnknown;
}

/////////////////////////////////////////////////////////////////////////////

bool RhinoRegenBenchMark( CRhinoView* view, DWORD& delta_time, int frame_count /*= 100*/, bool bFreeze /*= true*/ )
{
  delta_time = 0;

  if( 0 == view )
  {
    view = RhinoApp().ActiveView();
    if( 0 == view )
      return false;
  }

  double delta_angle = 5.0 * ON_PI/180.0;
  DWORD time0 = 0, time1 = 0;

  CClientDC dc( view );
  CRhinoViewport& vp = view->MainViewport();
  CRhinoDisplayPipeline* dp = vp.DisplayPipeline();
  CDisplayPipelineAttributes* da = view->DisplayAttributes();
  CDC* pDC = dp ? dp->GetDrawDC() : &dc;
    
  // this prevents capturing of the frame buffer on every update...
  CRhinoDisplayPipeline::EnableFrameBufferCapture( false );
    
  // We also don't need to update the draw lists every frame, so make 
  // sure the pipeline uses a "frozen" snapshot of the current object
  // list...
  if( bFreeze && dp )
    dp->FreezeDrawing( true );

  // Page view can't be rotated so just pan them back and forth
  bool bIsPageView = ( view->RhinoViewType() == CRhinoView::page_view_type );
    
  MSG msg;
  HWND hWnd = ::RhinoApp().MainWnd();
    
  if( bIsPageView )
  {
    time0 = ::GetTickCount();
    int i;
    for( i = 0; i < frame_count; i++ )
    {
      if( i < 5 || i % 20 > 10 )
        vp.LeftRightDolly( 0.05 );
      else
        vp.LeftRightDolly( -0.05 );
      dp->DrawFrameBuffer( da );
      dp->ShowFrameBuffer( pDC );
      ::PeekMessage( &msg, hWnd, 0, 0, PM_REMOVE );
    }
  }
  else
  {
    time0 = ::GetTickCount();
    int i;
    for( i = 0; i < frame_count; i++ ) 
    {
      vp.LeftRightRotate( delta_angle );
      dp->DrawFrameBuffer( da );
      dp->ShowFrameBuffer( pDC );
      ::PeekMessage( &msg, hWnd, 0, 0, PM_REMOVE );
    }
  }

  time1 = ::GetTickCount();
  delta_time = time1 - time0;
    
  if( dp )
    dp->FreezeDrawing( false );

  CRhinoDisplayPipeline::EnableFrameBufferCapture( true );
    
  // Now redraw the view since frame capturing has been turned back on.
  view->Redraw();

  return true;
}