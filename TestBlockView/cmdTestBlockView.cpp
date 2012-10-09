/////////////////////////////////////////////////////////////////////////////
// cmdTestBlockView.h

#include "StdAfx.h"
#include "TestBlockViewDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CCommandTestBlockView

class CCommandTestBlockView : public CRhinoCommand
{
public:
	CCommandTestBlockView() {}
  ~CCommandTestBlockView() {}
	UUID CommandUUID()
	{
		// {94E45BC9-0270-40E0-939A-7B7D32726CBE}
    static const GUID TestBlockViewCommand_UUID =
    { 0x94E45BC9, 0x270, 0x40E0, { 0x93, 0x9A, 0x7B, 0x7D, 0x32, 0x72, 0x6C, 0xBE } };
    return TestBlockViewCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestBlockView"; }
	const wchar_t* LocalCommandName() { return L"TestBlockView"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestBlockView object
static class CCommandTestBlockView theTestBlockViewCommand;

CRhinoCommand::result CCommandTestBlockView::RunCommand( const CRhinoCommandContext& context )
{
  const CRhinoInstanceDefinitionTable& idef_table = context.m_doc.m_instance_definition_table;

  bool bFound = false;
  int i;
  for( i = 0; i < idef_table.InstanceDefinitionCount(); i++ )
  {
    const CRhinoInstanceDefinition* idef = idef_table[i];
    if( idef && !idef->IsDeleted() )
    {
      bFound = true;
      break;
    }
  }

  if( !bFound )
  {
    ON_wString msg( L"No block definitions to view.\n" );
    if( context.IsInteractive() )
      RhinoMessageBox( msg, EnglishCommandName(), MB_OK );
    else
	    RhinoApp().Print( msg );
    return nothing;
  }

  CTestBlockViewDialog dialog( CWnd::FromHandle(RhinoApp().MainWnd()), context.m_doc );
  dialog.DoModal();

  return success;
}
