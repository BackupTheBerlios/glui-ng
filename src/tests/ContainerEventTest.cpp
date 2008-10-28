#include <GL/glui/container.h>
using namespace GLUI;

/////////////////////////////////////////////////////////////////
class LeefOk : public Control
{
    public :
        LeefOk(char* name) : Control(name) {}
        virtual int AddEvent (::XEvent* event);
        void draw() {};
};

class LeefKo : public Control
{
    public :
        LeefKo(char* name) : Control(name) {}
        virtual int AddEvent (::XEvent* event);
        void draw() {};
};

int LeefOk::AddEvent(::XEvent* event)
{
    if (event->type == KeyPress)
      return 0;
}

int LeefKo::AddEvent(::XEvent* event)
{
    return 1;
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
    LeefKo leefb1("leefb1");
    LeefKo leef1b2("leef1b2");
    LeefOk leef2b2("leef2b2");

    root.add_control(&branch1);
    root.add_control(&branch2);

    branch1.add_control(&leefb1);

    branch2.add_control(&leef1b2);
    branch2.add_control(&leef2b2);

    leefb1.set_size(Control::Size(10,20));  //position 0x 0y size 10x 20y
    leef1b2.set_size(Control::Size(10,30)); //position 0x 20y size 10 30
    leef2b2.set_size(Control::Size(10,10)); //position 0x 50y size 10 10

    ::XKeyEvent keyevent;
    keyevent.type= KeyPress;
    keyevent.x = 5;
    keyevent.y = 10;

    int step = 1;

    // try to send a event to some widget that is masked if we get something then error
    if (root.AddEvent((::XEvent*) & keyevent))
    {
         return -step;
    }
    step++;
    // try to send an event to some widget that shall refuse all events
    keyevent.y = 25;
    if ( root.AddEvent((::XEvent*) & keyevent) != 1 )
    {
        return -step;
    }
    // try to send an event to some widget that shall accept it
    keyevent.y = 55;
    if ( root.AddEvent((::XEvent*) & keyevent) != 0 )
    {
        return -step;
    }

}
