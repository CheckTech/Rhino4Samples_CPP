/////////////////////////////////////////////////////////////////////////////
// TestScriptObject.h
//

#pragma once

class CTestScriptObject : public CCmdTarget
{
	DECLARE_DYNAMIC(CTestScriptObject)

public:
	CTestScriptObject();
	virtual ~CTestScriptObject();
	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

  enum 
  {
    dispidAddPointCloud = 4L,
    dispidAddPoint = 3L,
    dispidMultiply = 2L,
    dispidAbout = 1L
  };

  void About(void);
  DOUBLE Multiply(DOUBLE a, DOUBLE b);
  VARIANT AddPoint(VARIANT* vaPoint);
  VARIANT AddPointCloud(VARIANT* vaPointCloud);
};


