#ifndef __GLUI_LIVE_H
#define __GLUI_LIVE_H
#include <cstring>
#include <string>
/*
   GLUI-ng, an openGL widget toolkit. Copyright (C) 2010 MALET Jean-Luc

   This library is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the 
   Free Software Foundation; either version 2.1 of the License, 
   or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License along with this library;
   if not, write to the 
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 

   based on the work of Paul Rademacher (orignal software http://glui.sourceforge.net/)
*/

/********** What type of live variable does a control have? **********/

namespace GLUI
{
	class LiveVariables
	{
		public : //methods
			LiveVariables(long user_id=-1, CB callback=CB());
			virtual int    get_id( void ) const { return user_id; }
			virtual void   set_id( int id ) { user_id=id; }
			void         execute_callback( void );
		protected : //variables
			/** Callbacks */
			int             ManagedByUser;
			long            user_id;  ///< Integer to pass to callback function.
			CB*             callback; ///< User callback function, or NULL.
	};


	class LiveInt : public LiveVariables
	{
		public : //methods
			LiveInt(int* live, long user_id=-1, CB callback=CB());
			~LiveInt();
			void  SetVal( int new_int );
			int   GetVal();
		protected: //variables
			int* value;
	};

	class LiveFloat : public LiveVariables
	{
		public :
			LiveFloat(float* live, long user_id=-1, CB callback=CB());
			void   SetVal( float new_float );
			float  GetVal();
		protected:
			float* value;
	};
	
	class LiveText : public LiveVariables, public std::string
	{
		public:
			LiveText(std::string* live, long user_id=-1, CB callback=CB());
			void   SetVal( std::string string);
			std::string GetVal();
		protected:
			std::string* value;
	};

	class LiveDouble : public LiveVariables
	{
		public:
			LiveDouble(double* live, long user_id=-1, CB callback=CB());
			void   SetVal( double new_double);
			double GetVal();
		protected :
			double* value;
	};

/*	class LivefloatArray : public LiveVariables
	{
		public :
			LivefloatArray(long user_id=-1, CB callback=CB());
			void   SetVal(float* NewFloatarray);
			float* GetVal();
		protected :
			float* value[GLUI_DEF_MAX_ARRAY];
	};*/
}


#endif//__GLUI_LIVE_H
