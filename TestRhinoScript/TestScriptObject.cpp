/////////////////////////////////////////////////////////////////////////////
// TestScriptObject.cpp
//

#include "StdAfx.h"
#include "TestScriptPlugIn.h"
#include "TestScriptObject.h"
#include "VariantUtilities.h"
#include "TestAboutDialog.h"

IMPLEMENT_DYNAMIC(CTestScriptObject, CCmdTarget)

CTestScriptObject::CTestScriptObject()
{
	EnableAutomation();
}

CTestScriptObject::~CTestScriptObject()
{
}

void CTestScriptObject::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CTestScriptObject, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTestScriptObject, CCmdTarget)
  DISP_FUNCTION_ID(CTestScriptObject, "About", dispidAbout, About, VT_EMPTY, VTS_NONE)
  DISP_FUNCTION_ID(CTestScriptObject, "Multiply", dispidMultiply, Multiply, VT_R8, VTS_R8 VTS_R8)
  DISP_FUNCTION_ID(CTestScriptObject, "AddPoint", dispidAddPoint, AddPoint, VT_VARIANT, VTS_PVARIANT)
  DISP_FUNCTION_ID(CTestScriptObject, "AddPointCloud", dispidAddPointCloud, AddPointCloud, VT_VARIANT, VTS_PVARIANT)
  DISP_FUNCTION_ID(CTestScriptObject, "TestByReference", dispidTestByReference, TestByReference, VT_VARIANT, VTS_PVARIANT)
END_DISPATCH_MAP()

// Note: we add support for IID_ITestScriptObject to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {0C171EB5-71BE-4E8B-AD17-FAE2405AB502}
static const IID IID_ITestScriptObject =
{ 0xC171EB5, 0x71BE, 0x4E8B, { 0xAD, 0x17, 0xFA, 0xE2, 0x40, 0x5A, 0xB5, 0x2 } };

BEGIN_INTERFACE_MAP(CTestScriptObject, CCmdTarget)
	INTERFACE_PART(CTestScriptObject, IID_ITestScriptObject, Dispatch)
END_INTERFACE_MAP()

// CTestScriptObject message handlers

void CTestScriptObject::About(void)
{
  AFX_MANAGE_STATE( AfxGetStaticModuleState() );
  CTestAboutDialog dialog( CWnd::FromHandle(RhinoApp().MainWnd()) );
  dialog.DoModal();
}

DOUBLE CTestScriptObject::Multiply(DOUBLE a, DOUBLE b)
{
  return a*b;
}

VARIANT CTestScriptObject::AddPoint(VARIANT* vaPoint)
{
  VARIANT vaResult;
  VariantInit(&vaResult);
  V_VT(&vaResult) = VT_NULL;
	
  if( vaPoint )
  {
	  ON_3dPoint pt;
    if( VariantToPoint(*vaPoint, pt) )
    {
      CRhinoDoc* doc = RhinoApp().ActiveDoc();
      if( doc )
      {
        CRhinoPointObject* obj = doc->AddPointObject( pt );
        if( obj )
        {
          doc->Redraw();
          ON_wString wstr;
          ON_UuidToString( obj->Attributes().m_uuid, wstr );
          CString str(wstr);
          V_VT(&vaResult) = VT_BSTR;
          vaResult.bstrVal = str.AllocSysString();
        }
      }
    }
  }

  return vaResult;
}

VARIANT CTestScriptObject::AddPointCloud(VARIANT* vaPointCloud)
{
	VARIANT vaResult;
	VariantInit(&vaResult);
  V_VT(&vaResult) = VT_NULL;
	
  if( vaPointCloud )
  {
	  ON_3dPointArray point_cloud; 
    if( VariantToPointArray(*vaPointCloud, point_cloud) )
    {
      CRhinoDoc* doc = RhinoApp().ActiveDoc();
      if( doc )
      {
        CRhinoPointCloudObject* obj = doc->AddPointCloudObject( point_cloud.Count(), point_cloud.Array() );
        if( obj )
        {
          doc->Redraw();
          ON_wString wstr;
          ON_UuidToString( obj->Attributes().m_uuid, wstr );
          CString str(wstr);
          V_VT(&vaResult) = VT_BSTR;
          vaResult.bstrVal = str.AllocSysString();
        }
      }
    }
  }

  return vaResult;
}

VARIANT CTestScriptObject::TestByReference(VARIANT* vaValue)
{
	VARIANT vaResult;
	VariantInit(&vaResult);
  V_VT(&vaResult) = VT_NULL;

  if( 0 == vaValue )
    return vaResult;

  bool b = false;
  if( !VariantToBoolean(*vaValue, b) )
    return vaResult;

  VariantClear( vaValue );
  V_VT(vaValue) = VT_BOOL | VT_BYREF;
  *(vaValue->pboolVal) = b ? VARIANT_FALSE : VARIANT_TRUE; // invert

  V_VT(&vaResult) = VT_BOOL;
  vaResult.boolVal = b ? VARIANT_TRUE : VARIANT_FALSE;

  return vaResult;
}
