/////////////////////////////////////////////////////////////////////////////
// cmdTestOptionsListCtrl.cpp

#include "StdAfx.h"
#include "TestOptionsListCtrlPlugIn.h"
#include "TestOptionsListCtrlDockBar.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestOptionsListCtrl command
//
class CCommandTestOptionsListCtrl : public CRhinoCommand
{
public:
	CCommandTestOptionsListCtrl() {}
  ~CCommandTestOptionsListCtrl() {}
	UUID CommandUUID()
	{
		// {834588E8-1FD3-4E14-ABD4-36EDD9C079F5}
    static const GUID TestOptionsListCtrlCommand_UUID =
    { 0x834588E8, 0x1FD3, 0x4E14, { 0xAB, 0xD4, 0x36, 0xED, 0xD9, 0xC0, 0x79, 0xF5 } };
    return TestOptionsListCtrlCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestOptionsListCtrl"; }
	const wchar_t* LocalCommandName() { return L"TestOptionsListCtrl"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

private:
	CRhinoCommand::result RunScriptCommand( const CRhinoCommandContext& );

};

static class CCommandTestOptionsListCtrl theTestOptionsListCtrlCommand;

CRhinoCommand::result CCommandTestOptionsListCtrl::RunCommand( const CRhinoCommandContext& context )
{
  if( !context.IsInteractive() )
	  return RunScriptCommand( context );

  CRhinoUiDockBarManager& dbm = RhinoUiDockBarManager();
  ON_UUID uuid = CTestOptionsListCtrlDockBar::Id();
  if( !dbm.IsDockBarVisible(uuid) )
    dbm.ShowDockBar( uuid, true, false );

  return success;
}

CRhinoCommand::result CCommandTestOptionsListCtrl::RunScriptCommand( const CRhinoCommandContext& context )
{
  CRhinoUiDockBarManager& dbm = RhinoUiDockBarManager();
  ON_UUID uuid = CTestOptionsListCtrlDockBar::Id();
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
// END TestOptionsListCtrl command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
