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

#warning "hide x, y, y_off_top... into private"
// expose them through inline API
// do pack on setting of x, y, offset, size, orientation, alignement
// same for update_size

#warning "rewrite size computation algorythm, do it in 2 pass"
// first pass : parse down fixed size widget
// second pass : parse up variable size widget
#warning "create an image button widget"
#warning "create a live variable class"
#warning "create toggle button"
#warning "create a real bitmap class that can be used as control"
#warning "use toggle button in checkbox, do some cleaning..."
#warning "implement such mechanism with event handling"
#warning "mutex to prevent accessing live data of controls while displaying"
#warning "handle internal live variable as enum and union"
#warning "create a layout class that will handle the position of the child widget according to the parent policy"
#warning "update code to have either fixed size control, dynamic sized control and proportional sized control"
#warning "free ressources of text in destructor"
#warning "spinner class should use container facilities.... in particular"
#warning "fix display bug seen into example2"
#warning "still drawing bug"
#warning "add delete virtual to delete the whole tree with one delete call"
#warning "add delete virtual to delete the whole tree with one delete call"
#warning "use this string in debug to display the tree"
#warning "add tree parsing function to select a node according some criteria"
#warning "add delete virtual to delete the whole tree with one delete call"
#warning "decorelate name from displayed content"


int __GLUI__todo() {
	return 1;
}

