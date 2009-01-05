#include <GL/glui/container.h>
#include <assert.h>
using namespace GLUI;
using namespace std;
#include <algorithm>


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

    assert(leefb1.Width() == 10 + leefb1.XOffLeft() + leefb1.XOffRight());
    assert(leefb1.Height() == 20 + leefb1.YOffTop() + leefb1.YOffBot());

    assert(leef1b2.Width() == 10 + leef1b2.XOffLeft() + leef1b2.XOffRight());
    assert(leef1b2.Height() == 30 + leef1b2.YOffTop() + leef1b2.YOffBot());

    assert(leef2b2.Width() == 10 + leef2b2.XOffLeft() + leef2b2.XOffRight());
    assert(leef2b2.Height() == 10 + leef2b2.YOffTop() + leef2b2.YOffBot());

    //vertical orientation

    assert(branch1.Width() == leefb1.Width() + branch1.XOffLeft() + branch1.XOffRight());
    assert(branch1.Height() == leefb1.Height() + branch1.YOffTop() + branch1.YOffBot());

    assert(branch2.Width() == max<int>(leef1b2.Width(), leef2b2.Width()) + branch2.XOffLeft() + branch2.XOffRight());
    assert(branch2.Height() == leef1b2.Height() + leef2b2.Height() + branch2.YOffTop() + branch2.YOffBot());

    assert(root.Width() == max<int>(branch1.Width(), branch2.Width()) + root.XOffLeft() + root.XOffRight());
    assert(root.Height() == branch1.Height() + branch2.Height() + root.YOffTop() + root.YOffBot());

    //horizontal orientation
    root.set_orientation(Container::horizontal);

    assert(branch1.Width() == leefb1.Width() + branch1.XOffLeft() + branch1.XOffRight());
    assert(branch1.Height() == leefb1.Height() + branch1.YOffTop() + branch1.YOffBot());

    assert(branch2.Width() == max<int>(leef1b2.Width(), leef2b2.Width()) + branch2.XOffLeft() + branch2.XOffRight());
    assert(branch2.Height() == leef1b2.Height() + leef2b2.Height() + branch2.YOffTop() + branch2.YOffBot());

    assert(root.Width() == branch1.Width() + branch2.Width() + root.XOffLeft() + root.XOffRight());
    assert(root.Height() ==  max<int>(branch1.Height(), branch2.Height()) + root.YOffTop() + root.YOffBot());

    return 0;
}
