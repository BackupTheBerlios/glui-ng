#ifndef __GLUI_STATICTEXT_H
#define __GLUI_STATICTEXT_H
/************************************************************/
/*                                                          */
/*               StaticText class                           */
/*                                                          */
/************************************************************/
#include <GL/glui/glui_forward.h>
#include <GL/glui/glui_text.h>
#include <GL/glui/glui_control.h>

class GLUIAPI GLUI_StaticText : public GLUI_Control, public GLUI_Text
{
public:
    void set_text( const char *text );
    void draw( void );
    void update_size( void );

    GLUI_StaticText(GLUI_Node *parent, const char *name);

protected:
    void common_init() {
        can_activate  = false;
    }

    void erase_text( void );
};
#endif
