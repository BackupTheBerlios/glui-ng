#ifndef __X11WRAPPER_H
#define __X11WRAPPER_H
using namespace std;
#ifdef __USE_XLIB
#include <X11/Xlib.h>
#else
#include <GL/glui/X11/Xlib.h>
#endif // __USE_XLIB

#endif // __X11WRAPPER_H
