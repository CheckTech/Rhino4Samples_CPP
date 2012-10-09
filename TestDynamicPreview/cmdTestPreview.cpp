/////////////////////////////////////////////////////////////////////////////
// cmdTestPreview.cpp

#include "StdAfx.h"
#include "TestPreviewPlugIn.h"
#include "TestPreviewDialog.h"

class CCommandTestPreview : public CRhinoCommand
{
public:
	CCommandTestPreview() {}
  ~CCommandTestPreview() {}
	UUID CommandUUID()
	{
		// {E88E171C-F2C6-4A21-B7C7-FD424E8ACC13}
    static const GUID TestPreviewCommand_UUID =
    { 0xE88E171C, 0xF2C6, 0x4A21, { 0xB7, 0xC7, 0xFD, 0x42, 0x4E, 0x8A, 0xCC, 0x13 } };
    return TestPreviewCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestPreview"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only instance of CCommandTestPreview
static class CCommandTestPreview theTestPreviewCommand;

CRhinoCommand::result CCommandTestPreview::RunCommand( const CRhinoCommandContext& context )
{
  CTestPreviewDialog dialog;
  if( dialog.DoModal() == IDOK )
    context.m_doc.AddCurveObject( dialog.m_preview.m_circle );

  return CRhinoCommand::success;
}
