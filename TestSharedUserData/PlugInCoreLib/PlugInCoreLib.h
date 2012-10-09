/////////////////////////////////////////////////////////////////////////////
// PlugInCoreLib.h
//

#pragma once

#if defined(PLUGINCORELIB_DLL_EXPORTS)

/* Compiling PlugInCoreLib as a Windows DLL - export classes, functions, and globals */
#define PLUGINCORELIB_CLASS __declspec(dllexport)
#define PLUGINCORELIB_FUNCTION __declspec(dllexport)
#define PLUGINCORELIB_DATA __declspec(dllexport)

#else

/* Using PlugInCoreLib as a Windows DLL - import classes, functions, and globals */
#define PLUGINCORELIB_CLASS __declspec(dllimport)
#define PLUGINCORELIB_FUNCTION __declspec(dllimport)
#define PLUGINCORELIB_DATA __declspec(dllimport)

#endif

/////////////////////////////////////////////////////////////////////////////
// Exported functions

PLUGINCORELIB_FUNCTION
bool HasPlugInUserData( const CRhinoObject* object );

PLUGINCORELIB_FUNCTION
bool AddPlugInUserData( CRhinoDoc& doc, const CRhinoObject* object, ON_3dPoint point, ON_wString string );

PLUGINCORELIB_FUNCTION
bool SetPlugInUserData( CRhinoDoc& doc, const CRhinoObject* object, ON_3dPoint point, ON_wString string );

PLUGINCORELIB_FUNCTION
bool GetPlugInUserData( const CRhinoObject* object, ON_3dPoint& point, ON_wString& string );

PLUGINCORELIB_FUNCTION
bool RemovePlugInUserData( CRhinoDoc& doc, const CRhinoObject* object );

/////////////////////////////////////////////////////////////////////////////
// Plug-in linking pragmas

#if !defined(PLUGINCORELIB_DLL_EXPORTS)

#if defined(NDEBUG) && defined(RHINO_DEBUG_PLUGIN)
#pragma message( " --- Plug-in linking with PlugInCoreLib PseudoDebug Win32." )
#pragma comment(lib, "../PlugInCoreLib/PseudoDebug/PlugInCoreLib.lib")

#elif defined(NDEBUG)
#pragma message( " --- Plug-in linking with PlugInCoreLib Release Win32." )
#pragma comment(lib, "../PlugInCoreLib/Release/PlugInCoreLib.lib")

#else // Debug
#pragma message( " --- Plug-in linking with PlugInCoreLib Debug Win32." )
#pragma comment(lib, "../PlugInCoreLib/Debug/PlugInCoreLib.lib")
#endif

#endif