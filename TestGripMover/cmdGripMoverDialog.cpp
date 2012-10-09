/////////////////////////////////////////////////////////////////////////////
// cmdGripMoverDialog.cpp : command file
//

#include "StdAfx.h"
#include "GripMoverPlugIn.h"
#include "MoveDialog.h"

using namespace std;

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN GripMoverDialog command
//
class CCommandGripMoverDialog : public CRhinoCommand
{
public:
	CCommandGripMoverDialog() {}
  ~CCommandGripMoverDialog() {}
	UUID CommandUUID()
	{
		// {08BD0005-92C7-49b2-87DF-63FA0711E058}
		static const GUID GripMoverDialogCommand_UUID = 
		{ 0x8bd0005, 0x92c7, 0x49b2, { 0x87, 0xdf, 0x63, 0xfa, 0x7, 0x11, 0xe0, 0x58 } };
	    return GripMoverDialogCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"GripMoverDialog"; }
	const wchar_t* LocalCommandName() { return L"GripMoverDialog"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
	void deleteDialog();

};
static class CCommandGripMoverDialog theGripMoverDialogCommand;

static CMoveDialog* move_dialog = NULL;

CRhinoCommand::result CCommandGripMoverDialog::RunCommand( const CRhinoCommandContext& context )
{
	// Toggle dialog.

	if( move_dialog != NULL && !move_dialog->IsWindowVisible() )
	{
		deleteDialog();
	}

	if( move_dialog == NULL )
	{
		// Create and show dialog.
		move_dialog = new CMoveDialog( CWnd::FromHandle(RhinoApp().MainWnd()) );
		if( move_dialog->Create(IDD_DIALOG1, CWnd::FromHandle(RhinoApp().MainWnd())) )
		{
			move_dialog->ShowWindow( SW_SHOW );
			move_dialog->UpdateWindow();
			move_dialog->SetFocus();
		}
		else
		{
			deleteDialog();
		}
	}
	else
	{
		// Delete dialog.
		deleteDialog();
	}
	
	return success;
}

void CCommandGripMoverDialog::deleteDialog()
{
	delete move_dialog;
	move_dialog = NULL;
}

//
// END GripMoverDialog command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
