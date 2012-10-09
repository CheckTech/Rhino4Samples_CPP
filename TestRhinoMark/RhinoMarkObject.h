/////////////////////////////////////////////////////////////////////////////
// RhinoMarkObject.h

#pragma once

class CRhinoMarkObject : public CCmdTarget
{
	DECLARE_DYNAMIC( CRhinoMarkObject )

public:
	CRhinoMarkObject();
	virtual ~CRhinoMarkObject();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

  LONG DoRhinoMark( LONG frame_count, VARIANT_BOOL bFreeze );

  enum 
  {
    dispidDoRhinoMark = 1L
  };
};


