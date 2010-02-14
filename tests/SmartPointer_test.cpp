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
#include <GL/glui/SmartPointer.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace GLUI;
using namespace std;

class testNonCopyAble : public NonCopyableReferenceCountedClass
{
        public :
                testNonCopyAble(int val=0) { value = val; };
                int value;
};

int main(int argc, char** argv)
{
        testNonCopyAble* ref = new testNonCopyAble(1);
        testNonCopyAble* newref = new testNonCopyAble(2);

        NCRC_AutoPtr<testNonCopyAble> first = NCRC_AutoPtr<testNonCopyAble>(ref); //copy constructor
        NCRC_AutoPtr<testNonCopyAble> second;
        NCRC_AutoPtr<testNonCopyAble> third(newref);
        if (first->GetCount() != 1)
        {
                cerr << "first count != 1" <<endl;
                return -1;
        }
        if (first != ref)
        {
                cerr << "first and ref don't have same address" <<endl;
                return -1;
        }
        if (second != NULL)
        {
                cerr << "second isn't null" <<endl;
                return -1;
        }
        second = first;
        if (first != ref)
        {
                cerr << "first and ref don't have same address after assignement" <<endl;
                return -1;
        }
        if (second != ref)
        {
                cerr << "second and ref don't have same address" <<endl;
                return -1;
        }
        if (first->GetCount() != 2)
        {
                cerr << "first count != 2" <<endl;
                return -1;
        }
        if (second->GetCount() != 2)
        {
                cerr << "first count != 2" <<endl;
                return -1;
        }
        first = third;
        if (first != newref)
        {
                cerr << "first and newref don't have same address after assignement" <<endl;
                return -1;
        }
        if (second != ref)
        {
                cerr << "second and ref don't have same address after first=third" <<endl;
                return -1;
        }
        if (first->GetCount() != 2)
        {
                cerr << "first count != 2" <<endl;
                return -1;
        }
        if (third->GetCount() != 2)
        {
                cerr << "first count != 2" <<endl;
                return -1;
        }
        if (second->GetCount() != 1)
        {
                cerr << "first count != 1" <<endl;
                return -1;
        }
        //valgrind shall report error on this if not correctly handled
        first = NULL;
        second = NULL;
        third = NULL;
        /*third.SetPointee(NULL);
        if (first != NULL)
        {
                cerr << "first and NULL don't have same address after assignement" <<endl;
                return -1;
        }
        if (third != NULL)
        {
                cerr << "third and NULL don't have same address after first=third" <<endl;
                return -1;
        }*/
}
