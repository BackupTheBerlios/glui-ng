#ifndef __GLUI_LIVE_H
#define __GLUI_LIVE_H
#include <cstring>
#include <string>

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
};


#endif//__GLUI_LIVE_H
