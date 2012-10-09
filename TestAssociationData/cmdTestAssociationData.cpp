/////////////////////////////////////////////////////////////////////////////
// cmdTestAssociationData.cpp

#include "StdAfx.h"
#include "TestAssociationDataPlugIn.h"
#include "AssociationData.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestAddData command
//

class CCommandTestAddData : public CRhinoCommand
{
public:
	CCommandTestAddData() {}
	~CCommandTestAddData() {}
	UUID CommandUUID()
	{
		// {85E46469-1C32-4B9E-A170-F15E8159DA6F}
		static const GUID TestAddDataCommand_UUID =
		{ 0x85E46469, 0x1C32, 0x4B9E, { 0xA1, 0x70, 0xF1, 0x5E, 0x81, 0x59, 0xDA, 0x6F } };
		return TestAddDataCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestAddData"; }
	const wchar_t* LocalCommandName() { return L"TestAddData"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestAddData object
static class CCommandTestAddData theTestAddDataCommand;

CRhinoCommand::result CCommandTestAddData::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select two objects to associate" );
  go.GetObjects( 2, 2 );
  if( go.CommandResult() != CRhinoCommand::success )
    return go.CommandResult();

  const CRhinoObject* object0 = go.Object(0).Object();
  const CRhinoObject* object1 = go.Object(1).Object();
  if( 0 == object0 || 0 == object1 )
    return CRhinoCommand::failure;

  AssociationData::AddData( context.m_doc, object0, object0->Attributes().m_uuid, object1->Attributes().m_uuid );
  AssociationData::AddData( context.m_doc, object1, object1->Attributes().m_uuid, object0->Attributes().m_uuid );

	return CRhinoCommand::success;
}

//
// END TestAddData command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestGetData command
//

class CCommandTestGetData : public CRhinoCommand
{
public:
	CCommandTestGetData() {}
	~CCommandTestGetData() {}
	UUID CommandUUID()
	{
		// {DCA119F7-60F2-409C-A1B7-445028F7FA47}
		static const GUID TestGetDataCommand_UUID =
		{ 0xDCA119F7, 0x60F2, 0x409C, { 0xA1, 0xB7, 0x44, 0x50, 0x28, 0xF7, 0xFA, 0x47 } };
		return TestGetDataCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestGetData"; }
	const wchar_t* LocalCommandName() { return L"TestGetData"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestGetData object
static class CCommandTestGetData theTestGetDataCommand;

CRhinoCommand::result CCommandTestGetData::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select object" );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != CRhinoCommand::success )
    return go.CommandResult();

  const CRhinoObject* object = go.Object(0).Object();
  if( 0 == object )
    return CRhinoCommand::failure;

  ON_UUID object0_uuid, object1_uuid;
  if( AssociationData::GetData(object, object0_uuid, object1_uuid) )
  {
    ON_wString object0_str, object1_str;
    ON_UuidToString( object0_uuid, object0_str );
    ON_UuidToString( object1_uuid, object1_str );
    RhinoApp().Print( L"Object0 = %s\n", object0_str );
    RhinoApp().Print( L"Object1 = %s\n", object1_str );
  }

	return CRhinoCommand::success;
}

//
// END TestGetData command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestRemoveData command
//

class CCommandTestRemoveData : public CRhinoCommand
{
public:
	CCommandTestRemoveData() {}
	~CCommandTestRemoveData() {}
	UUID CommandUUID()
	{
		// {1ED96C3-A8E3-43BB-870C-A9DBC237E77B}
		static const GUID TestRemoveDataCommand_UUID =
		{ 0x1ED96C3, 0xA8E3, 0x43BB, { 0x87, 0x0C, 0xA9, 0xDB, 0xC2, 0x37, 0xE7, 0x7B } };
		return TestRemoveDataCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestRemoveData"; }
	const wchar_t* LocalCommandName() { return L"TestRemoveData"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestRemoveData object
static class CCommandTestRemoveData theTestRemoveDataCommand;

CRhinoCommand::result CCommandTestRemoveData::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select object" );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != CRhinoCommand::success )
    return go.CommandResult();

  const CRhinoObject* object = go.Object(0).Object();
  if( 0 == object )
    return CRhinoCommand::failure;

  AssociationData::RemoveData( context.m_doc, object );

	return CRhinoCommand::success;
}

//
// END TestRemoveData command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

