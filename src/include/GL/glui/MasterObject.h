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
/*
#include <GL/glui/window.h>
namespace GLUI
{

    class MasterObject
    {

        public:
            static MasterObject* Register();
            static void DeRegister();
            static MasterObject* Instance();
            Window*      FindWindow( WindowId window_id );

            Node     gluis;
            Control *active_control;

            //void           get_viewport_area( int *x, int *y, int *w, int *h );
            //void           auto_set_viewport();
            //void           close_all();
            //void           sync_live_all();
            //void           reshape();
            //float          get_version() { return GLUI_VERSION; }

            //void glui_setIdleFuncIfNecessary(void);


        private:
            ~MasterObject();
            MasterObject();
            static MasterObject* TheInstance;
            static int ClientCount;

            Node     glut_windows;

            void (*glut_idle_CB)(void);
            void          add_cb_to_glut_window(int window,int cb_type,void *cb);
    };

}
*/
#endif //__GLUI_MASTEROBJECT_H
