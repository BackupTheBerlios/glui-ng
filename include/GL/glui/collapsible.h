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

#ifndef __GLUI_COLLAPSIBLE_H
#define __GLUI_COLLAPSIBLE_H
#include <GL/glui/commondefs.h>
#include <GL/glui/container.h>

namespace GLUI
{

class GLUIAPI Collapsible : public Container
{
    public  :
        Collapsible(const char *name,
                   orientation orient=Container::TopDown);
        void  open               (  bool recurse=false );
        void  close              (  bool recurse=false );

    protected :
        bool            is_open;
        NCRC_AutoPtr<Control>   Toggle; //the toggle ie widget that is always displayed
        NCRC_AutoPtr<Control>   Content; //the content that can or not be displayed
};

}
#endif //__GLUI_COLLAPSIBLE_H
