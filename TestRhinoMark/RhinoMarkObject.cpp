/////////////////////////////////////////////////////////////////////////////
// RhinoMarkObject.cpp

#include "stdafx.h"
#include "RhinoMarkObject.h"
#include "RhinoMarkPlugIn.h"

IMPLEMENT_DYNAMIC(CRhinoMarkObject, CCmdTarget)

CRhinoMarkObject::CRhinoMarkObject()
{
	EnableAutomation();
}

CRhinoMarkObject::~CRhinoMarkObject()
{
}

void CRhinoMarkObject::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CRhinoMarkObject, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CRhinoMarkObject, CCmdTarget)
  DISP_FUNCTION_ID(CRhinoMarkObject, "DoRhinoMark", dispidDoRhinoMark, DoRhinoMark, VT_I4, VTS_I4 VTS_BOOL)
END_DISPATCH_MAP()

// Note: we add support for IID_IRhinoMarkObject to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {48F21CC0-83B6-4B34-AD5E-D5A91105DAF9}
static const IID IID_IRhinoMarkObject =
{ 0x48F21CC0, 0x83B6, 0x4B34, { 0xAD, 0x5E, 0xD5, 0xA9, 0x11, 0x5, 0xDA, 0xF9 } };

BEGIN_INTERFACE_MAP(CRhinoMarkObject, CCmdTarget)
	INTERFACE_PART(CRhinoMarkObject, IID_IRhinoMarkObject, Dispatch)
END_INTERFACE_MAP()

// CRhinoMarkObject message handlers

LONG CRhinoMarkObject::DoRhinoMark(LONG frame_count, VARIANT_BOOL bFreeze)
{
  LONG rc = 0;

  CRhinoView* view = RhinoApp().ActiveView();
  if( view && 1 <= frame_count && frame_count <= 5000 )
  {
    bool b = ( bFreeze == VARIANT_TRUE ) ? true : false;
    DWORD delta_time = 0;
    if( RhinoRegenBenchMark(view, delta_time, frame_count, b) )
      rc = delta_time;
  }

  return rc;
}
