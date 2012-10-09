/////////////////////////////////////////////////////////////////////////////
// cmdTestRhinoPreview.cpp

#include "StdAfx.h"
#include "TestRhinoPreviewPlugIn.h"
#include "TestRhinoPreviewDialog.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestRhinoPreview command
//
class CCommandTestRhinoPreview : public CRhinoCommand
{
public:
	CCommandTestRhinoPreview() {}
  ~CCommandTestRhinoPreview() {}
	UUID CommandUUID()
	{
		// {D7A6C4D7-E1D3-43AA-8071-B78DD8896C96}
    static const GUID TestRhinoPreviewCommand_UUID =
    { 0xD7A6C4D7, 0xE1D3, 0x43AA, { 0x80, 0x71, 0xB7, 0x8D, 0xD8, 0x89, 0x6C, 0x96 } };
    return TestRhinoPreviewCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestRhinoPreview"; }
	const wchar_t* LocalCommandName() { return L"TestRhinoPreview"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};
static class CCommandTestRhinoPreview theTestRhinoPreviewCommand;

CRhinoCommand::result CCommandTestRhinoPreview::RunCommand( const CRhinoCommandContext& context )
{
  CTestRhinoPreviewDialog dialog( CWnd::FromHandle(RhinoApp().MainWnd()) );
  dialog.DoModal();
  return CRhinoCommand::success;
}

//
// END TestRhinoPreview command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
