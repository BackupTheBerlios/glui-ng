#include <GL/glui/container.h>
#include <assert.h>
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


//////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    DoForward root("root");
    DoNotForward branch1("branch1");
    DoForward branch2("branch2");
    EventCounter leefb1("leefb1");
    EventCounter leef1b2("leef1b2");
    EventCounter leef2b2("leef2b2");

    root.add_control(&branch1);
    root.add_control(&branch2);

    branch1.add_control(&leefb1);

    branch2.add_control(&leef1b2);
    branch2.add_control(&leef2b2);

    leefb1.set_size(Control::Size(10,20));  //position 0x 0y size 10x 20y
    leefb1.WaitedEvent = KeyPress;
    leef1b2.set_size(Control::Size(10,30)); //position 0x 20y size 10 30
    leef2b2.set_size(Control::Size(10,10)); //position 0x 50y size 10 10
    leef2b2.WaitedEvent = KeyPress;

    ::XKeyEvent keyevent;
    keyevent.type= KeyPress;
    keyevent.x = 5;
    keyevent.y = 10;

    int step = 1;

    // try to send a event to some widget that is masked if we get something then error
    root.AddEvent((::XEvent*) & keyevent);
    assert( leefb1.count == 0 && leefb1.bad_count == 0 );
    // try to send an event to some widget that shall refuse all events
    keyevent.y = branch1.Height() + leef1b2.Height()/2;
    root.AddEvent((::XEvent*) & keyevent);
    assert( leef1b2.count == 0 && leef1b2.bad_count == 1 );
    // try to send an event to some widget that shall accept it
    keyevent.y = branch1.Height() + leef1b2.Height() + leef2b2.Height()/2;
    root.AddEvent((::XEvent*) & keyevent);
    assert( leef2b2.count == 1 && leef2b2.bad_count == 0 );
}
