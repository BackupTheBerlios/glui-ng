#ifndef __GLUI_SEPARATOR_H
#define __GLUI_SEPARATOR_H

/************************************************************/
/*                                                          */
/*               Separator class                            */
/*                                                          */
/************************************************************/

class GLUIAPI GLUI_Separator : public GLUI_Control
{
public:
    void draw( void );

    GLUI_Separator( GLUI_Node *parent, const char* name );

protected:
    void common_init() {
        w            = 100;
        h            = GLUI_SEPARATOR_HEIGHT;
        can_activate = false;
    }
};

#endif
