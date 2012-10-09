#include "StdAfx.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestDecorate command
//

class CTestDecorateEventWatcher : public CRhinoEventWatcher
{
public:
  CTestDecorateEventWatcher();
  ~CTestDecorateEventWatcher() {}

  void SetActiveView( CRhinoView* active_view );

  // CRhinoEventWatcher overrides
  void OnSetActiveView( CRhinoView* new_active_view );

private:
  CRhinoView* m_old_active_view;
};

CTestDecorateEventWatcher::CTestDecorateEventWatcher()
: m_old_active_view(0)
{
}

void CTestDecorateEventWatcher::SetActiveView( CRhinoView* active_view )
{
  m_old_active_view = active_view;
}

void CTestDecorateEventWatcher::OnSetActiveView( CRhinoView* new_active_view )
{
  // Regenerate the old active view (to remove decoration)
  if( m_old_active_view )
    m_old_active_view->Redraw( CRhinoView::regenerate_display_hint );

  // Regenerate the new active view (to draw decoration)
  if( new_active_view )
    new_active_view->Redraw( CRhinoView::regenerate_display_hint );

  m_old_active_view = new_active_view;
}

////////////////////////////////////////////////////////////////

class CTextDecorationConduit : public CRhinoDisplayConduit
{
public:
  CTextDecorationConduit();
  ~CTextDecorationConduit() {}
  bool ExecConduit(
        CRhinoDisplayPipeline& dp, // pipeline executing this conduit
        UINT nChannelID,           // current channel within the pipeline
        bool& bTerminationFlag     // channel termination flag
        );    
};

CTextDecorationConduit::CTextDecorationConduit()
: CRhinoDisplayConduit( CSupportChannels::SC_DRAWFOREGROUND )
{
}

bool CTextDecorationConduit::ExecConduit( CRhinoDisplayPipeline& dp, UINT nChannelID, bool& bTerminationFlag )
{
  // Get the active view
  CRhinoView* view = RhinoApp().ActiveView();
  if( 0 == view )
    return true;

  // Get the viewport that we are currently drawing in
  CRhinoViewport& vp = dp.GetRhinoVP();

  // Compare ids
  if( view->ActiveViewportID() != vp.ViewportId() )
    return true;

  if( nChannelID == CSupportChannels::SC_DRAWFOREGROUND )
  {
    // Use the screen port to determine text location
    int vp_left, vp_right, vp_top, vp_bottom;
    vp.VP().GetScreenPort( &vp_left, &vp_right, &vp_bottom, &vp_top );
    int vp_width = vp_right - vp_left;
    int vp_height = vp_bottom - vp_top;

    // Determine rect of text string
    ON_wString str( L"Hello Rhino!" );
    CRect rect;
    dp.MeasureString( rect, str, str.Length(), ON_2dPoint(0,0) );

    // Make sure text will fit on string
    int x_gap = 4;
    int y_gap = 4;
    if( rect.Width() + (2*x_gap) < vp_width ||  rect.Height() + (2*y_gap) < vp_height )
    {
      // Cook up text location (lower right corner of viewport)
      ON_2dPoint point( vp_right - rect.Width() - x_gap, vp_bottom - y_gap );

      // Draw text
      dp.DrawString( str, str.Length(), RGB(255,255,255), point );
    }
  }

  return true;
}

////////////////////////////////////////////////////////////////

class CCommandTestDecorate : public CRhinoCommand
{
public:
	CCommandTestDecorate();
	~CCommandTestDecorate() {}
	UUID CommandUUID()
	{
		// {A3FBFCB7-2FBE-4492-A0F5-5F90446D9510}
		static const GUID TestDecorateCommand_UUID =
		{ 0xA3FBFCB7, 0x2FBE, 0x4492, { 0xA0, 0xF5, 0x5F, 0x90, 0x44, 0x6D, 0x95, 0x10 } };
		return TestDecorateCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestDecorate"; }
	const wchar_t* LocalCommandName() { return L"TestDecorate"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

private:
  CTextDecorationConduit m_conduit;
  CTestDecorateEventWatcher m_watcher;
};

// The one and only CCommandTestDecorate object
static class CCommandTestDecorate theTestDecorateCommand;

CCommandTestDecorate::CCommandTestDecorate()
{
  // Register our event watcher
  m_watcher.Register();
}

CRhinoCommand::result CCommandTestDecorate::RunCommand( const CRhinoCommandContext& context )
{
  bool bEnable = m_conduit.IsEnabled();

  CRhinoGetOption go;
  go.SetCommandPrompt( L"Decoration options" );
  go.AddCommandOptionToggle( RHCMDOPTNAME(L"Enable"), RHCMDOPTVALUE(L"No"), RHCMDOPTVALUE(L"Yes"), bEnable, &bEnable );
  go.AcceptNothing();
  for(;;)
  {
    CRhinoGet::result res = go.GetOption();

    if( res == CRhinoGet::option )
    {
      // Get the active view
      CRhinoView* view = RhinoApp().ActiveView();
      if( 0 == view )
      {
        RhinoApp().Print( L"Unable to obtain the active view.\n" );
        return failure;
      }

      if( bEnable )
      {
        m_watcher.SetActiveView( view );
        m_watcher.Enable( TRUE );
        m_conduit.Enable();
      }
      else
      {
        m_watcher.SetActiveView( 0 );
        m_watcher.Enable( FALSE );
        m_conduit.Disable();
      }
      
      // Redraw the active view
      view->Redraw( CRhinoView::regenerate_display_hint );
      continue;
    }

    break;
  }

  return success;
}

//
// END TestDecorate command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
