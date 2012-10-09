/////////////////////////////////////////////////////////////////////////////
// cmdTestWinMsg.cpp

#include "StdAfx.h"
#include "TestWinMsgDialog.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestWinMsg command
//

class CCommandTestWinMsg : public CRhinoCommand
{
public:
	CCommandTestWinMsg() {}
  ~CCommandTestWinMsg() {}
	UUID CommandUUID()
	{
		// {87C9B2DE-5322-4898-B6A7-AEB45C840329}
    static const GUID TestWinMsgCommand_UUID =
    { 0x87C9B2DE, 0x5322, 0x4898, { 0xB6, 0xA7, 0xAE, 0xB4, 0x5C, 0x84, 0x3, 0x29 } };
    return TestWinMsgCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestWinMsg"; }
	const wchar_t* LocalCommandName() { return L"TestWinMsg"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestWinMsg object.  
static class CCommandTestWinMsg theTestWinMsgCommand;

CRhinoCommand::result CCommandTestWinMsg::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoCommand::result rc = CRhinoCommand::failure;

  CTestWinMsgDialog* pDialog = new CTestWinMsgDialog();
  if( pDialog && pDialog->Create(IDD_TESTWINMSG_DIALOG, CWnd::FromHandle(RhinoApp().MainWnd())) )
	{
		pDialog->ShowWindow( SW_SHOW );
		pDialog->UpdateWindow();
  }
  else
    return CRhinoCommand::failure;

  CRhinoGetOption go;
  go.SetCommandPrompt( L"Calculating, please wait...." );
  go.AcceptCustomWindowsMessage( CTestWinMsgDialog::TestWinMsgOk() );
  go.AcceptCustomWindowsMessage( CTestWinMsgDialog::TestWinMsgCancel() );
  while( true )
  {
    CRhinoGet::result res = go.GetOption();
    if( CRhinoGet::winmsg != res )
      continue;

    MSG msg = go.WindowsMessage();
    if( CTestWinMsgDialog::TestWinMsgOk() == msg.message )
      rc = CRhinoCommand::success;
    else
      rc = CRhinoCommand::cancel;

    break;
  }

  return rc;
}

//
// END TestWinMsg command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
