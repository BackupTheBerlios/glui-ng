#ifndef __GLUI_FILE_BROWSER_H
#define __GLUI_FILE_BROWSER_H

/************************************************************/
/*                                                          */
/*               File Browser class (container)             */
/*                         JVK                              */
/************************************************************/

/**
 A list of files the user can select from.
*/
class GLUIAPI GLUI_FileBrowser : public GLUI_Panel
{
public:
/**
 Create a new list of files the user can select from.

  @param parent The panel our object is inside; or the main GLUI object.
  @param name Prompt to give to the user at the top of the file browser.
  @param frame_type Optional style to display the panel with--GLUI_PANEL_EMBOSSED by default.
      GLUI_PANEL_RAISED causes the panel to appear higher than the surroundings.
      GLUI_PANEL_NONE causes the panel's outline to be invisible.
  @param id Optional ID number, to pass to the optional callback function.
  @param callback Optional callback function, taking either the int ID or control.
*/
    GLUI_FileBrowser( GLUI_Node *parent,
                      const char *name,
                      int frame_type = GLUI_PANEL_EMBOSSED,
                      int user_id = -1,
                      GLUI_CB callback = GLUI_CB());

    GLUI_List *list;
    std::string current_dir;

    void fbreaddir(const char *);
    static void dir_list_callback(GLUI_Control*);

    int   set_size( Size sz, Size min=Size(0,0) );
    const char* get_file() { return file.c_str(); }
    void set_allow_change_dir(int c) { allow_change_dir = c; }

protected:
    void common_init()
    {
        w            = GLUI_DEFAULT_CONTROL_WIDTH;
        h            = GLUI_DEFAULT_CONTROL_HEIGHT;
        int_val      = GLUI_PANEL_EMBOSSED;
        alignment    = GLUI_ALIGN_CENTER;
        can_activate = false;
        allow_change_dir = true;
        last_item    = -1;
        user_id      = -1;
        current_dir  = ".";
        file         = "";
    };

private:
    int last_item;
    std::string file;
    int allow_change_dir;

};


#endif
