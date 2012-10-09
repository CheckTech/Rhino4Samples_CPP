/////////////////////////////////////////////////////////////////////////////
// cmdPlugIn1.cpp : command file
//

#include "StdAfx.h"
#include "PlugIn1PlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN PlugIn1Add command
//

class CCommandPlugIn1Add : public CRhinoCommand
{
public:
	CCommandPlugIn1Add() {}
	~CCommandPlugIn1Add() {}
	UUID CommandUUID()
	{
		// {9FF2AEC5-E5EF-4A45-83C4-5DD83E8BCC15}
		static const GUID PlugIn1AddCommand_UUID =
		{ 0x9FF2AEC5, 0xE5EF, 0x4A45, { 0x83, 0xC4, 0x5D, 0xD8, 0x3E, 0x8B, 0xCC, 0x15 } };
		return PlugIn1AddCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"PlugIn1Add"; }
	const wchar_t* LocalCommandName() { return L"PlugIn1Add"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandPlugIn1Add object
static class CCommandPlugIn1Add thePlugIn1AddCommand;

CRhinoCommand::result CCommandPlugIn1Add::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select object" );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != success )
    return go.CommandResult();

  const CRhinoObject* object = go.Object(0).Object();
  if( 0 == object )
    return failure;

  CRhinoGetPoint gp;
  gp.SetCommandPrompt( L"Pick point" );
  gp.GetPoint();
  if( gp.CommandResult() != success )
    return gp.CommandResult();

  CRhinoGetString gs;
  gp.SetCommandPrompt( L"Description" );
  gs.GetString();
  if( gs.CommandResult() != success )
    return gs.CommandResult();

  bool rc = AddPlugInUserData( context.m_doc, object, gp.Point(), gs.String() );
  RhinoApp().Print( L"%s\n", rc ? L"Succeeded!" : L"Failed!" );

  return success;
}

//
// END PlugIn1Add command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN PlugIn1Get command
//

class CCommandPlugIn1Get : public CRhinoCommand
{
public:
	CCommandPlugIn1Get() {}
	~CCommandPlugIn1Get() {}
	UUID CommandUUID()
	{
		// {A4B430BF-A839-4AB9-B373-64AAD76E9749}
		static const GUID PlugIn1GetCommand_UUID =
		{ 0xA4B430BF, 0xA839, 0x4AB9, { 0xB3, 0x73, 0x64, 0xAA, 0xD7, 0x6E, 0x97, 0x49 } };
		return PlugIn1GetCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"PlugIn1Get"; }
	const wchar_t* LocalCommandName() { return L"PlugIn1Get"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandPlugIn1Get object
static class CCommandPlugIn1Get thePlugIn1GetCommand;

CRhinoCommand::result CCommandPlugIn1Get::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select object" );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != success )
    return go.CommandResult();

  const CRhinoObject* object = go.Object(0).Object();
  if( 0 == object )
    return failure;

  ON_3dPoint point;
  ON_wString string;
  bool rc = GetPlugInUserData( object, point, string );
  if( rc )
  {
    ON_wString pointstr;
    RhinoFormatPoint( point, pointstr );
    RhinoApp().Print( L"point = %s, string = %s\n", pointstr, string );
  }
  else
  {
    RhinoApp().Print( L"Failed!\n" );
  }

  return success;
}

//
// END PlugIn1Get command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN PlugIn1Remove command
//

class CCommandPlugIn1Remove : public CRhinoCommand
{
public:
	CCommandPlugIn1Remove() {}
	~CCommandPlugIn1Remove() {}
	UUID CommandUUID()
	{
		// {CC97E00F-DA64-4220-850A-C91361EA6225}
		static const GUID PlugIn1RemoveCommand_UUID =
		{ 0xCC97E00F, 0xDA64, 0x4220, { 0x85, 0x0A, 0xC9, 0x13, 0x61, 0xEA, 0x62, 0x25 } };
		return PlugIn1RemoveCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"PlugIn1Remove"; }
	const wchar_t* LocalCommandName() { return L"PlugIn1Remove"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandPlugIn1Remove object
static class CCommandPlugIn1Remove thePlugIn1RemoveCommand;

CRhinoCommand::result CCommandPlugIn1Remove::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select object" );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != success )
    return go.CommandResult();

  const CRhinoObject* object = go.Object(0).Object();
  if( 0 == object )
    return failure;

  bool rc = RemovePlugInUserData( context.m_doc, object );
  RhinoApp().Print( L"%s\n", rc ? L"Succeeded!" : L"Failed!" );

  return success;
}

//
// END PlugIn1Remove command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
