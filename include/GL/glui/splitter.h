#ifndef __GLUI_SPLITTER_H
#define __GLUI_SPLITTER_H
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

#include <GL/glui/container.h>
#include <GL/glui/panel.h>
#include <GL/glui/separator.h>


/************************************************************/
/*                                                          */
/*               Splitter class                             */
/*                                                          */
/************************************************************/

/**
 A Splitter object devide the drawing area into 2 container
 separated by an optional bar.
 The Layout can be either vertical or horizontal (default)
*/
namespace GLUI
{
    class GLUIAPI Splitter : public Container
    {
        public:
            Splitter( Node *parent, const char* name, bool draw_bar = true );
            Panel *GetFirstPanel() {return &first_panel;}
            Panel *GetSecondPanel() {return &second_panel;}
            void draw() {} //<nothing done here, all is done by translate_and_draw

        protected: //variables
            Panel first_panel;
            Panel second_panel;
            Separator separator;
            bool draw_separator;

        protected: //methods
             void common_init();
    };
}
#endif //__SPLITTER_H
