/////////////////////////////////////////////////////////////////////////////
// cmdTestDockBar.cpp

#include "StdAfx.h"
#include "TestDockBarPlugIn.h"
#include "TestDockBar.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestDockBar command
//
class CCommandTestDockBar : public CRhinoCommand
{
public:
	CCommandTestDockBar() {}
  ~CCommandTestDockBar() {}
	UUID CommandUUID()
	{
		// {C9780FB2-6680-4412-BACF-6F047D30E77B}
    static const GUID TestDockBarCommand_UUID =
    { 0xC9780FB2, 0x6680, 0x4412, { 0xBA, 0xCF, 0x6F, 0x4, 0x7D, 0x30, 0xE7, 0x7B } };
    return TestDockBarCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestDockBar"; }
	const wchar_t* LocalCommandName() { return L"TestDockBar"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

private:
	CRhinoCommand::result RunScriptCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestDockBar object
static class CCommandTestDockBar theTestDockBarCommand;

CRhinoCommand::result CCommandTestDockBar::RunCommand( const CRhinoCommandContext& context )
{
  if( !context.IsInteractive() )
	  return RunScriptCommand( context );

  CRhinoUiDockBarManager& dbm = RhinoUiDockBarManager();
  ON_UUID uuid = CTestDockBar::Id();
  if( !dbm.IsDockBarVisible(uuid) )
    dbm.ShowDockBar( uuid, true, false );

  return success;
}

CRhinoCommand::result CCommandTestDockBar::RunScriptCommand( const CRhinoCommandContext& context )
{
  CRhinoUiDockBarManager& dbm = RhinoUiDockBarManager();
  ON_UUID uuid = CTestDockBar::Id();
  bool bVisible = dbm.IsDockBarVisible( uuid );

  ON_wString str;
  if( bVisible )
    str = L"TestDockBar window is visible. New value";
  else
    str = L"TestDockBar window is hidden. New value";

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
// END TestDockBar command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
