/////////////////////////////////////////////////////////////////////////////
// cmdToolBarTestPlugIn.cpp : command file
//

#include "StdAfx.h"
#include "ToolBarTestPlugInPlugIn.h"
#include "resource.h"
#include "ToolbarsDlg.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ToolBarTestPlugIn command
//

// Do NOT put the definition of class CCommandToolBarTestPlugIn in a header
// file.  There is only ONE instance of a CCommandToolBarTestPlugIn class
// and that instance is the static theToolBarTestPlugInCommand that appears
// immediately below the class definition.

class CCommandToolBarTestPlugIn : public CRhinoCommand
{
public:
  // The one and only instance of CCommandToolBarTestPlugIn is created below.
  // No copy constructor or operator= is required.  Values of
  // member variables persist for the duration of the application.

  // CCommandToolBarTestPlugIn::CCommandToolBarTestPlugIn()
  // is called exactly once when static theToolBarTestPlugInCommand is created.
	CCommandToolBarTestPlugIn() {}

  // CCommandToolBarTestPlugIn::~CCommandToolBarTestPlugIn()
  // is called exactly once when static theToolBarTestPlugInCommand is
  // destroyed.  The destructor should not make any calls to
  // the Rhino SDK.  If your command has persistent settings,
  // then override CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandToolBarTestPlugIn() {}

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work.  Use GUIDGEN.EXE to make unique UUID.
	UUID CommandUUID()
	{
		// {8236476C-0417-4559-B1DC-EF5F61B527D0}
    static const GUID ToolBarTestPlugInCommand_UUID =
    { 0x8236476C, 0x417, 0x4559, { 0xB1, 0xDC, 0xEF, 0x5F, 0x61, 0xB5, 0x27, 0xD0 } };
    return ToolBarTestPlugInCommand_UUID;
	}

  // Returns the English command name.
	const wchar_t* EnglishCommandName() { return L"ToolBarTestPlugIn"; }

  // Returns the localized command name.
	const wchar_t* LocalCommandName() { return L"ToolBarTestPlugIn"; }

  // Rhino calls RunCommand to run the command.
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandToolBarTestPlugIn object.  
// Do NOT create any other instance of a CCommandToolBarTestPlugIn class.
static class CCommandToolBarTestPlugIn theToolBarTestPlugInCommand;

CRhinoCommand::result CCommandToolBarTestPlugIn::RunCommand( const CRhinoCommandContext& context )
{
  // Display file dialog prompting user file tool bar file name
  CRhinoGetFileDialog gfd;
  if( !context.IsInteractive())
    gfd.SetScriptMode( true); // Don't show file dialog if not in interactive mode
  if( !gfd.DisplayFileDialog( CRhinoGetFileDialog::open_toolbar_collection_dialog))
    return CRhinoCommand::cancel;
  // Check to see if this collection is already open
  if( RhinoApp().RhinoUiToolBarManager().Collection( gfd.FileName(), false))
  { // collection is currently open so nothing to do
    if( context.IsInteractive())
    {
      ON_wString w;
      w.Format( L"Collection file is already open\n\n%s", gfd.FileName());
      ::RhinoMessageBox( w, L"Open Collection", MB_OK|MB_ICONINFORMATION);
    }
    else
      RhinoApp().Print( L"Collection file is already open: \"%s\"", gfd.FileName());
    return CRhinoCommand::success;
  }
  // Attempt to read the collection
  bool success = RhinoApp().RhinoUiToolBarManager().ReadFile( gfd.FileName(), // Collection file to read
                                                              true, // Create tool bars
                                                              true, // Recalculate layout
                                                              true // Show progress control
                                                            );
  if( !success)
    return CRhinoCommand::failure;

  RhinoApp().Print( L"Tool bar collection file \"%s\" read successfully\n", gfd.FileName());

  if( context.IsInteractive())
  {
    CToolbarsDlg dlg( gfd.FileName(), CWnd::FromHandle( RhinoApp().MainWnd()));
    dlg.DoModal();
  }
  return CRhinoCommand::success;
}

//
// END ToolBarTestPlugIn command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
