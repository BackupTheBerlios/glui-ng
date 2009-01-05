#include <GL/glui/container.h>
#include <assert.h>
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

    assert( leefb1.X() == 0 && leefb1.Y() == 0 );
    assert( leef1b2.X() == 0 && leef1b2.Y() == 0 );
    assert( leef2b2.X() == 0 && leef2b2.Y() == leef1b2.Height() );

    int x, y;
    branch1.GetAbsPosition(&branch1, &x, &y);
    assert( x==0 && y==0);
    branch2.GetAbsPosition(&branch2, &x, &y);
    assert( x==0 && y==branch1.Height());
    leefb1.GetAbsPosition(&leefb1, &x, &y);
    assert( x==0 && y==0);
    leef1b2.GetAbsPosition(&leef1b2, &x, &y);
    assert( x==0 && y==branch1.Height());
    leef2b2.GetAbsPosition(&leef2b2, &x, &y);
    assert( x==0 && y==branch1.Height() + leef1b2.Height());

}
