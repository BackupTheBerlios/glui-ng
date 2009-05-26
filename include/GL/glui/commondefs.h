/* GLUI API shared library export/import declarations. */
#ifndef __GLUI_COMMONDEFS_H
#define __GLUI_COMMONDEFS_H

/* GLUI API shared library export/import declarations. */
#if defined(_WIN32)
# ifdef GLUI_BUILDING_LIB
#  ifdef GLUIDLL
#   define GLUIAPI __declspec(dllexport)
#  else
#   define GLUIAPI
#  endif
# else
#  ifdef GLUIDLL
#   define GLUIAPI __declspec(dllimport)
#  else
#   define GLUIAPI
#  endif
# endif
#else
#define GLUIAPI
#endif


#define GLUI_VERSION 2.36f    /********** Current version **********/

#if defined(_WIN32)
#  if !defined(GLUI_NO_LIB_PRAGMA) && !defined(GLUI_BUILDING_LIB)
// Link automatically with GLUI library
#    if defined GLUIDLL  // define this when using glui dynamic library
#      pragma comment(lib, "glui32dll.lib")
#    else
#      pragma comment(lib, "glui32.lib")
#    endif
#  endif
#endif


#endif // __GLUI_COMMONDEFS_H
