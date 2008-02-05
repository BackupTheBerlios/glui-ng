#ifndef __GLUI_CONTROL_H
#define __GLUI_CONTROL_H

/************************************************************/
/*                                                          */
/*       GLUI_Control: base class for all controls          */
/*                                                          */
/************************************************************/

/**
 All the GUI objects inherit from GLUI_Control: buttons,
 checkboxes, labels, edit boxes, scrollbars, etc.
 Most of the work of this class is in routing events,
 like keystrokes, mouseclicks, redraws, and sizing events.

 Yes, this is a huge and hideous class.  It needs to be
 split up into simpler subobjects.  None of the data members
 should be directly accessed by users (they should be protected,
 not public); only subclasses.
*/
#include <errno.h>
class GLUIAPI GLUI_Control : public GLUI_Node
{
    public : //types
        enum SizePolicy {
            FixedSize,
            PercentOfParent,
            FillSpace,
            AdaptThisToFitChilds,
        };

        union Size {
            struct {
                int w;
                int h;
            } size;
            struct {
                char w;
                char h;
            } percent;
            Size(int w, int h) {this->size.w=w; this->size.h=h; }
            Size() {this->size.w=0; this->size.h=0;}
            bool operator!=(const Size &other) const
                 { return (this->size.w != other.size.w) ||
                          (this->size.h != other.size.h);
                 }
            bool operator>(const Size &other) const
                {return (this->size.w > other.size.w) &&
                        (this->size.h > other.size.h);
                }
        };


    public:
        int            Width() const  {return w;}
        int            Height() const {return h;}

        /** Onscreen coordinates */
        int             w, h;                        /* dimensions of control */
        int             x_abs, y_abs;
        int             x_off, y_off;            // offset between childs elements
        int             y_off_top, y_off_bot;    // top and bottom margin inside the control
        int             x_off_left, x_off_right; // right and left inner margin
        int             contain_x, contain_y;
        int             contain_w, contain_h;
        /* if this is a container control (e.g.,
           radiogroup or panel) this indicated dimensions
           of inner area in which controls reside */

        /** "activation" for tabbing between controls. */
        int             active_type; ///< "GLUI_CONTROL_ACTIVE_..."
        bool            active;       ///< If true, we've got the focus
        bool            can_activate; ///< If false, remove from tab order.
        bool            spacebar_mouse_click; ///< Spacebar simulates click.

        /** Callbacks */
        long            user_id;  ///< Integer to pass to callback function.
        GLUI_CB         callback; ///< User callback function, or NULL.

        /** Variable value storage */
        float           float_val;        /**< Our float value */
        int             int_val;          /**< Our integer value */
        float           float_array_val[GLUI_DEF_MAX_ARRAY];
        int             float_array_size;

        /** "Live variable" updating */
        void           *ptr_val;          /**< A pointer to the user's live variable value */
        int             live_type;
        bool            live_inited;
        /* These variables store the last value that live variable was known to have. */
        int             last_live_int;
        float           last_live_float;
        std::string     last_live_text;
        float           last_live_float_array[GLUI_DEF_MAX_ARRAY];

        /** Properties of our control */
        GLUI           *glui;       /**< Our containing event handler (NEVER NULL during event processing!) */

        int             alignment;
        bool            enabled;    /**< Is this control grayed out? */

#warning "remove and use a class collapsible"
        bool            collapsible, is_open;
        GLUI_Node       collapsed_node;
        bool            hidden; /* Collapsed controls (and children) are hidden */

    public:
        /*** Get/Set values ***/
        virtual void   set_int_val( int new_int )         { int_val = new_int; output_live(true); }
        virtual void   set_float_val( float new_float )   { float_val = new_float; output_live(true); }
        virtual void   set_ptr_val( void *new_ptr )       { ptr_val = new_ptr; output_live(true); }
        virtual void   set_float_array_val( float *array_ptr );

        virtual float  get_float_val( void )              { return float_val; }
        virtual int    get_int_val( void )                { return int_val; }
        virtual void   get_float_array_val( float *array_ptr );
        virtual int    get_id( void ) const { return user_id; }
        virtual void   set_id( int id ) { user_id=id; }

