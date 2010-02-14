/*
   GLUI-ng, an openGL widget toolkit. Copyright (C) 2010 MALET Jean-Luc

   This library is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the 
   Free Software Foundation; either version 2.1 of the License, 
   or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License along with this library;
   if not, write to the 
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 

   based on the work of Paul Rademacher (orignal software http://glui.sourceforge.net/)
*/

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
