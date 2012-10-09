/////////////////////////////////////////////////////////////////////////////
// cmdRhinoMark.cpp

#include "StdAfx.h"
#include "RhinoMarkPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN RhinoMark command
//

class CCommandRhinoMark : public CRhinoCommand
{
public:
	CCommandRhinoMark() : CRhinoCommand( true, false ) { m_frame_count = 100; m_bFreeze = true; }
  ~CCommandRhinoMark() {}

	UUID CommandUUID()
	{
		// {7662ADED-42C6-4CE2-B958-D37AA739F0BA}
    static const GUID RhinoMarkCommand_UUID =
    { 0x7662ADED, 0x42C6, 0x4CE2, { 0xB9, 0x58, 0xD3, 0x7A, 0xA7, 0x39, 0xF0, 0xBA } };
    return RhinoMarkCommand_UUID;
	}

	const wchar_t* EnglishCommandName() { return L"RhinoMark"; }
	const wchar_t* LocalCommandName() { return L"RhinoMark"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

  int m_frame_count;
  bool m_bFreeze;
};

// The one and only CCommandRhinoMark object.  
// Do NOT create any other instance of a CCommandRhinoMark class.
static class CCommandRhinoMark theRhinoMarkCommand;

CRhinoCommand::result CCommandRhinoMark::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoView* view = RhinoApp().ActiveView();
  if( view ) 
  {
    if( !context.IsInteractive() )
    {
      CRhinoGetOption go;
      go.SetCommandPrompt(L"Options");
      go.AddCommandOptionInteger( RHCMDOPTNAME(L"FrameCount"), &m_frame_count, L"Frame Count", 1, 5000 );
      go.AddCommandOptionToggle(  RHCMDOPTNAME(L"DisplayList"), RHCMDOPTVALUE(L"Rebuild"), RHCMDOPTVALUE(L"NoRebuild"), m_bFreeze, &m_bFreeze );
      while( go.GetOption() == CRhinoGet::option ) {}
    }

    DWORD delta_time = 0;
    bool rc = RhinoRegenBenchMark( view, delta_time, m_frame_count, m_bFreeze );
    if( rc )
      RhinoApp().Print("Time to regen viewport %d times = %.2lf seconds.\n", m_frame_count, delta_time / 1000.0 );
  }

  return success;
}

//
// END RhinoMark command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
