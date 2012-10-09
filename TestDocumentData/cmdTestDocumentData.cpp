/////////////////////////////////////////////////////////////////////////////
// cmdTestDocumentData.cpp : command file
//

#include "StdAfx.h"
#include "TestDocumentDataPlugIn.h"
#include "Resource.h"

////////////////////////////////////////////////////////////////
// CCommandTestDocumentData
//

class CCommandTestDocumentData : public CRhinoCommand
{
public:
	CCommandTestDocumentData() {}
  ~CCommandTestDocumentData() {}

	UUID CommandUUID()
	{
		// {4E54467C-4A56-4249-AD9C-F129BC070D47}
		static const GUID TestDocumentDataCommand_UUID =
    { 0x4E54467C, 0x4A56, 0x4249, { 0xAD, 0x9C, 0xF1, 0x29, 0xBC, 0x07, 0x0D, 0x47 } };
		return TestDocumentDataCommand_UUID;
	}

	const wchar_t* EnglishCommandName() { return L"TestDocumentData"; }
	const wchar_t* LocalCommandName() const { return L"TestDocumentData"; }

	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

  enum CommandOptions
  {
    add_option = 1,
    delete_option,
    list_option,
    option_count
  };

private:
  CRhinoCommand::result CommandOption( const CRhinoCommandOption* option );
  CRhinoCommand::result AddOption();
  CRhinoCommand::result DeleteOption();
  CRhinoCommand::result ListOption();
};

static class CCommandTestDocumentData theTestDocumentDataCommand;

CRhinoCommand::result CCommandTestDocumentData::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetOption go;
  go.SetCommandPrompt( L"Choose an option" );
  go.AddCommandOption( RHCMDOPTNAME(L"Add") );
  go.AddCommandOption( RHCMDOPTNAME(L"Delete") );
  go.AddCommandOption( RHCMDOPTNAME(L"List") );
  go.AcceptNothing();

  for( ;; )
  {
    CRhinoGet::result res = go.GetOption();
    switch( res )
    {
      case CRhinoGet::option:
        if( CommandOption( go.Option() ) == CRhinoCommand::cancel )
          return CRhinoCommand::cancel;
        break;
      case CRhinoGet::nothing:
        return CRhinoCommand::success;
      default:
        return CRhinoCommand::cancel;
    }
  }	
  
  return CRhinoCommand::success;
}

CRhinoCommand::result CCommandTestDocumentData::CommandOption( const CRhinoCommandOption* option )
{
  if( !option )
    return CRhinoCommand::cancel;

  switch( option->m_option_index )
  {
    case add_option:
      return AddOption();
    case delete_option:
      return DeleteOption();
    case list_option:
      return ListOption();
  }

  return CRhinoCommand::cancel;
}

CRhinoCommand::result CCommandTestDocumentData::AddOption()
{  
  CRhinoGetString get;
  get.SetCommandPrompt( L"String to add" );
  get.AcceptNothing();
  switch( get.GetString() )
  {
    case CRhinoGet::string:
      break;
    case CRhinoGet::nothing:
      return CRhinoCommand::nothing;
    default:
      return CRhinoCommand::cancel;
  }

  ON_wString wstr( get.String() );
  wstr.TrimLeft();
  wstr.TrimRight();
  if( wstr.IsEmpty() )
    return CRhinoCommand::nothing;

  CTestDocumentDataPlugIn& plugin = TestDocumentDataPlugIn();
  int nItem = plugin.FindStringTableItem( wstr );
  if( nItem < 0 )
    plugin.m_string_table.Append( wstr );
  else
    RhinoApp().Print( L"String already exists!\n" );

  return CRhinoCommand::success;
}

CRhinoCommand::result CCommandTestDocumentData::DeleteOption()
{  
  CRhinoGetString get;
  get.SetCommandPrompt( L"String to remove" );
  get.AcceptNothing();
  switch( get.GetString() )
  {
    case CRhinoGet::string:
      break;
    case CRhinoGet::nothing:
      return CRhinoCommand::nothing;
    default:
      return CRhinoCommand::cancel;
  }

  ON_wString wstr( get.String() );
  wstr.TrimLeft();
  wstr.TrimRight();
  if( wstr.IsEmpty() )
    return CRhinoCommand::nothing;

  CTestDocumentDataPlugIn& plugin = TestDocumentDataPlugIn();
  int nItem = plugin.FindStringTableItem( wstr );
  if( nItem > -1 )
    plugin.m_string_table.Remove(nItem);
  else
    RhinoApp().Print( L"Error removing string!\n" );

  return CRhinoCommand::success;
}

CRhinoCommand::result CCommandTestDocumentData::ListOption()
{  
  CTestDocumentDataPlugIn& plugin = TestDocumentDataPlugIn();
  for( int i = 0; i < plugin.m_string_table.Count(); i++ )
    RhinoApp().Print( L"%s\n", plugin.m_string_table[i] );
  return CRhinoCommand::success;
}