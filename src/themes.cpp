/*

  glui_glut_window.h : the top level widget, in glut

  GLUI User Interface Toolkit
  Copyright (c) 2008 MALET Jean-Luc

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

*/

#include <GL/glui/themes.h>

using namespace GLUI;

theme::theme()
{
	int r=200, g=200, b=200;
	bkgd_color[0] = r;
	bkgd_color[1] = g;
	bkgd_color[2] = b;
	bkgd_color_f[0] = r / 255.0f;
	bkgd_color_f[1] = g / 255.0f;
	bkgd_color_f[2] = b / 255.0f;
}

theme* theme::Instance()
{
	static theme;
	return &theme;
}
