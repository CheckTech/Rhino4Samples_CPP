/////////////////////////////////////////////////////////////////////////////
// cmdDockBarWithUserDialogs.cpp

#include "StdAfx.h"
#include "DockBarWithUserDialogsPlugIn.h"
#include "DockBarWithUserDialogs.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN DockBarWithUserDialogs command
//

class CCommandDockBarWithUserDialogs : public CRhinoCommand
{
public:
	CCommandDockBarWithUserDialogs() {}
  ~CCommandDockBarWithUserDialogs() {}
	UUID CommandUUID()
	{
		// {84D581FB-9EBE-4F8B-B607-77349CDDC18F}
    static const GUID DockBarWithUserDialogsCommand_UUID =
    { 0x84D581FB, 0x9EBE, 0x4F8B, { 0xB6, 0x7, 0x77, 0x34, 0x9C, 0xDD, 0xC1, 0x8F } };
    return DockBarWithUserDialogsCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"DockBarWithUserDialogs"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

static class CCommandDockBarWithUserDialogs theDockBarWithUserDialogsCommand;

CRhinoCommand::result CCommandDockBarWithUserDialogs::RunCommand( const CRhinoCommandContext& context )
{
  if( 0 == DockBarWithUserDialogsPlugIn().m_pDockBar )
    return CRhinoCommand::failure;
  
  CRhinoGetOption get;
  const int iA = get.AddCommandOption(CRhinoCommandOptionName(L"A", L"A"));
  const int iB = get.AddCommandOption(CRhinoCommandOptionName(L"B", L"B"));
  const int iC = get.AddCommandOption(CRhinoCommandOptionName(L"C", L"C"));
  get.GetOption();
  if( get.CommandResult() != CRhinoCommand::success )
    return get.CommandResult();

  if( get.Result() == CRhinoGet::option && get.Option() )
  {
    int iShowDialog = -1;
    if( iA == get.Option()->m_option_index )
      iShowDialog = 0;
    else if( iB == get.Option()->m_option_index )
      iShowDialog = 1;
    else if( iC == get.Option()->m_option_index )
      iShowDialog = 2;
    if( iShowDialog >= 0 )
      DockBarWithUserDialogsPlugIn().m_pDockBar->ShowDialog( iShowDialog );
  }

  RhinoApp().RhinoUiDockBarManager().ShowDockBar( DockBarWithUserDialogsPlugIn().m_pDockBar, true, false );
 
  return CRhinoCommand::success;
}

//
// END DockBarWithUserDialogs command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