        virtual int mouse_down_handler( int local_x, int local_y )                 { return false; }
        virtual int mouse_up_handler( int local_x, int local_y, bool inside )       { return false; }
        virtual int mouse_held_down_handler( int local_x, int local_y, bool inside) { return false; }
        virtual int key_handler( unsigned char key, int modifiers )                { return false; }
        virtual int special_handler( int key,int modifiers )                       { return false; }

        virtual void pack (int x, int y);
        virtual void update_size( void );
        virtual void idle( void )            { }
        virtual int  mouse_over( int state, int x, int y ) { return false; }

        virtual void enable( void );
        virtual void disable( void );
        virtual void activate( int how )     { active = true; }
        virtual void deactivate( void )     { active = false; }

        /** Hide (shrink into a rollout) and unhide (expose from a rollout) */
        void         hide_internal( int recurse );
        void         unhide_internal( int recurse );

        /** Return true if it currently makes sense to draw this class. */
        int          can_draw( void ) { return (glui != NULL && hidden == false); }


        virtual void draw(void)=0;


        int          set_to_glut_window( void );
        void         restore_window( int orig );
        virtual void         translate_and_draw( void );
        void         draw_box_inwards_outline( int x_min, int x_max,
                int y_min, int y_max );
        void         draw_box( int x_min, int x_max, int y_min, int y_max,
                float r, float g, float b );
        void         draw_bkgd_box( int x_min, int x_max, int y_min, int y_max );
        void         draw_emboss_box( int x_min, int x_max,int y_min,int y_max);

        void         draw_active_box( int x_min, int x_max, int y_min, int y_max );
        void         set_to_bkgd_color( void );

        virtual int         set_size( Size sz, Size min=Size(0,0) );
        void         set_alignment( int new_align );
        void         set_resize_policy( SizePolicy policy) { resizeable = policy; }
        SizePolicy   get_resize_policy( void ) { return resizeable;}


        void         sync_live( int recurse, int draw );  /* Reads live variable */
        void         init_live( void );
        void         output_live( int update_main_gfx );        /** Writes live variable **/
        void         execute_callback( void );
        virtual bool needs_idle( void ) const;
        virtual bool wants_tabs() const      { return false; }

        GLUI_Control(const char* name)
            : GLUI_Node(name)
              , collapsed_node("collapsed_node")
    {
        x_off          = GLUI_XOFF;
        y_off_top      = GLUI_YOFF;
        y_off_bot      = GLUI_YOFF;
        x_off_left     = GLUI_XOFF;
        x_off_right    = GLUI_XOFF;
        x_abs          = GLUI_XOFF;
        y_abs          = GLUI_YOFF;
        active         = false;
        enabled        = true;
        int_val        = 0;
        last_live_int  = 0;
        float_array_size = 0;
        float_val      = 0.0;
        last_live_float = 0.0;
        ptr_val        = NULL;
        glui           = NULL;
        w              = GLUI_DEFAULT_CONTROL_WIDTH;
        h              = GLUI_DEFAULT_CONTROL_HEIGHT;
        Min            = Size(x_off_left + x_off_right, y_off_top + y_off_bot);
        CurrentSize    = Min;
        active_type    = GLUI_CONTROL_ACTIVE_MOUSEDOWN;
        alignment      = GLUI_ALIGN_LEFT;
        can_activate   = true;         /* By default, you can activate a control */
        spacebar_mouse_click = true;    /* Does spacebar simulate a mouse click? */
        live_type      = GLUI_LIVE_NONE;
        last_live_text == "";
        live_inited    = false;
        collapsible    = false;
        is_open        = true;
        hidden         = false;
        resizeable     = FixedSize;
        int i;
        for( i=0; i<GLUI_DEF_MAX_ARRAY; i++ )
            float_array_val[i] = last_live_float_array[i] = 0.0;
    }

        virtual ~GLUI_Control();

    protected: //methods
        GLUI_Control();
    protected: //variables
        SizePolicy resizeable;
        Size CurrentSize;
        Size Min;
};

#endif
