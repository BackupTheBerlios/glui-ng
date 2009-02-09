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
    branch1.set_orientation(Container::useparent);

    branch2.add_control(&leef1b2);
    branch2.add_control(&leef2b2);
    branch2.set_orientation(Container::useparent);

    leefb1.set_size(Control::Size(10u,20u));
    leef1b2.set_size(Control::Size(10u,30u));
    leef2b2.set_size(Control::Size(10u,10u));

    root.set_orientation(Container::TopDown);
    assert( branch1.X() == root.XOffLeft() && branch1.Y() == (root.Height() - root.YOffTop() - branch1.Height()) );
    assert( branch2.X() == root.XOffLeft() && branch2.Y() == root.YOffBot());
    assert( leefb1.X()  == root.XOffLeft() && leefb1.Y()  == (root.Height() - root.YOffTop() - branch1.YOffTop() - leefb1.Height()));
    assert( leef1b2.X() == root.XOffLeft() && leef1b2.Y() == leef1b2.Height() + root.YOffBot());
    assert( leef2b2.X() == root.XOffLeft() && leef2b2.Y() == root.YOffBot());
    root.set_orientation(Container::BottomUp);
    assert( branch1.X() == 0 && branch1.Y() == 0);
    assert( branch2.X() == 0 && branch2.Y() == branch1.Height());
    assert( leefb1.X()  == 0 && leefb1.Y()  == 0);
    assert( leef1b2.X() == 0 && leef1b2.Y() == branch1.Height());
    assert( leef2b2.X() == 0 && leef2b2.Y() == branch1.Height() + leef1b2.Height());
    root.set_orientation(Container::LeftToRight);
    assert( branch1.X() == 0 && branch1.Y() == 0);
    assert( branch2.X() == 0 && branch2.Y() == branch1.Height());
    assert( leefb1.X()  == 0 && leefb1.Y()  == 0);
    assert( leef1b2.X() == 0 && leef1b2.Y() == branch1.Height());
    assert( leef2b2.X() == 0 && leef2b2.Y() == branch1.Height() + leef1b2.Height());
    root.set_orientation(Container::RightToLeft);
    assert( branch1.X() == 0 && branch1.Y() == 0);
    assert( branch2.X() == 0 && branch2.Y() == branch1.Height());
    assert( leefb1.X()  == 0 && leefb1.Y()  == 0);
    assert( leef1b2.X() == 0 && leef1b2.Y() == branch1.Height());
    assert( leef2b2.X() == 0 && leef2b2.Y() == branch1.Height() + leef1b2.Height());



}
