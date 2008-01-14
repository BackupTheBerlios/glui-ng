#ifndef __GLUI_BITMAPS_H
#define __GLUI_BITMAPS_H
/************************************************************/
/*                                                          */
/*                  Standard Bitmap stuff                   */
/*                                                          */
/************************************************************/

enum GLUI_StdBitmaps_Codes
{
    GLUI_STDBITMAP_CHECKBOX_OFF = 0,
    GLUI_STDBITMAP_CHECKBOX_ON,
    GLUI_STDBITMAP_RADIOBUTTON_OFF,
    GLUI_STDBITMAP_RADIOBUTTON_ON,
    GLUI_STDBITMAP_UP_ARROW,
    GLUI_STDBITMAP_DOWN_ARROW,
    GLUI_STDBITMAP_LEFT_ARROW,
    GLUI_STDBITMAP_RIGHT_ARROW,
    GLUI_STDBITMAP_SPINNER_UP_OFF,
    GLUI_STDBITMAP_SPINNER_UP_ON,
    GLUI_STDBITMAP_SPINNER_DOWN_OFF,
    GLUI_STDBITMAP_SPINNER_DOWN_ON,
    GLUI_STDBITMAP_CHECKBOX_OFF_DIS,    /*** Disactivated control bitmaps ***/
    GLUI_STDBITMAP_CHECKBOX_ON_DIS,
    GLUI_STDBITMAP_RADIOBUTTON_OFF_DIS,
    GLUI_STDBITMAP_RADIOBUTTON_ON_DIS,
    GLUI_STDBITMAP_SPINNER_UP_DIS,
    GLUI_STDBITMAP_SPINNER_DOWN_DIS,
    GLUI_STDBITMAP_LISTBOX_UP,
    GLUI_STDBITMAP_LISTBOX_DOWN,
    GLUI_STDBITMAP_LISTBOX_UP_DIS,
    GLUI_STDBITMAP_NUM_ITEMS
};

/************************************************************/
/*                                                          */
/*                  Class GLUI_Bitmap                       */
/*                                                          */
/************************************************************/

/**
 GLUI_Bitmap is a simple 2D texture map.  It's used
 to represent small textures like checkboxes, arrows, etc.
 via the GLUI_StdBitmaps class.
*/
class GLUIAPI GLUI_Bitmap
{
    friend class GLUI_StdBitmaps;

public:
    GLUI_Bitmap();
    ~GLUI_Bitmap();

    /** Create bitmap from greyscale byte image */
    void init_grey(unsigned char *array);

    /** Create bitmap from color int image */
    void init(int *array);

private:
    /** RGB pixel data */
    unsigned char *pixels;
    int            w, h;
};


/************************************************************/
/*                                                          */
/*                  Class GLUI_StdBitmap                    */
/*                                                          */
/************************************************************/

/**
 Keeps an array of GLUI_Bitmap objects to represent all the
 images used in the UI: checkboxes, arrows, etc.
*/
class GLUIAPI GLUI_StdBitmaps
{
public:
    GLUI_StdBitmaps();
    ~GLUI_StdBitmaps();

    /** Return the width (in pixels) of the n'th standard bitmap. */
    int  width (int n) const;
    /** Return the height (in pixels) of the n'th standard bitmap. */
    int  height(int n) const;

    /** Draw the n'th standard bitmap (one of the enums
       listed in GLUI_StdBitmaps_Codes) at pixel corner (x,y).
    */
    void draw(int n, int x, int y) const;

private:
    GLUI_Bitmap bitmaps[GLUI_STDBITMAP_NUM_ITEMS];
};


#endif
