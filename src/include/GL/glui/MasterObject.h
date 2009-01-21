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
            static MasterObject* Instance();
            GLUIWindow*      FindWindow( WindowId window_id );
            virtual int  add_control( Node *window );

        private:
            MasterObject();
    };

    inline MasterObject::MasterObject()
    {
    }

}

#endif //__GLUI_MASTEROBJECT_H
