/////////////////////////////////////////////////////////////////////////////
// cmdTestPointCloudUserData.cpp

#include "StdAfx.h"
#include "TestPointCloudUserDataPlugIn.h"
#include "PointCloudUserData.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestAdd command
//

class CCommandTestAdd : public CRhinoCommand
{
public:
	CCommandTestAdd() {}
	~CCommandTestAdd() {}
	UUID CommandUUID()
	{
		// {F51F2E21-267E-47A4-B89A-8A179A5F39FC}
		static const GUID TestAddCommand_UUID =
		{ 0xF51F2E21, 0x267E, 0x47A4, { 0xB8, 0x9A, 0x8A, 0x17, 0x9A, 0x5F, 0x39, 0xFC } };
		return TestAddCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestAdd"; }
	const wchar_t* LocalCommandName() { return L"TestAdd"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestAdd object
static class CCommandTestAdd theTestAddCommand;

CRhinoCommand::result CCommandTestAdd::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select point cloud" );
  go.SetGeometryFilter( CRhinoGetObject::pointset_object );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != success )
    return go.CommandResult();

  const CRhinoPointCloudObject* object = CRhinoPointCloudObject::Cast( go.Object(0).Object() );
  if( 0 == object )
    return CRhinoCommand::failure;

  const int point_count = object->PointCloud().PointCount();
  ON_SimpleArray<unsigned short> intensity( point_count );

  int i;
  for( i = 0; i < point_count; i++ )
    intensity.Append( i % 0xffff ); // Make something up...

  bool rc = CPointCloudUserData::AddPointCloudUserData( context.m_doc, object, intensity );
  RhinoApp().Print( L"%s\n", rc ? L"Succeeded!" : L"Failed!" );

  if( rc )
    context.m_doc.Redraw();

	return CRhinoCommand::success;
}

//
// END TestAdd command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestGet command
//

class CCommandTestGet : public CRhinoCommand
{
public:
	CCommandTestGet() {}
	~CCommandTestGet() {}
	UUID CommandUUID()
	{
		// {525F0EDB-8A7E-4705-B6EC-16FB384B1630}
		static const GUID TestGetCommand_UUID =
		{ 0x525F0EDB, 0x8A7E, 0x4705, { 0xB6, 0xEC, 0x16, 0xFB, 0x38, 0x4B, 0x16, 0x30 } };
		return TestGetCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestGet"; }
	const wchar_t* LocalCommandName() { return L"TestGet"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestGet object
static class CCommandTestGet theTestGetCommand;

CRhinoCommand::result CCommandTestGet::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select point cloud" );
  go.SetGeometryFilter( CRhinoGetObject::pointset_object );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != success )
    return go.CommandResult();

  const CRhinoPointCloudObject* object = CRhinoPointCloudObject::Cast( go.Object(0).Object() );
  if( 0 == object )
    return CRhinoCommand::failure;

  ON_SimpleArray<unsigned short> intensity;
  bool rc = CPointCloudUserData::GetPointCloudUserData( object, intensity );
  if( rc )
  {
    int i;
    for( i = 0; i < intensity.Count(); i++ )
      RhinoApp().Print( L"Intensity(i) = %d\n", i, intensity[i] );
  }
  else
  {
    RhinoApp().Print( L"Failed!\n" );
  }

	return CRhinoCommand::success;
}

//
// END TestGet command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestRemove command
//

class CCommandTestRemove : public CRhinoCommand
{
public:
	CCommandTestRemove() {}
	~CCommandTestRemove() {}
	UUID CommandUUID()
	{
		// {FEB9AE72-681F-4580-92A8-158C9DE5E0C9}
		static const GUID TestRemoveCommand_UUID =
		{ 0xFEB9AE72, 0x681F, 0x4580, { 0x92, 0xA8, 0x15, 0x8C, 0x9D, 0xE5, 0xE0, 0xC9 } };
		return TestRemoveCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestRemove"; }
	const wchar_t* LocalCommandName() { return L"TestRemove"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestRemove object
static class CCommandTestRemove theTestRemoveCommand;

CRhinoCommand::result CCommandTestRemove::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select point cloud" );
  go.SetGeometryFilter( CRhinoGetObject::pointset_object );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != success )
    return go.CommandResult();

  const CRhinoPointCloudObject* object = CRhinoPointCloudObject::Cast( go.Object(0).Object() );
  if( 0 == object )
    return CRhinoCommand::failure;

  bool rc = CPointCloudUserData::RemovePointCloudUserData( context.m_doc, object );
  RhinoApp().Print( L"%s\n", rc ? L"Succeeded!" : L"Failed!" );

  if( rc )
    context.m_doc.Redraw();

  return CRhinoCommand::success;
}

//
// END TestRemove command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

