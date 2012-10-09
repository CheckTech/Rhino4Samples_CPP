/////////////////////////////////////////////////////////////////////////////
// cmdPlugInData.cpp

#include "StdAfx.h"
#include "TestObjectUserDataPlugIn.h"
#include "PlugInUserData.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN PlugInDataAdd command
//

class CCommandPlugInDataAdd : public CRhinoCommand
{
public:
	CCommandPlugInDataAdd() {}
	~CCommandPlugInDataAdd() {}
	UUID CommandUUID()
	{
		// {9FF2AEC5-E5EF-4A45-83C4-5DD83E8BCC15}
		static const GUID PlugInDataAddCommand_UUID =
		{ 0x9FF2AEC5, 0xE5EF, 0x4A45, { 0x83, 0xC4, 0x5D, 0xD8, 0x3E, 0x8B, 0xCC, 0x15 } };
		return PlugInDataAddCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"PlugInDataAdd"; }
	const wchar_t* LocalCommandName() { return L"PlugInDataAdd"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandPlugInDataAdd object
static class CCommandPlugInDataAdd thePlugInDataAddCommand;

CRhinoCommand::result CCommandPlugInDataAdd::RunCommand( const CRhinoCommandContext& context )
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

  bool rc = CPlugInUserData::AddPlugInUserData( context.m_doc, object, gp.Point(), gs.String() );
  RhinoApp().Print( L"%s\n", rc ? L"Succeeded!" : L"Failed!" );

  return success;
}

//
// END PlugInDataAdd command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN PlugInDataGet command
//

class CCommandPlugInDataGet : public CRhinoCommand
{
public:
	CCommandPlugInDataGet() {}
	~CCommandPlugInDataGet() {}
	UUID CommandUUID()
	{
		// {A4B430BF-A839-4AB9-B373-64AAD76E9749}
		static const GUID PlugInDataGetCommand_UUID =
		{ 0xA4B430BF, 0xA839, 0x4AB9, { 0xB3, 0x73, 0x64, 0xAA, 0xD7, 0x6E, 0x97, 0x49 } };
		return PlugInDataGetCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"PlugInDataGet"; }
	const wchar_t* LocalCommandName() { return L"PlugInDataGet"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandPlugInDataGet object
static class CCommandPlugInDataGet thePlugInDataGetCommand;

CRhinoCommand::result CCommandPlugInDataGet::RunCommand( const CRhinoCommandContext& context )
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
  bool rc = CPlugInUserData::GetPlugInUserData( object, point, string );
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
// END PlugInDataGet command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN PlugInDataRemove command
//

class CCommandPlugInDataRemove : public CRhinoCommand
{
public:
	CCommandPlugInDataRemove() {}
	~CCommandPlugInDataRemove() {}
	UUID CommandUUID()
	{
		// {CC97E00F-DA64-4220-850A-C91361EA6225}
		static const GUID PlugInDataRemoveCommand_UUID =
		{ 0xCC97E00F, 0xDA64, 0x4220, { 0x85, 0x0A, 0xC9, 0x13, 0x61, 0xEA, 0x62, 0x25 } };
		return PlugInDataRemoveCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"PlugInDataRemove"; }
	const wchar_t* LocalCommandName() { return L"PlugInDataRemove"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandPlugInDataRemove object
static class CCommandPlugInDataRemove thePlugInDataRemoveCommand;

CRhinoCommand::result CCommandPlugInDataRemove::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select object" );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != success )
    return go.CommandResult();

  const CRhinoObject* object = go.Object(0).Object();
  if( 0 == object )
    return failure;

  bool rc = CPlugInUserData::RemovePlugInUserData( context.m_doc, object );
  RhinoApp().Print( L"%s\n", rc ? L"Succeeded!" : L"Failed!" );

  return success;
}

//
// END PlugInDataRemove command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
