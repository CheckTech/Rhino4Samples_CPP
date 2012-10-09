/////////////////////////////////////////////////////////////////////////////
// TestRhinoPreviewStatic.cpp

#include "stdafx.h"
#include "TestRhinoPreviewStatic.h"

IMPLEMENT_DYNAMIC( CTestRhinoPreviewStatic, CStatic )

CTestRhinoPreviewStatic::CTestRhinoPreviewStatic()
{
}

CTestRhinoPreviewStatic::~CTestRhinoPreviewStatic()
{
}

BEGIN_MESSAGE_MAP( CTestRhinoPreviewStatic, CStatic )
END_MESSAGE_MAP()

bool CTestRhinoPreviewStatic::UpdateDib( const wchar_t* filename )
{
  m_dib.DestroyDib();

  if( 0 == filename || 0 == filename[0] || !CRhinoFileUtilities::FileExists(filename) )
    return false;

  FILE* archive_fp = ON::OpenFile( filename, L"rb" );
  if( 0 == archive_fp ) 
    return false;

  ON_BinaryFile archive( ON::read3dm, archive_fp );
    
  int file_version = 0;
  ON_String strComments;
  if( !archive.Read3dmStartSection(&file_version, strComments) )
  {
    ON::CloseFile( archive_fp );
    return false;
  }

  ON_3dmProperties properties;
  if( !archive.Read3dmProperties(properties) )
  {
    ON::CloseFile( archive_fp );
    return false;
  }

  ON::CloseFile( archive_fp );

  if( !properties.m_PreviewImage.IsValid() )
    return false;

  LPBITMAPINFO bmi = properties.m_PreviewImage.m_bmi;
  if( 0 == bmi )
    return false;

  properties.m_PreviewImage.m_bmi = 0;
  m_dib.SetDib( bmi, true );
  Invalidate();

  return true;
}

void CTestRhinoPreviewStatic::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
  if( lpDrawItemStruct && m_dib.FindDIBBits() )
  {
    CDC dc;
    if( dc.Attach(lpDrawItemStruct->hDC) )
    {
      m_dib.Stretch( &dc, lpDrawItemStruct->rcItem );
      dc.Detach();
    }
  }                
}
