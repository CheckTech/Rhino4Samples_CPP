/////////////////////////////////////////////////////////////////////////////
// cmdHippoPlugIn.cpp : command file
//

#include "StdAfx.h"
#include "HippoPlugInPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN HippoPlugIn command
//
class CCommandHippoPlugIn : public CRhinoCommand
{
public:
	CCommandHippoPlugIn() {}
  ~CCommandHippoPlugIn() {}
	UUID CommandUUID()
	{
		// {06E4AB85-CBA1-48B5-BA50-88F2B2612F16}
    static const GUID HippoPlugInCommand_UUID =
    { 0x6E4AB85, 0xCBA1, 0x48B5, { 0xBA, 0x50, 0x88, 0xF2, 0xB2, 0x61, 0x2F, 0x16 } };
    return HippoPlugInCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"HippoPlugIn"; }
	const wchar_t* LocalCommandName() { return L"HippoPlugIn"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};
static class CCommandHippoPlugIn theHippoPlugInCommand;

CRhinoCommand::result CCommandHippoPlugIn::RunCommand( const CRhinoCommandContext& context )
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
// END HippoPlugIn command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
