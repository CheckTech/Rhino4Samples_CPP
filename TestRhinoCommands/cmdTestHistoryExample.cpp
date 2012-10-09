#include "StdAfx.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN HistoryExample command
//
//  This command shows how to use the History mechanism in Rhino.
//  The command makes a simple surface from a pair of input curves.
//  A history record is added to the document together with the object.
//  The record refers to the curves which are called the antecedent objects.
//  The ReplayHistory function reads the history record and constructs the 
//  updated surface from the updated curves. 

class CCommandTestHistoryExample : public CRhinoCommand
{
public:

	CCommandTestHistoryExample() {}
  ~CCommandTestHistoryExample() {}

	UUID CommandUUID()
	{
		// {D7BA354E-B9B5-4F08-B3D1-DF38329BE353}
    static const GUID TestHistoryExampleCommand_UUID =
    { 0xD7BA354E, 0xB9B5, 0x4F08, { 0xB3, 0xD1, 0xDF, 0x38, 0x32, 0x9B, 0xE3, 0x53 } };
    return TestHistoryExampleCommand_UUID;
	}

  // Returns the English command name.
	const wchar_t* EnglishCommandName() { return L"TestHistoryExample"; }

  // Returns the localized command name.
	const wchar_t* LocalCommandName() { return L"TestHistoryExample"; }

  // returns the resulting surface from the imput curves
  ON_Surface* MakeBilinearSurface(const ON_Curve& C0, const ON_Curve& C1);

  // Rhino calls RunCommand to run the command.
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );

 /*Description:
    Rhino calls the virtual ReplayHistory functions to
    to remake an objects when inputs have changed.  
    If a command supports history, it must override exactly
    one of the ReplayHistory functions. 
    */
  CRhinoObject* ReplayHistory( const class CRhinoHistoryRecord& history_record );

  // Write a history record referencing the antecedent objects
  // The history should contain all the information required to reconstruct the input,
  // This may include parameters, options, or settings
  bool WriteHistory( CRhinoHistory& history, 
                  CRhinoObjRef Crv0 ,
                  CRhinoObjRef Crv1
                  );

  // Read a history record and extract the references for the antecedent objects
  bool ReadHistory( const CRhinoHistoryRecord& history_record, 
                  CRhinoObjRef& Crv0 ,
                  CRhinoObjRef& Crv1
                  );

    // history recording version
    // This field is used to ensure the version of the replay function matches
    // the version that originally created the geometry.
  static const int m_historyexample_history_version;
};


static class CCommandTestHistoryExample theTestHistoryExampleCommand;
const int CCommandTestHistoryExample::m_historyexample_history_version(20070227);  

bool 
CCommandTestHistoryExample::WriteHistory( CRhinoHistory& history, 
                  CRhinoObjRef Crv0 ,
                  CRhinoObjRef Crv1 )
{
  if ( !history.SetObjRefValue(0,Crv0) )
    return false;
  if ( !history.SetObjRefValue(1,Crv1) )
    return false;

  history.SetHistoryVersion(m_historyexample_history_version);
  return true;
}

bool 
CCommandTestHistoryExample::ReadHistory( const CRhinoHistoryRecord& history_record, 
                  CRhinoObjRef& Crv0 ,
                  CRhinoObjRef& Crv1 )
{
  // Check to make sure this history record was made with this version
  if ( m_historyexample_history_version != history_record.HistoryVersion() )
    return false;
  
  if ( !history_record.GetRhinoObjRef(0, Crv0) )
    return false;
  if ( !history_record.GetRhinoObjRef(1, Crv1) )
    return false;

  return true;
}

CRhinoObject* CCommandTestHistoryExample::ReplayHistory( const class CRhinoHistoryRecord& history_record )
{
  CRhinoSurfaceObject* result = NULL;
  CRhinoObjRef Crv0, Crv1;
  if(ReadHistory(history_record, Crv0, Crv1))
  {
    if(Crv0.Curve() && Crv1.Curve() )
    {
      ON_Surface* pSrf = MakeBilinearSurface(*Crv0.Curve(), *Crv1.Curve());
      if( pSrf)
      {
        result = new CRhinoSurfaceObject();
        result->SetSurface(pSrf);
      }
    }
  }
  return result;
}

ON_Surface* 
CCommandTestHistoryExample::MakeBilinearSurface(const ON_Curve& C0, const ON_Curve& C1)
{
  ON_BezierSurface Srf(3, false, 2, 2);
  Srf.SetCV(0,0, C0.PointAtStart());
  Srf.SetCV(0,1, C0.PointAtEnd());
  Srf.SetCV(1,0, C1.PointAtStart());
  Srf.SetCV(1,1, C1.PointAtEnd());

  ON_NurbsSurface* pSrf = new ON_NurbsSurface(Srf);
  return pSrf;
}

CRhinoCommand::result CCommandTestHistoryExample::RunCommand( const CRhinoCommandContext& context )
{
  CRhinoCommand::result rc  = CRhinoCommand::failure; 

  CRhinoGetObject go;
  go.SetCommandPrompt(L"Pick two curves");
  go.SetGeometryFilter(CRhinoGetObject::curve_object);
  go.GetObjects(2,2);
  if( go.Result()== CRhinoGet::object && 
      go.ObjectCount()==2)
  {
    CRhinoObjRef CObj0 = go.Object(0);
    CRhinoObjRef CObj1 = go.Object(1);
    const ON_Curve* c0 = CObj0.Curve();
    const ON_Curve* c1 = CObj1.Curve();
    if( c0 && c1)
    {
      ON_Surface* pSrf = MakeBilinearSurface( *c0, *c1);
      ON_Brep brep;
      if(pSrf && brep.Create(pSrf))
      {
        CRhinoHistory history(*this);
        WriteHistory(history,  CObj0, CObj1);
        context.m_doc.AddBrepObject(brep,NULL,&history);
        rc  = CRhinoCommand::success; 
      }
    }

  }

  return rc;
}

//
// END TestHistoryExample command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
