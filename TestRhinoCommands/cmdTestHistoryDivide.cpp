#include "StdAfx.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestHistoryDivide command
//

class CTestHistoryDivide : public CRhinoCommand
{
public:
	CTestHistoryDivide() {}
	~CTestHistoryDivide() {}
	UUID CommandUUID()
	{

		// {8B00BE25-2B8B-4a8f-95C1-75A33BF9512A}
		static const GUID TestHistoryDivideCommand_UUID = 
		{ 0x8b00be25, 0x2b8b, 0x4a8f, { 0x95, 0xc1, 0x75, 0xa3, 0x3b, 0xf9, 0x51, 0x2a } };
		return TestHistoryDivideCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TestHistoryDivide"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

	 /*Description:
    Rhino calls the virtual ReplayHistory functions to
    to remake an objects when inputs have changed.  
    If a command supports history, it must override exactly
    one of the ReplayHistory functions. 
    */
  bool ReplayHistory(	const class CRhinoHistoryRecord& history_record,
																ON_SimpleArray<CRhinoObjectPair>& results);

  // Write a history record referencing the antecedent objects
  // The history should contain all the information required to reconstruct the input,
  // This may include parameters, options, or settings
  bool WriteHistory(	CRhinoHistory& history, 
											CRhinoObjRef Crv,
											int num
											);

  // Read a history record and extract the references for the antecedent objects
  bool ReadHistory( const CRhinoHistoryRecord& history_record, 
										CRhinoObjRef& Crv,
										int& num
										);

    // history recording version
    // This field is used to ensure the version of the replay function matches
    // the version that originally created the geometry.
  static const int m_archcutdivide_history_version;
};

// The one and only CTestHistoryDivide object
static class CTestHistoryDivide theDivideCommand;
const int CTestHistoryDivide::m_archcutdivide_history_version(20070228); 



bool 
CTestHistoryDivide::WriteHistory( CRhinoHistory& history, 
                  CRhinoObjRef Crv,
									int num )
{
  if ( !history.SetObjRefValue(0,Crv) )
    return false;
	if ( !history.SetIntValue(2, num) )
		return false;

  history.SetHistoryVersion(m_archcutdivide_history_version);
  return true;
}

bool 
CTestHistoryDivide::ReadHistory( const CRhinoHistoryRecord& history_record, 
                  CRhinoObjRef& Crv,
									int& num )
{
  // Check to make sure this history record was made with this version
  if ( m_archcutdivide_history_version != history_record.HistoryVersion() )
    return false;
  
  if ( !history_record.GetRhinoObjRef(0, Crv) )
    return false;
	if ( !history_record.m_hr.GetIntValue(2, &num) )
		return false;

  return true;
}

bool CTestHistoryDivide::ReplayHistory( const class CRhinoHistoryRecord& history_record,
																		ON_SimpleArray<CRhinoObjectPair>& results)
{
  bool result = false;
  CRhinoObjRef Crv;
	int num = 0;

  if(ReadHistory( history_record, Crv, num))
  {
    if( Crv.Curve() )
    {
			ON_SimpleArray<ON_3dPoint> pts;
			pts.SetCount(0);
			result = RhinoDivideCurve( *Crv.Curve(), num, 0, false, true, &pts, NULL );
			if( !result )
				return false;

			for( int i = 0; i < pts.Count(); i++ )
			{
				CRhinoPointObject* PObj = new CRhinoPointObject();
				PObj->SetPoint( pts[i] );

				if( results.Count() > i )
				{
					results[i].m_object[1] = PObj;
				}
				else
				{
					CRhinoObjectPair& op = results.AppendNew();
					op.m_object[0] = NULL;
					op.m_object[1] = PObj;
				}
			}
    }
  }
  return true;
}

CRhinoCommand::result CTestHistoryDivide::RunCommand( const CRhinoCommandContext& context )
{
	static int num = 10;

	CRhinoGetObject go;
	for(;;)
	{
		go.SetCommandPrompt( L"Select curves to divide" );
		go.SetGeometryFilter( ON::curve_object );
		go.AddCommandOptionInteger( RHCMDOPTNAME( L"Num"), &num );
		
		go.GetObjects(1,1);

		if( go.CommandResult() != CRhinoCommand::success )
			return go.CommandResult();

		if( go.Result() == CRhinoGet::option )
			continue;

		break;
	}

	CRhinoObjRef CObj = go.Object(0);
	const ON_Curve* crv = CObj.Curve();
	if( !crv )
		return failure;

	ON_SimpleArray<ON_3dPoint> crv_pts;
	crv_pts.SetCount(0);

	if( !RhinoDivideCurve( *crv, num, 0, false, true, &crv_pts, NULL ) )
		return failure;

	//ADD POINTS TO CONTEXT
  CRhinoHistory history(*this);
  WriteHistory( history, CObj, num );

	for( int j = 0; j < crv_pts.Count(); j++ )
	{
		CRhinoPointObject* obj = context.m_doc.AddPointObject( crv_pts[j], NULL, &history );
	}

	return CRhinoCommand::success;
}

//
// END TestHistoryDivide command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
