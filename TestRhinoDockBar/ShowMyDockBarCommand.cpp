/////////////////////////////////////////////////////////////////////////////
// ShowMyRhinoDockBarCommand.cpp : command file
//

#include "StdAfx.h"
#include "RhinoDockBarApp.h"
#include "MyRhinoDockBar.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ShowMyRhinoDockBar command
//

// Do NOT put the definition of class CCommandShowMyRhinoDockBar in a header
// file.  There is only ONE instance of a CCommandShowMyRhinoDockBar class
// and that instance is the static theShowMyRhinoDockBarCommand that appears
// immediately below the class definition.

class CCommandShowMyRhinoDockBar : public CRhinoCommand
{
public:
  // The one and only instance of CCommandShowMyRhinoDockBar is created below.
  // No copy constructor or operator= is required.  Values of
  // member variables persist for the duration of the application.

  // CCommandShowMyRhinoDockBar::CCommandShowMyRhinoDockBar()
  // is called exactly once when static theRhinoDockBarCommand is created.
	CCommandShowMyRhinoDockBar() {}

  // CCommandShowMyRhinoDockBar::~CCommandShowMyRhinoDockBar()
  // is called exactly once when static CCommandShowMyRhinoDockBar is
  // destroyed.  The destructor should not make any calls to
  // the Rhino SDK.  If your command has persistent settings,
  // then override CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandShowMyRhinoDockBar() {}

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work.  Use GUIDGEN.EXE to make unique UUID.
	UUID CommandUUID()
	{
  // {CA51E15A-A364-4E30-9F5B-FDDEAD1F7161}
    static const GUID RhinoDockBarCommand_UUID =
    { 0xCA51E15A, 0xA364, 0x4E30, { 0x9F, 0x5B, 0xFD, 0xDE, 0xAD, 0x1F, 0x71, 0x61 } };
    return RhinoDockBarCommand_UUID;
	}

  // Returns the English command name.
	const wchar_t* EnglishCommandName() { return L"ShowMyRhinoDockBar"; }

  // Returns the localized command name.
	const wchar_t* LocalCommandName() { return L"ShowMyRhinoDockBar"; }

  // Rhino calls RunCommand to run the command.
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandShowMyRhinoDockBar object.  
// Do NOT create any other instance of a CCommandShowMyRhinoDockBar class.
static class CCommandShowMyRhinoDockBar theShowMyRhinoDockBarCommand;

CRhinoCommand::result CCommandShowMyRhinoDockBar::RunCommand( const CRhinoCommandContext& context )
{
  // CCommandShowMyRhinoDockBar::RunCommand() is called when the user runs the "ShowMyRhinoDockBar"
  // command or the "ShowMyRhinoDockBar" command is run by a history operation.

  // TODO: Add command code here.

  // Rhino command that display a dialog box interface should also support
  // a command-line, or scriptable interface.

	  RhinoApp().Print(L"Showing MyRhinoDockBar...");

  // TODO: Return one of the following values:
  //   CRhinoCommand::success:  The command worked.
  //   CRhinoCommand::failure:  The command failed because of invalid input, inability
  //                            to compute the desired result, or some other reason
  //                            computation reason.
  //   CRhinoCommand::cancel:   The user interactively canceled the command 
  //                            (by pressing ESCAPE, clicking a CANCEL button, etc.)
  //                            in a Get operation, dialog, time consuming computation, etc.



////////////////////////////////////////////////////////////////////////////////////
// show the dockbar
//
	//ask Rhino's DockBarManager to show our dockbar
	::RhinoUiDockBarManager().ShowDockBar(CMyRhinoDockBar().DockBarID(), true, false);
//
// end show the dockbar
////////////////////////////////////////////////////////////////////////////////////



  return CRhinoCommand::success;
}

//
// END ShowMyRhinoDockBarCommand
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
