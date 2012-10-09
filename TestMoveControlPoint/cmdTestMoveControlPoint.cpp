#include "StdAfx.h"
#include "TestMoveControlPointDialog.h"
#include "RhinoObjectList.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestMoveControlPoint command
//

class CCommandTestMoveControlPoint : public CRhinoCommand
{
public:
	CCommandTestMoveControlPoint() {}
  ~CCommandTestMoveControlPoint() {}
	UUID CommandUUID()
	{
		// {98159686-5604-4760-B835-5DFBDB9C511E}
    static const GUID TestMoveControlPointCommand_UUID =
    { 0x98159686, 0x5604, 0x4760, { 0xB8, 0x35, 0x5D, 0xFB, 0xDB, 0x9C, 0x51, 0x1E } };
    return TestMoveControlPointCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestMoveControlPoint"; }
	const wchar_t* LocalCommandName() { return L"TestMoveControlPoint"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};
static class CCommandTestMoveControlPoint theTestMoveControlPointCommand;

CRhinoCommand::result CCommandTestMoveControlPoint::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select control point to move" );
  go.EnablePreSelect( TRUE );
  go.EnableSubObjectSelect( FALSE );
  go.SetGeometryFilter( CRhinoGetObject::grip_object );
  go.EnableIgnoreGrips( false );
  go.GetObjects( 1, 1 );
  if( go.CommandResult() != CRhinoCommand::success )
    return go.CommandResult();

  const CRhinoGripObject* grip = CRhinoGripObject::Cast( go.Object(0).Object() );
  if( 0 == grip )
    return CRhinoCommand::failure;

  ON_3dPoint point = grip->Point();
 
  CRhinoObjectList list;
  if( list.AddObjects(go) < 1 )
    return CRhinoCommand::failure;

  CWnd* pParent = CWnd::FromHandle( RhinoApp().MainWnd() );
  CTestMoveControlPointDialog dialog( context.m_doc, pParent );
  dialog.AppendObjects( list );
  dialog.SetPoint( point );

  INT_PTR rc = dialog.DoModal();
  if( rc == IDCANCEL || 0 == dialog.m_distance )
  {
    list.ResetGrips();
    context.m_doc.Redraw();
    return CRhinoCommand::cancel;
  }

  ON_3dPoint new_point = point;
  new_point.z += dialog.m_distance;

  ON_Xform xform(1);
  xform.Translation( new_point - point );

  list.Transform( context.m_doc, xform, false, true );
  context.m_doc.Redraw();

  return CRhinoCommand::success;
}

//
// END TestMoveControlPoint command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
