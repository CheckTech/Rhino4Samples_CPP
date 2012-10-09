/////////////////////////////////////////////////////////////////////////////
// cmdPlugIn2.cpp : command file
//

#include "StdAfx.h"
#include "PlugIn2PlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN PlugIn2Add command
//

class CCommandPlugIn2Add : public CRhinoCommand
{
public:
	CCommandPlugIn2Add() {}
	~CCommandPlugIn2Add() {}
	UUID CommandUUID()
	{
    // {1144749A-9409-498C-A597-7693083682FB}
    static const GUID PlugIn2AddCommand_UUID =
    { 0x1144749A, 0x9409, 0x498C, { 0xA5, 0x97, 0x76, 0x93, 0x08, 0x36, 0x82, 0xFB } };
		return PlugIn2AddCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"PlugIn2Add"; }
	const wchar_t* LocalCommandName() { return L"PlugIn2Add"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandPlugIn2Add object
static class CCommandPlugIn2Add thePlugIn2AddCommand;

CRhinoCommand::result CCommandPlugIn2Add::RunCommand( const CRhinoCommandContext& context )
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
// END PlugIn2Add command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN PlugIn2Get command
//

class CCommandPlugIn2Get : public CRhinoCommand
{
public:
	CCommandPlugIn2Get() {}
	~CCommandPlugIn2Get() {}
	UUID CommandUUID()
	{
    // {6388B270-BC82-4AD4-B2D6-6DC021CF9C21}
    static const GUID PlugIn2GetCommand_UUID =
    { 0x6388B270, 0xBC82, 0x4AD4, { 0xB2, 0xD6, 0x6D, 0xC0, 0x21, 0xCF, 0x9C, 0x21 } };
		return PlugIn2GetCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"PlugIn2Get"; }
	const wchar_t* LocalCommandName() { return L"PlugIn2Get"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandPlugIn2Get object
static class CCommandPlugIn2Get thePlugIn2GetCommand;

CRhinoCommand::result CCommandPlugIn2Get::RunCommand( const CRhinoCommandContext& context )
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
// END PlugIn2Get command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN PlugIn2Remove command
//

class CCommandPlugIn2Remove : public CRhinoCommand
{
public:
	CCommandPlugIn2Remove() {}
	~CCommandPlugIn2Remove() {}
	UUID CommandUUID()
	{
    // {680FB74D-FE69-48A9-A5F0-C8A1A7ECC851}
    static const GUID PlugIn2RemoveCommand_UUID =
    { 0x680FB74D, 0xFE69, 0x48A9, { 0xA5, 0xF0, 0xC8, 0xA1, 0xA7, 0xEC, 0xC8, 0x51 } };
		return PlugIn2RemoveCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"PlugIn2Remove"; }
	const wchar_t* LocalCommandName() { return L"PlugIn2Remove"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandPlugIn2Remove object
static class CCommandPlugIn2Remove thePlugIn2RemoveCommand;

CRhinoCommand::result CCommandPlugIn2Remove::RunCommand( const CRhinoCommandContext& context )
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
// END PlugIn2Remove command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
