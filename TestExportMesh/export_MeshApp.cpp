/////////////////////////////////////////////////////////////////////////////
// export_MeshApp.cpp

#include "stdafx.h"
#include "export_MeshApp.h"

//
//	Note!
//
//    A Rhino plug-in is an MFC DLL.
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

BEGIN_MESSAGE_MAP(Cexport_MeshApp, CWinApp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cexport_MeshApp construction

Cexport_MeshApp::Cexport_MeshApp()
{
}

// The one and only Cexport_MeshApp object
Cexport_MeshApp theApp;

/////////////////////////////////////////////////////////////////////////////
// Cexport_MeshApp initialization

BOOL Cexport_MeshApp::InitInstance()
{
	CWinApp::InitInstance();
	return TRUE;
}
