/////////////////////////////////////////////////////////////////////////////
// cmdTestCustomOptions.cpp

#include "StdAfx.h"
#include "TestCustomOptionsPlugIn.h"
#include "TestCustomOptionsDockBar.h"

////////////////////////////////////////////////////////////////////////////////////
// CCommandTestCustomOptions

class CCommandTestCustomOptions : public CRhinoCommand
{
public:
	CCommandTestCustomOptions() {}
  ~CCommandTestCustomOptions() {}
	UUID CommandUUID()
	{
		// {BBA9D095-C905-4C27-9506-43DFC9CB188F}
    static const GUID TestCustomOptionsCommand_UUID =
    { 0xBBA9D095, 0xC905, 0x4C27, { 0x95, 0x6, 0x43, 0xDF, 0xC9, 0xCB, 0x18, 0x8F } };
    return TestCustomOptionsCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestCustomOptions"; }
	const wchar_t* LocalCommandName() { return L"TestCustomOptions"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

private:
  CRhinoCommand::result RunScriptCommand( const CRhinoCommandContext& context );
};

// The one and only CCommandTestCustomOptions object
static class CCommandTestCustomOptions theTestCustomOptionsCommand;

CRhinoCommand::result CCommandTestCustomOptions::RunCommand( const CRhinoCommandContext& context )
{
  if( !context.IsInteractive() )
	  return RunScriptCommand( context );

  CRhinoUiDockBarManager& dbm = RhinoUiDockBarManager();
  ON_UUID uuid = CTestCustomOptionsDockBar::Id();
  if( !dbm.IsDockBarVisible(uuid) )
    dbm.ShowDockBar( uuid, true, false );

  return CRhinoCommand::success;
}

CRhinoCommand::result CCommandTestCustomOptions::RunScriptCommand( const CRhinoCommandContext& context )
{
  CRhinoUiDockBarManager& dbm = RhinoUiDockBarManager();
  ON_UUID uuid = CTestCustomOptionsDockBar::Id();
  bool bVisible = dbm.IsDockBarVisible( uuid );

  ON_wString str;
  if( bVisible )
    str = L"BoxEdit window is visible. New value";
  else
    str = L"BoxEdit window is hidden. New value";

  CRhinoGetOption go;
  go.SetCommandPrompt( str );
  int h_option = go.AddCommandOption( RHCMDOPTNAME(L"Hide") );
  int s_option = go.AddCommandOption( RHCMDOPTNAME(L"Show") );
  int t_option = go.AddCommandOption( RHCMDOPTNAME(L"Toggle") );
  go.GetOption();
  if( go.CommandResult() != success )
    return go.CommandResult();

  const CRhinoCommandOption* option = go.Option();
  if( 0 == option )
    return failure;

  int option_index = option->m_option_index;
  if( h_option == option_index )
  {
    if( bVisible )
      dbm.ShowDockBar( uuid, false, false );
  }
  else if( s_option == option_index )
  {
    if( !bVisible )
      dbm.ShowDockBar( uuid, true, false );
  }
  else if( t_option == option_index )
  {
    dbm.ShowDockBar( uuid, !bVisible, false );
  }

  return success;
}

//
// END TestCustomOptions command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
