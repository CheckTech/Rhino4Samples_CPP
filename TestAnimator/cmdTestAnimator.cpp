/////////////////////////////////////////////////////////////////////////////
// cmdTestAnimator.cpp

#include "StdAfx.h"
#include "TestAnimatorDlg.h"

class CCommandTestAnimator : public CRhinoCommand
{
public:
  CCommandTestAnimator() { m_max_steps = 100; }
  ~CCommandTestAnimator() {}

	UUID CommandUUID()
	{
		// {4815256C-E758-4AA8-8AD5-2DD350924748}
		static const GUID TestAnimatorCommand_UUID =
    { 0x4815256C, 0xE758, 0x4AA8, { 0x8A, 0xD5, 0x2D, 0xD3, 0x50, 0x92, 0x47, 0x48 } };
		return TestAnimatorCommand_UUID;
	}

	const wchar_t* EnglishCommandName() { return L"TestAnimator"; }
	const wchar_t* LocalCommandName() const { return L"TestAnimator"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

private:
  int m_max_steps;
};

// The one and only CCommandTestAnimator object
static class CCommandTestAnimator theTestAnimatorCommand;

CRhinoCommand::result CCommandTestAnimator::RunCommand( const CRhinoCommandContext& context )
{
  // Select objects to animate
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select objects to animate" );
  go.GetObjects( 1, 0 );
  if( go.CommandResult() != success )
    return go.CommandResult();

  // Select path curve
  CRhinoGetObject gc;
  gc.SetCommandPrompt( L"Select path curve" );
  gc.SetGeometryFilter( CRhinoGetObject::curve_object );
  gc.SetGeometryAttributeFilter( CRhinoGetObject::open_curve );
  gc.GetObjects( 1, 1 );
  if( gc.CommandResult() != success )
    return gc.CommandResult();

  const ON_Curve* crv = gc.Object(0).Curve();
  if( 0 == crv )
    return failure;

  // Create an array of normalized curve parameters
  ON_SimpleArray<double> t_array( m_max_steps );
  t_array.SetCount( m_max_steps );
  int i = 0;
  for( i = 0; i < m_max_steps; i++ )
  {
    double t = (double)i / ( (double)m_max_steps - 1 );
    t_array[i] = t;
  }

  // Get the real parameters along the curve
  if( !crv->GetNormalizedArcLengthPoints(m_max_steps, t_array.Array(), t_array.Array()) ) 
    return failure;

  // Create our dialog box with animatin slider...
  CTestAnimatorDlg dlg( CWnd::FromHandle(RhinoApp().MainWnd()) );
  dlg.m_max_steps = m_max_steps;
  dlg.m_start = crv->PointAtStart();

  // Get points along curve
  for( i = 0; i < m_max_steps; i++ )
  {
    ON_3dPoint pt = crv->PointAt( t_array[i] );
    dlg.m_points.Append( pt );
  }

  // Hide objects and add them to callback's object array
  for( i = 0; i < go.ObjectCount(); i++ )
  {
    CRhinoObjRef ref = go.Object(i);
    context.m_doc.HideObject( ref );
    dlg.m_conduit.m_objects.Append( ref.Object() );
  }

  // Do the dialog
  INT_PTR rc = dlg.DoModal();

  // If OK was pressed, transform the objects.
  // Otherwise, just unhide them.
  for( i = 0; i < go.ObjectCount(); i++ )
  {
    CRhinoObjRef ref = go.Object(i);
    context.m_doc.ShowObject( ref );
    if( rc == IDOK )
    {
      ON_Xform xform = dlg.m_conduit.m_xform;
      context.m_doc.TransformObject( ref, xform );
    }
  }

  context.m_doc.Redraw( CRhinoView::regenerate_display_hint );

  return CRhinoCommand::success;
}
