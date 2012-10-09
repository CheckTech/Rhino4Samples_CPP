/////////////////////////////////////////////////////////////////////////////
// cmdGripMover.cpp

#include "StdAfx.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN GripMover command
//
class CCommandGripMover : public CRhinoCommand
{
public:
	CCommandGripMover() { m_bUp = true; }
	~CCommandGripMover() {}
	UUID CommandUUID()
	{
		// {5D44340E-50F1-4BBD-BC5A-FF9A8959A0BC}
		static const GUID GripMoverCommand_UUID =
		{ 0x5D44340E, 0x50F1, 0x4BBD, { 0xBC, 0x5A, 0xFF, 0x9A, 0x89, 0x59, 0xA0, 0xBC } };
		return GripMoverCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"GripMover"; }
	const wchar_t* LocalCommandName() { return L"GripMover"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

private:
  bool m_bUp;
};

// The one and only CCommandGripMover object
static class CCommandGripMover theGripMoverCommand;

static int CompareRhinoObjectPtr(CRhinoObject* const* a, CRhinoObject* const* b)
{
  unsigned int sna = (a && *a) ? (*a)->m_runtime_object_serial_number : 0;
  unsigned int snb = (b && *b) ? (*b)->m_runtime_object_serial_number : 0;
	if( sna < snb ) 
    return -1;
	if( snb < sna ) 
    return  1;
	return 0;
}

CRhinoCommand::result CCommandGripMover::RunCommand( const CRhinoCommandContext& context )
{
	CRhinoXformObjectList xform_list;

  CRhinoObjectIterator it( CRhinoObjectIterator::normal_objects, CRhinoObjectIterator::active_objects );
	it.EnableSelectedFilter();
	it.IncludeGrips();

  CRhinoObject* obj = 0;
	for( obj = it.First(); obj; obj = it.Next() )
	{
		CRhinoGripObject* grip_obj = CRhinoGripObject::Cast( obj );
		if( grip_obj )
  		xform_list.AddObject( grip_obj );
	}

	if( 0 == xform_list.m_grips.Count() )
	{
		RhinoApp().Print( L"No grips selected.\n" );
		return CRhinoCommand::nothing;
	}

  xform_list.m_grip_owners.HeapSort( CompareRhinoObjectPtr );

  ON_3dVector v( 0.0, 0, m_bUp ? 5.0 : -5.0 );
	m_bUp = !m_bUp;

  int i;
  for( i = 0; i < xform_list.m_grips.Count(); i++ )
    xform_list.m_grips[i]->MoveGrip( v );

  for( i = 0; i < xform_list.m_grip_owners.Count(); i++ )
    RhinoUpdateGripOwner( xform_list.m_grip_owners[i], false, 0 );

	context.m_doc.Redraw();

	return CRhinoCommand::success;
}

//
// END GripMover command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
