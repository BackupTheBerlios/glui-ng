/*
   GLUI, an openGL widget toolkit. Copyright (C) 2010 MALET Jean-Luc

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
*/
#include <GL/glui/NonCopyableClass.h>
#include <GL/glui/Exception.h>
#ifndef __SMARTPOINTER_H
#define __SMARTPOINTER_H
namespace GLUI
{

        template<class __Array>
                class Array
                {
                        public :
                                Array(int count);
                                virtual ~Array();
                                __Array& operator[] (int index);
                        protected:
                                __Array* data;
                };

        /* NCRC : Non Copyable Reference Counted class  */

        template<class T>
                class NCRC_AutoPtr 
                {
                        public:
                                NCRC_AutoPtr(T* realPtr = 0);
                                NCRC_AutoPtr(const NCRC_AutoPtr& rhs);
                                ~NCRC_AutoPtr();
                                NCRC_AutoPtr& operator=(const NCRC_AutoPtr& rhs);
                                void SetPointee(T* NewPointee); //< broadcast the pointee
                                bool operator==(const T* rhs);
                                bool operator!=(const T* rhs);

                                T* operator->() const;
                                T& operator*() const;

                                T* getPointee() // give access to pointee
                                { return this->pointee; }

                        private:
                                T *pointee;

                                void init();
                };

        template<class T>
                void NCRC_AutoPtr<T>::init()
                {
                        if (pointee->isShareable() == false) 
                        {
                                throw Exception(EINVAL,"trying to duplicate a non copyable object");
                                //T *oldValue = this->pointee;
                                //counter = new CountHolder;
                                //counter->pointee = oldValue ? new T(*oldValue) : 0;
                        } 

                        pointee->addReference();
                }

        template<class T>
                NCRC_AutoPtr<T>::NCRC_AutoPtr(T* realPtr)
                { 
                        this->pointee = realPtr;
                        init();
                }

        template<class T>
                NCRC_AutoPtr<T>::NCRC_AutoPtr(const NCRC_AutoPtr& rhs)
                {
                        pointee = rhs.pointee;
                        init();
                }

        template<class T>
                NCRC_AutoPtr<T>::~NCRC_AutoPtr()
                {
                        pointee->removeReference();
                }

        template<class T>
                NCRC_AutoPtr<T>& NCRC_AutoPtr<T>::operator=(const NCRC_AutoPtr& rhs)
                {
                        if (pointee != rhs.pointee) 
                        {
                                pointee->removeReference();
                                pointee = rhs.pointee;
                                init();
                        }
                        return *this;
                }

        template<class T>
                bool NCRC_AutoPtr<T>::operator==(const T* rhs)
                {
                        return (this->pointee == rhs);
                }

        template<class T>
                bool NCRC_AutoPtr<T>::operator!=(const T* rhs)
                {
                        return (this->pointee != rhs);
                }


        template<class T>
                T* NCRC_AutoPtr<T>::operator->() const
                { return this->pointee; }

        template<class T>
                T& NCRC_AutoPtr<T>::operator*() const
                { return *(this->pointee); }

        ///////////////////////////////////////////////////////////////////////////
        // NCIRC :  Non Copyable Indirect Reference Counted class  for reference //
        /*
           template<class T>
                class NCRC_AutoPtr 
                {
                        public:
                                NCRC_AutoPtr(T* realPtr = 0);
                                NCRC_AutoPtr(const NCRC_AutoPtr& rhs);
                                ~NCRC_AutoPtr();
                                NCRC_AutoPtr& operator=(const NCRC_AutoPtr& rhs);
                                bool operator==(const T* rhs);
                                bool operator!=(const T* rhs);

                                T* operator->() const;
                                T& operator*() const;

                                NonCopyableReferenceCountedClass& getReferenceCounter()  // give clients access to
                                { return *counter; }     // isShared, etc.
                                T* getPointee() // give access to a reference for type checking
                                { return counter->pointee; }

                        private:
                                struct CountHolder: public NonCopyableReferenceCountedClass
                                {
                                        ~CountHolder() { delete pointee; }
                                        T *pointee;
                                };

                                CountHolder *counter;
                                void init();
                };

        template<class T>
                void NCRC_AutoPtr<T>::init()
                {
                        if (counter->isShareable() == false) 
                        {
                                throw Exception(EINVAL,"trying to duplicate a non copyable object");
                                //T *oldValue = counter->pointee;
                                //counter = new CountHolder;
                                //counter->pointee = oldValue ? new T(*oldValue) : 0;
                        } 

                        counter->addReference();
                }

        template<class T>
                NCRC_AutoPtr<T>::NCRC_AutoPtr(T* realPtr)
                : counter(new CountHolder)
                { 
                        counter->pointee = realPtr;
                        init();
                }

        template<class T>
                void NCRC_AutoPtr<T>::SetPointee(T* NewPointee)
                {
                        if (counter->pointee != NULL)
                        {
                                delete counter->pointee;
                        }
                        counter->pointee = NewPointee;
                }


        template<class T>
                NCRC_AutoPtr<T>::NCRC_AutoPtr(const NCRC_AutoPtr& rhs)
                : counter(rhs.counter)
                { init(); }

        template<class T>
                NCRC_AutoPtr<T>::~NCRC_AutoPtr()
                { counter->removeReference(); }

        template<class T>
                NCRC_AutoPtr<T>& NCRC_AutoPtr<T>::operator=(const NCRC_AutoPtr& rhs)
                {
                        if (counter != rhs.counter) 
                        {
                                counter->removeReference();
                                counter = rhs.counter;
                                init();
                        }
                        return *this;
                }

        template<class T>
                bool NCRC_AutoPtr<T>::operator==(const T* rhs)
                {
                        return (counter->pointee == rhs);
                }

        template<class T>
                bool NCRC_AutoPtr<T>::operator!=(const T* rhs)
                {
                        return (counter->pointee != rhs);
                }


        template<class T>
                T* NCRC_AutoPtr<T>::operator->() const
                { return counter->pointee; }

        template<class T>
                T& NCRC_AutoPtr<T>::operator*() const
                { return *(counter->pointee); }

        */

}
#endif //__SMARTPOINTER_H
