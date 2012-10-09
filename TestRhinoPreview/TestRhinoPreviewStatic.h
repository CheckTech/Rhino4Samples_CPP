/////////////////////////////////////////////////////////////////////////////
// TestRhinoPreviewStatic.h

#pragma once

// Owner-drawn static control
class CTestRhinoPreviewStatic : public CStatic
{
	DECLARE_DYNAMIC( CTestRhinoPreviewStatic )

public:
	CTestRhinoPreviewStatic();
	virtual ~CTestRhinoPreviewStatic();

  bool UpdateDib( const wchar_t* filename );
  void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );

protected:
	DECLARE_MESSAGE_MAP()

private:
  CRhinoDib m_dib;
};
