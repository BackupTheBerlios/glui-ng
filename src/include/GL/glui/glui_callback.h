#ifndef __GLUI_CALLBACK_H
#define __GLUI_CALLBACK_H
#include <GL/glui/glui_forward.h>

/********** List of GLUT callbacks ********/

enum GLUI_Glut_CB_Types
{
    GLUI_GLUT_RESHAPE,
    GLUI_GLUT_KEYBOARD,
    GLUI_GLUT_DISPLAY,
    GLUI_GLUT_MOUSE,
    GLUI_GLUT_MOTION,
    GLUI_GLUT_SPECIAL,
    GLUI_GLUT_PASSIVE_MOTION,
    GLUI_GLUT_ENTRY,
    GLUI_GLUT_VISIBILITY
};
/*** Definition of callbacks ***/
typedef void (*GLUI_Update_CB) (int id);
typedef void (*GLUI_Control_CB)(GLUI_Control *);
typedef void (*Int1_CB)        (int);
typedef void (*Int2_CB)        (int, int);
typedef void (*Int3_CB)        (int, int, int);
typedef void (*Int4_CB)        (int, int, int, int);

/************************************************************/
/**
 Callback Adapter Class
    Allows us to support different types of callbacks;
    like a GLUI_Update_CB function pointer--which takes an int;
    and a GLUI_Control_CB function pointer--which takes a GUI_Control object.
*/
class GLUIAPI GLUI_CB
{
public:
  GLUI_CB() : idCB(0),objCB(0) {}
  GLUI_CB(GLUI_Update_CB cb) : idCB(cb),objCB(0) {}
  GLUI_CB(GLUI_Control_CB cb) : idCB(0),objCB(cb) {}
  // (Compiler generated copy constructor)

  /** This control just activated.  Fire our callback.*/
  void operator()(GLUI_Control *ctrl) const;
  bool operator!() const { return !idCB && !objCB; }
  operator bool() const { return !(!(*this)); }
private:
  GLUI_Update_CB idCB;
  GLUI_Control_CB objCB;
};

#endif
