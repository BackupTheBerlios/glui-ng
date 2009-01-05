#ifndef __GLUI_BITMAPS_H
#define __GLUI_BITMAPS_H
/************************************************************/
/*                                                          */
/*                  Standard Bitmap stuff                   */
/*                                                          */
/************************************************************/
namespace GLUI
{
	/************************************************************/
	/*                                                          */
	/*                  Class Bitmap                       */
	/*                                                          */
	/************************************************************/

	/**
	  Bitmap is a simple 2D texture map.  It's used
	  to represent small textures like checkboxes, arrows, etc.
	  via the StdBitmaps class.
	  */
	class Bitmap
	{
		friend class StdBitmaps;

		public:
		Bitmap();
		~Bitmap();

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
	/*                  Class StdBitmap                    */
	/*                                                          */
	/************************************************************/

	/**
	  Keeps an array of Bitmap objects to represent all the
	  images used in the UI: checkboxes, arrows, etc.
	  */
	class StdBitmaps
	{
		public: //enums
			enum Codes
			{
				CHECKBOX_OFF = 0,
				CHECKBOX_ON,
				RADIOBUTTON_OFF,
				RADIOBUTTON_ON,
				UP_ARROW,
				DOWN_ARROW,
				LEFT_ARROW,
				RIGHT_ARROW,
				SPINNER_UP_OFF,
				SPINNER_UP_ON,
				DOWN_OFF,
				DOWN_ON,
				CHECKBOX_OFF_DIS,    /*** Disactivated control bitmaps ***/
				CHECKBOX_ON_DIS,
				RADIOBUTTON_OFF_DIS,
				RADIOBUTTON_ON_DIS,
				SPINNER_UP_DIS,
				SPINNER_DOWN_DIS,
				LISTBOX_UP,
				LISTBOX_DOWN,
				LISTBOX_UP_DIS,
				NUM_ITEMS
			};


		public:
			static StdBitmaps* Instance();
			/** Return the width (in pixels) of the n'th standard bitmap. */
			int  width (Codes n) const;
			/** Return the height (in pixels) of the n'th standard bitmap. */
			int  height(Codes n) const;

			/** Draw the n'th standard bitmap (one of the enums
			  listed in StdBitmaps_Codes) at pixel corner (x,y).
			  */
			void draw(Codes n, int x, int y) const;

		private:
			~StdBitmaps();
			StdBitmaps();
			Bitmap bitmaps[NUM_ITEMS];
	};

}
#endif
