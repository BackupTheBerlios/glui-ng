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
#ifndef __NONCOPYABLECLASS_H
#define __NONCOPYABLECLASS_H
namespace GLUI
{
        class NonCopyableClass
        {
                public : 
                        NonCopyableClass() {};
                        virtual ~NonCopyableClass() {};
                private :
                        NonCopyableClass(const NonCopyableClass & copy) {};
                        virtual NonCopyableClass& operator= 
                                (const NonCopyableClass& n) throw() 
                                {return *this;};

        };


        class NonCopyableReferenceCountedClass :public NonCopyableClass
        {
                public:
                        void addReference();
                        void removeReference();
                        void markUnshareable();
                        bool isShareable() const;
                        bool isShared() const;
                        int  GetCount() const;

                public:
                        NonCopyableReferenceCountedClass();
                        virtual ~NonCopyableReferenceCountedClass() = 0;
                private:
                        int refCount;
                        bool shareable;
        };


}
#endif //__NONCOPYABLECLASS_H
