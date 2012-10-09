/////////////////////////////////////////////////////////////////////////////
// HippoPlugInApp.cpp : Menu handler for Hippo skin.
//

#include "StdAfx.h"
#include "HippoPlugInPlugIn.h"
#include "../HippoSkin/Resource.h"

void CHippoPlugInPlugIn::OnInitPlugInMenuPopups( WPARAM wParam, LPARAM lParam )
{
  // TODO
}

BOOL CHippoPlugInPlugIn::OnPlugInMenuCommand( WPARAM wParam )
{
  switch( wParam )
  {
  case ID_FILE_NEW32773:
    ::RhinoApp().RunMenuScript( L"_New" );
    break;
  case ID_FILE_OPEN32774:
    ::RhinoApp().RunMenuScript( L"_Open" );
    break;
  case ID_FILE_SAVE32775:
    ::RhinoApp().RunMenuScript( L"_Save" );
    break;
  case ID_FILE_SAVEAS:
    ::RhinoApp().RunMenuScript( L"_SaveAs" );
    break;
  case ID_FILE_EXIT:
    ::RhinoApp().RunMenuScript( L"_Exit" );
    break;
  }
   
  return true;
}