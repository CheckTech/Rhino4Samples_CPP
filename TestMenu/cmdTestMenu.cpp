/////////////////////////////////////////////////////////////////////////////
// cmdTestMenu.cpp : command file
//

#include "StdAfx.h"
#include "TestMenuPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestMenu1 command
//

class CCommandTestMenu1 : public CRhinoCommand
{
public:
	CCommandTestMenu1() {}
	~CCommandTestMenu1() {}
	UUID CommandUUID()
	{
		// {68F5E001-A331-49FD-9D5F-2E8D42C4ED39}
		static const GUID TestMenu1Command_UUID =
		{ 0x68F5E001, 0xA331, 0x49FD, { 0x9D, 0x5F, 0x2E, 0x8D, 0x42, 0xC4, 0xED, 0x39 } };
		return TestMenu1Command_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestMenu1"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestMenu1 object
static class CCommandTestMenu1 theTestMenu1Command;

CRhinoCommand::result CCommandTestMenu1::RunCommand( const CRhinoCommandContext& context )
{
  ON_wString wStr;
  wStr.Format(L"The \"%s\" command is under construction.\n", EnglishCommandName() );
  if( context.IsInteractive() )
    RhinoMessageBox( wStr, PlugIn()->PlugInName(), MB_OK );
  else
	  RhinoApp().Print( wStr );
	return CRhinoCommand::success;
}

//
// END TestMenu1 command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestMenu2 command
//

class CCommandTestMenu2 : public CRhinoCommand
{
public:
	CCommandTestMenu2() {}
	~CCommandTestMenu2() {}
	UUID CommandUUID()
	{
		// {EDC337AA-FED5-4873-8779-7FE515097B1E}
		static const GUID TestMenu2Command_UUID =
		{ 0xEDC337AA, 0xFED5, 0x4873, { 0x87, 0x79, 0x7F, 0xE5, 0x15, 0x09, 0x7B, 0x1E } };
		return TestMenu2Command_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestMenu2"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestMenu2 object
static class CCommandTestMenu2 theTestMenu2Command;

CRhinoCommand::result CCommandTestMenu2::RunCommand( const CRhinoCommandContext& context )
{
  ON_wString wStr;
  wStr.Format(L"The \"%s\" command is under construction.\n", EnglishCommandName() );
  if( context.IsInteractive() )
    RhinoMessageBox( wStr, PlugIn()->PlugInName(), MB_OK );
  else
	  RhinoApp().Print( wStr );
	return CRhinoCommand::success;
}

//
// END TestMenu2 command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
