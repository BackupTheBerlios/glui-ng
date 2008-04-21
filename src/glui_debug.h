/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui_debug.h - Glui trace facility


          --------------------------------------------------

  Copyright (c) 2007 Jean-Luc MALET

  WWW:    http://sourceforge.net/projects/glui/
  Forums: http://sourceforge.net/forum/?group_id=92496

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

*****************************************************************************/
#ifndef __GLUI_DEBUG_H
#define __GLUI_DEBUG_H

using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <fstream>
//#include "GL/glui/glui_main.h"


const size_t ISIZE = 500;

class GLUI_debug
{
    public :
        static GLUI_debug* Instance();

        ~GLUI_debug();
        int print(const char* file, int line, const char* format,...);
        void FlushGL(); //flush gl operation if possible and if
                        //GLUI_SYNC environment variable is set

    private:
        GLUI_debug();
        char* use_debug;
        char* buf;
};

/*
public class ClassSingleton {
    // Seule instance de Class Factory
    public static ClassSingleton seuleInstance;
    // Initialisateur
    static {
        // Crée la seule instance
        seuleInstance = new ClassSingleton();
    }
    // Constructeur privé
    private ClassSingleton() {
    }
    // Getter qui renvoie l’instance
    public ClassSingleton getInstance() {
        return seuleInstance;
    }
}*/


#endif //__GLUI_DEBUG_H
