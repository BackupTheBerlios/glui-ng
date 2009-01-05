#ifndef __GLUI_CALLBACK_H
#define __GLUI_CALLBACK_H

/********** List of GLUT callbacks ********/
namespace GLUI
{
	class Control;

	enum Glut_CB_Types
	{
		GLUT_RESHAPE,
		GLUT_KEYBOARD,
		GLUT_DISPLAY,
		GLUT_MOUSE,
		GLUT_MOTION,
		GLUT_SPECIAL,
		GLUT_PASSIVE_MOTION,
		GLUT_ENTRY,
		GLUT_VISIBILITY
	};
	/*** Definition of callbacks ***/
	typedef void (*Update_CB) (int id);
	typedef void (*Control_CB)(Control *);
	typedef void (*Int1_CB)        (int);
	typedef void (*Int2_CB)        (int, int);
	typedef void (*Int3_CB)        (int, int, int);
	typedef void (*Int4_CB)        (int, int, int, int);

	/************************************************************/
	/**
	  Callback Adapter Class
	  Allows us to support different types of callbacks;
	  like a Update_CB function pointer--which takes an int;
	  and a Control_CB function pointer--which takes a GUI_Control object.
	  */
	class GLUIAPI CB
	{
		public:
			CB() : idCB(0),objCB(0) {}
			CB(Update_CB cb) : idCB(cb),objCB(0) {}
			CB(Control_CB cb) : idCB(0),objCB(cb) {}
			// (Compiler generated copy constructor)

			/** This control just activated.  Fire our callback.*/
			void operator()(Control *ctrl) const;
			bool operator!() const { return !idCB && !objCB; }
			operator bool() const { return !(!(*this)); }
			void         execute_callback( void );
		private:
			Update_CB idCB;
			Control_CB objCB;
	};
}
#endif
