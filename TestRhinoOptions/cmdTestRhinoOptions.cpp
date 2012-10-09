#include "StdAfx.h"
#include "TestRhinoOptionsPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestRhinoOptions command
//
class CCommandTestRhinoOptions : public CRhinoCommand
{
public:
	CCommandTestRhinoOptions() {}
  ~CCommandTestRhinoOptions() {}
	UUID CommandUUID()
	{
		// {68975261-22D6-47D2-AC97-72FFFC4C241B}
    static const GUID TestRhinoOptionsCommand_UUID =
    { 0x68975261, 0x22D6, 0x47D2, { 0xAC, 0x97, 0x72, 0xFF, 0xFC, 0x4C, 0x24, 0x1B } };
    return TestRhinoOptionsCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestRhinoOptions"; }
	const wchar_t* LocalCommandName() { return L"TestRhinoOptions"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};
static class CCommandTestRhinoOptions theTestRhinoOptionsCommand;

CRhinoCommand::result CCommandTestRhinoOptions::RunCommand( const CRhinoCommandContext& context )
{
  ON_wString wStr;
  wStr.Format( L"The \"%s\" command is under construction.\n", EnglishCommandName() );
  if( context.IsInteractive() )
    RhinoMessageBox( wStr, PlugIn()->PlugInName(), MB_OK );
  else
	  RhinoApp().Print( wStr );
  return CRhinoCommand::success;
}

//
// END TestRhinoOptions command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
