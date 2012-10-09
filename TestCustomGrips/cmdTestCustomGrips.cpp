/////////////////////////////////////////////////////////////////////////////
// cmdTestCustomGrips.cpp : command file
//

#include "StdAfx.h"
#include "TestCustomGripsPlugIn.h"
#include "RhinoRectangleObject.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestCustomGrips command
//

class CCommandTestCustomGrips : public CRhinoCommand
{
public:
	CCommandTestCustomGrips() {}
	~CCommandTestCustomGrips() {}
	UUID CommandUUID()
	{
		// {5E1AF233-2165-476A-9A58-311ADD7065AA}
		static const GUID TestCustomGripsCommand_UUID =
		{ 0x5E1AF233, 0x2165, 0x476A, { 0x9A, 0x58, 0x31, 0x1A, 0xDD, 0x70, 0x65, 0xAA } };
		return TestCustomGripsCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestCustomGrips"; }
	const wchar_t* LocalCommandName() { return L"TestCustomGrips"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTestCustomGrips object
static class CCommandTestCustomGrips theTestCustomGripsCommand;

CRhinoCommand::result CCommandTestCustomGrips::RunCommand( const CRhinoCommandContext& context )
{
  ON_3dPoint rect[5];
  
  CArgsRhinoGetPlane args;
  args.SetCornerMode( CArgsRhinoGetPlane::mode_corners );
  args.SetAllowRounded( FALSE );
  args.SetAllowDeformable( FALSE );
 
  CRhinoCommand::result rc = RhinoGetRectangle( args, rect );
  
  if( rc == CRhinoCommand::success)
  {
    ON_Polyline pline;
    rect[4] = rect[0];
    pline.Create( 3, FALSE, 5, 3, (double*)&rect );

    ON_PolylineCurve* pline_curve = new ON_PolylineCurve( pline );
    
    CRhinoRectangleObject* rect_object = new CRhinoRectangleObject();
    rect_object->SetCurve( pline_curve );

    if( context.m_doc.AddObject(rect_object) )
      context.m_doc.Redraw();
    else
      delete rect_object;
  }

  return CRhinoCommand::success;
}

//
// END TestGrips command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
