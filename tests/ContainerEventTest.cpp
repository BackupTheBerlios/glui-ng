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

#include <GL/glui/container.h>
#include <assert.h>
#include <string.h>

using namespace GLUI;

/////////////////////////////////////////////////////////////////
class EventCounter : public Control
{
    public :
        int count;
        int bad_count;
        int WaitedEvent;
        void draw() {};
        EventCounter(char* name);
        virtual int AddEvent (::XEvent* event);
};

EventCounter::EventCounter(char* name) : Control (name)
{
    count = 0;
    bad_count = 0;
    WaitedEvent = 0;
}


int EventCounter::AddEvent(::XEvent* event)
{
    if (event->type == WaitedEvent)
      {
        count ++;
      }
    else
      {
        bad_count ++;
      }
}


///////////////////////////////////////////////////////////////
class DoNotForward : public Container
{
    public :
    DoNotForward(char* name) : Container(name)
         { DoNotPropagateMask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask; }
    void draw() {}
};

class DoForward : public Container
{
    public :
    DoForward(char* name) : Container(name)
    { DoNotPropagateMask = 0; }
    void draw() {}
};


void fillEventStruct(Control* theCtrl, ::XKeyEvent* theEvent)
{
    theEvent->x = theCtrl->X() + theCtrl->Width() / 2;
    theEvent->y = theCtrl->Y() + theCtrl->Height() / 2;
}

//////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{


    NCRC_AutoPtr<DoForward> root = new DoForward("root");
    DoNotForward* branch1 = new DoNotForward("branch1");
    DoForward* branch2 = new DoForward("branch2");
    EventCounter* leefb1 = new EventCounter("leefb1");
    EventCounter* leef1b2 = new EventCounter("leef1b2");
    EventCounter* leef2b2 = new EventCounter("leef2b2");


    root->add_control(branch1);
    root->add_control(branch2);

    branch1->add_control(leefb1);

    branch2->add_control(leef1b2);
    branch2->add_control(leef2b2);

    leefb1->set_size(Control::Size(10u,20u));  //position 0x 0y size 10x 20y
    leefb1->WaitedEvent = KeyPress;
    leef1b2->set_size(Control::Size(10u,30u)); //position 0x 20y size 10 30
    leef2b2->set_size(Control::Size(10u,10u)); //position 0x 50y size 10 10
    leef2b2->WaitedEvent = KeyPress;

    ::XKeyEvent keyevent;
    ::memset(&keyevent,0, sizeof(keyevent));
    keyevent.type= KeyPress;

    // try to send a event to some widget that is masked if we get something then error
    fillEventStruct(leefb1, &keyevent);
    root->AddEvent((::XEvent*) & keyevent);
    assert( leefb1->count == 0 && leefb1->bad_count == 0 );
    // try to send an event to some widget that shall refuse all events
    fillEventStruct(leef1b2, &keyevent);
    root->AddEvent((::XEvent*) & keyevent);
    assert( leef1b2->count == 0 && leef1b2->bad_count == 1 );
    // try to send an event to some widget that shall accept it
    fillEventStruct(leef2b2, &keyevent);
    root->AddEvent((::XEvent*) & keyevent);
    assert( leef2b2->count == 1 && leef2b2->bad_count == 0 );
    root = NULL; //will delete everything recursively bellow it

}
