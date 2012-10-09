/////////////////////////////////////////////////////////////////////////////
// cmdTestDocUserText.cpp : command file
//

#include "StdAfx.h"
#include "TestDocUserTextPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN SetDocUserText command
//

class CCommandSetDocUserText : public CRhinoCommand
{
public:
	CCommandSetDocUserText() {}
	~CCommandSetDocUserText() {}
	UUID CommandUUID()
	{
		// {36D2A1A6-65DC-45C8-9979-04D0EB6725FA}
		static const GUID SetDocUserTextCommand_UUID =
		{ 0x36D2A1A6, 0x65DC, 0x45C8, { 0x99, 0x79, 0x04, 0xD0, 0xEB, 0x67, 0x25, 0xFA } };
		return SetDocUserTextCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"SetDocUserText"; }
	const wchar_t* LocalCommandName() { return L"SetDocUserText"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandSetDocUserText object
static class CCommandSetDocUserText theSetDocUserTextCommand;

CRhinoCommand::result CCommandSetDocUserText::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetString gid;
  gid.SetCommandPrompt( L"Text key" );
  gid.GetString();
  if( gid.CommandResult() != success )
    return gid.CommandResult();

  ON_wString key = gid.String();

  CRhinoGetString gs;
  gs.SetCommandPrompt( L"Text" );
  gs.GetString();
  if( gs.CommandResult() != success )
    return gs.CommandResult();

  ON_wString string_value = gs.String();

  CTestDocUserTextPlugIn& plugin = TestDocUserTextPlugIn();
  plugin.SetDocUserString( key, string_value );

	return success;
}

//
// END SetDocUserText command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN GetDocUserText command
//

class CCommandGetDocUserText : public CRhinoCommand
{
public:
	CCommandGetDocUserText() {}
	~CCommandGetDocUserText() {}
	UUID CommandUUID()
	{
		// {713B393-A2D2-4481-B8C8-387BFE822F1E}
		static const GUID GetDocUserTextCommand_UUID =
		{ 0x713B393, 0xA2D2, 0x4481, { 0xB8, 0xC8, 0x38, 0x7B, 0xFE, 0x82, 0x2F, 0x1E } };
		return GetDocUserTextCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"GetDocUserText"; }
	const wchar_t* LocalCommandName() { return L"GetDocUserText"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandGetDocUserText object
static class CCommandGetDocUserText theGetDocUserTextCommand;

CRhinoCommand::result CCommandGetDocUserText::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetString gid;
  gid.SetCommandPrompt( L"Text key" );
  gid.SetCommandPromptDefault( L"All keys" );
  gid.AcceptNothing();
  gid.GetString();
  if( gid.CommandResult() != success )
    return gid.CommandResult();

  bool bAllKeys = false;
  ON_wString key = gid.String();
  if( gid.Result() == CRhinoGet::nothing || key.IsEmpty() || 0 == key.Length() )
  {
    bAllKeys = true;
    key.Destroy();
  }

  CTestDocUserTextPlugIn& plugin = TestDocUserTextPlugIn();

  if( bAllKeys )
  {
    ON_ClassArray<ON_UserString> user_strings;
    if( plugin.GetDocUserStrings(user_strings) )
    {
      int si, scount = user_strings.Count();
      RhinoApp().Print( L"%d document user strings.\n", scount );
      for( si = 0; si < scount; si++ )
      {
        const wchar_t* key = user_strings[si].m_key;
        const wchar_t* value = user_strings[si].m_string_value;
        if( 0 == key )
          key = L"";
        if ( 0 == value )
          value = L"";
        RhinoApp().Print( L"  <%s> %s.\n", key, value );
      }
    }
  }
  else
  {
    ON_wString string_value;
    if( plugin.GetDocUserString(key, string_value) )
      RhinoApp().Print( L"Document text: %s\n", string_value.Array() );
    else
      RhinoApp().Print( L"Key not found.\n" );
  }

	return CRhinoCommand::success;
}

//
// END GetDocUserText command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
