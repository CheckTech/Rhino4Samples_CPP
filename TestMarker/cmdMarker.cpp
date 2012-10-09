/////////////////////////////////////////////////////////////////////////////
// cmdMarker.cpp : command file
//

#include "StdAfx.h"
#include "RhinoMarkerObject.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN Marker command
//

class CCommandMarker : public CRhinoCommand
{
public:
	CCommandMarker() {}
	~CCommandMarker() {}
	UUID CommandUUID()
	{
		// {3670DAFF-FD0E-439F-B977-04A53010046B}
		static const GUID MarkerCommand_UUID =
		{ 0x3670DAFF, 0xFD0E, 0x439F, { 0xB9, 0x77, 0x04, 0xA5, 0x30, 0x10, 0x04, 0x6B } };
		return MarkerCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"Marker"; }
	const wchar_t* LocalCommandName() { return L"Marker"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandMarker object
static class CCommandMarker theMarkerCommand;

CRhinoCommand::result CCommandMarker::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetPoint gp;
  gp.SetCommandPrompt( L"Location of marker object" );
  gp.GetPoint();
  if( gp.CommandResult() != success )
    return gp.CommandResult();

  CRhinoMarkerObject* marker = new CRhinoMarkerObject();
  marker->SetPoint( gp.Point() );

  context.m_doc.AddObject( marker );
  context.m_doc.Redraw();

  return success;
}

//
// END Marker command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN Markers command
//

class CCommandMarkers : public CRhinoCommand
{
public:
	CCommandMarkers() {}
	~CCommandMarkers() {}
	UUID CommandUUID()
	{
		// {830B90F3-1652-419F-BE09-081531782DC9}
		static const GUID MarkersCommand_UUID =
		{ 0x830B90F3, 0x1652, 0x419F, { 0xBE, 0x09, 0x08, 0x15, 0x31, 0x78, 0x2D, 0xC9 } };
		return MarkersCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"Markers"; }
	const wchar_t* LocalCommandName() { return L"Markers"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandMarkers object
static class CCommandMarkers theMarkersCommand;

CRhinoCommand::result CCommandMarkers::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetPoint gp;
  gp.SetCommandPrompt( L"Location of marker object" );
  gp.AcceptNothing();
  for(;;)
  {
    CRhinoGet::result res = gp.GetPoint();

    if( res == CRhinoGet::cancel )
      return cancel;

    if( res == CRhinoGet::nothing )
      break;

    CRhinoMarkerObject* marker = new CRhinoMarkerObject();
    marker->SetPoint( gp.Point() );

    context.m_doc.AddObject( marker );
    context.m_doc.Redraw();
  }

  return success;
}

//
// END Markers command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
