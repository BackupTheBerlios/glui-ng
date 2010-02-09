#ifndef __GLUI_MASTEROBJECT_H
#define __GLUI_MASTEROBJECT_H


/************************************************************/
/*                                                          */
/*                     Master GLUI Class                    */
/*                                                          */
/************************************************************/

/**
 The master manages our interaction with GLUT.
 There's only one GLUI_Master_Object.
*/

#include <GL/glui/window.h>
namespace GLUI
{

    class MasterObject : public Node
    {

        public:
            static NCRC_AutoPtr<Node> Instance();
            NCRC_AutoPtr<GLUI::Window>      FindWindow( ::Window window_id );
            virtual int  add_control( Node *window );
            virtual void pack( int x, int y);

        private:
            MasterObject(const char *name);
             MasterObject();
    };

}

#endif //__GLUI_MASTEROBJECT_H
