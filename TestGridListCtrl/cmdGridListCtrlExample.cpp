/////////////////////////////////////////////////////////////////////////////
// cmdGridListCtrlExample.cpp : command file
//

#include "StdAfx.h"
#include "GridListCtrlExamplePlugIn.h"
#include "Dialog1.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN GridListCtrlExample command
//

// Do NOT put the definition of class CCommandGridListCtrlExample in a header
// file.  There is only ONE instance of a CCommandGridListCtrlExample class
// and that instance is the static theGridListCtrlExampleCommand that appears
// immediately below the class definition.

class CCommandGridListCtrlExample : public CRhinoCommand
{
public:
  // The one and only instance of CCommandGridListCtrlExample is created below.
  // No copy constructor or operator= is required.  Values of
  // member variables persist for the duration of the application.

  // CCommandGridListCtrlExample::CCommandGridListCtrlExample()
  // is called exactly once when static theGridListCtrlExampleCommand is created.
	CCommandGridListCtrlExample() {}

  // CCommandGridListCtrlExample::~CCommandGridListCtrlExample()
  // is called exactly once when static theGridListCtrlExampleCommand is
  // destroyed.  The destructor should not make any calls to
  // the Rhino SDK.  If your command has persistent settings,
  // then override CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandGridListCtrlExample() {}

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work.  Use GUIDGEN.EXE to make unique UUID.
	UUID CommandUUID()
	{
		// {05C81721-C7AB-4611-AC2C-A91F917695D7}
    static const GUID GridListCtrlExampleCommand_UUID =
    { 0x5C81721, 0xC7AB, 0x4611, { 0xAC, 0x2C, 0xA9, 0x1F, 0x91, 0x76, 0x95, 0xD7 } };
    return GridListCtrlExampleCommand_UUID;
	}

  // Returns the English command name.
	const wchar_t* EnglishCommandName() { return L"GridListCtrlExample"; }

  // Returns the localized command name.
	const wchar_t* LocalCommandName() { return L"GridListCtrlExample"; }

  // Rhino calls RunCommand to run the command.
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandGridListCtrlExample object.  
// Do NOT create any other instance of a CCommandGridListCtrlExample class.
static class CCommandGridListCtrlExample theGridListCtrlExampleCommand;

CRhinoCommand::result CCommandGridListCtrlExample::RunCommand( const CRhinoCommandContext& context )
{
  CDialog1 dlg( context.m_doc, CWnd::FromHandle( RhinoApp().MainWnd()));

  switch( dlg.DoModal())
  {
    case IDABORT:
      return CRhinoCommand::failure;
    case IDOK:
      return CRhinoCommand::success;
  }

  return CRhinoCommand::cancel;
}

//
// END GridListCtrlExample command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
