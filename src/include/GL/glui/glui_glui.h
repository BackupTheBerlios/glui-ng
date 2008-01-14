#ifndef __GLUI_GLUI_H
#define __GLUI_GLUI_H

#include  <GL/glui/glui_main.h>

/**
 The main user-visible interface object to GLUI.

*/
class GLUIAPI GLUI : public GLUI_Main
{
public:
    int   add_control( GLUI_Control *control ) { return main_panel->add_control(control); }

/** Set the window where our widgets should be displayed. */
    void            set_main_gfx_window( int window_id );
    int             get_glut_window_id( void ) { return glut_window_id; }

    void            enable( void ) { main_panel->enable(); }
    void            disable( void );

    void            sync_live( void );

    void            close( void );

    void            show( void );
    void            hide( void );
    GLUI_Panel*     Get_main_panel() { return main_panel;}

    /***** GLUT callback setup functions *****/
    /*
      void set_glutDisplayFunc(void (*f)(void));
      void set_glutReshapeFunc(void (*f)(int width, int height));
      void set_glutKeyboardFunc(void (*f)(unsigned char key, int x, int y));
      void set_glutSpecialFunc(void (*f)(int key, int x, int y));
      void set_glutMouseFunc(void (*f)(int button, int state, int x, int y));
      void set_glutMotionFunc(void (*f)(int x, int y));
      void set_glutPassiveMotionFunc(void (*f)(int x, int y));
      void set_glutEntryFunc(void (*f)(int state));
      void set_glutVisibilityFunc(void (*f)(int state));
      void set_glutInit( int *argcp, const char **argv );
      void set_glutInitWindowSize(int width, int height);
      void set_glutInitWindowPosition(int x, int y);
      void set_glutInitDisplayMode(unsigned int mode);
      int  set_glutCreateWindow(const char *name);
    */

    /***** Constructors and desctructors *****/

    int init( const char *name, long flags, int x, int y, int parent_window );
protected:
    virtual int add_control( GLUI_Node *parent, GLUI_Control *control ) {
        return GLUI_Main::add_control( parent, control );
    }
};

#endif //__GLUI_GLUI_H
