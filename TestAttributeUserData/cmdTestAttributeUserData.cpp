/////////////////////////////////////////////////////////////////////////////
// cmdTestAttributeUserData.cpp

#include "StdAfx.h"
#include "TestAttributeUserDataPlugIn.h"
#include "TestUserData.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestAttachData command
//

class CCommandTestAttachData : public CRhinoCommand
{
public:
	CCommandTestAttachData() {}
	~CCommandTestAttachData() {}
	UUID CommandUUID()
	{
		// {65A1D235-6404-41B5-B561-9038B1F6363C}
		static const GUID TestAttachDataCommand_UUID =
		{ 0x65A1D235, 0x6404, 0x41B5, { 0xB5, 0x61, 0x90, 0x38, 0xB1, 0xF6, 0x36, 0x3C } };
		return TestAttachDataCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestAttachData"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestAttachData object
static class CCommandTestAttachData theTestAttachDataCommand;

CRhinoCommand::result CCommandTestAttachData::RunCommand( const CRhinoCommandContext& context )
{
  // Select object to attach user data
	CRhinoGetObject go;
  go.SetCommandPrompt( L"Select object to attach user data" );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != success )
    return go.CommandResult();

  // Validate the selection
  const CRhinoObjRef& ref = go.Object(0);
  const CRhinoObject* obj = ref.Object();
  if( !obj )
    return failure;

  // Get the selected object's attributes
  const CRhinoObjectAttributes& attribs = obj->Attributes();

  // See if our user data is already attached
  CTestUserData* ud = CTestUserData::Cast( attribs.GetUserData(ud->Id()) );
  if( ud )
  {
    RhinoApp().Print( L"User data already attached.\n" );
    return nothing;
  }

  // New up a copy of our user data and fill in the data members
  ud = new CTestUserData();
  ud->m_my_string = obj->ShortDescription( false );
  ref.SelectionPoint( ud->m_my_point );

  // Make a copy of the object's attributes
  ON_3dmObjectAttributes new_attribs( attribs );
  // Attach our user data to this copy
  new_attribs.AttachUserData( ud );

  // Replace the selected object's attributes
  context.m_doc.ModifyObjectAttributes( ref, new_attribs );

	return success;
}

//
// END TestAttachData command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestRetrieveData command
//

class CCommandTestRetrieveData : public CRhinoCommand
{
public:
	CCommandTestRetrieveData() {}
	~CCommandTestRetrieveData() {}
	UUID CommandUUID()
	{
		// {454332B9-9788-4034-8C94-D22718B63E0F}
		static const GUID TestRetrieveDataCommand_UUID =
		{ 0x454332B9, 0x9788, 0x4034, { 0x8C, 0x94, 0xD2, 0x27, 0x18, 0xB6, 0x3E, 0x0F } };
		return TestRetrieveDataCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestRetrieveData"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestRetrieveData object
static class CCommandTestRetrieveData theTestRetrieveDataCommand;

CRhinoCommand::result CCommandTestRetrieveData::RunCommand( const CRhinoCommandContext& context )
{
  // Select object to retrieve user data
	CRhinoGetObject go;
  go.SetCommandPrompt( L"Select object to retrieve user data" );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != success )
    return go.CommandResult();

  // Validate the selection
  const CRhinoObjRef& ref = go.Object(0);
  const CRhinoObject* obj = ref.Object();
  if( !obj )
    return failure;

  // Get the selected object's attributes
  const CRhinoObjectAttributes& attribs = obj->Attributes();

  // See if our user data is attached
  CTestUserData* ud = CTestUserData::Cast( attribs.GetUserData(ud->Id()) );
  if( ud )
  {
    // Print data members
    RhinoApp().Print( L"String = %s\n", ud->m_my_string );
    RhinoApp().Print( L"Point = %f,%f,%f\n", ud->m_my_point.x, ud->m_my_point.y, ud->m_my_point.z );
  }
  else
  {
    RhinoApp().Print( L"No user data attached.\n" );
  }

  return success;
}

//
// END TestRetrieveData command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
