#include <GL/glui/container.h>
#include <assert.h>
using namespace GLUI;

/////////////////////////////////////////////////////////////////
class LeefOk : public Control
{
    public :
        LeefOk(char* name) : Control(name) {}
        virtual int AddEvent (::XEvent* event);
};

class LeefKo : public Control
{
    public :
        LeefKo(char* name) : Control(name) {}
        virtual int AddEvent (::XEvent* event);
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
};


class DoForward : public Container
{
    public :
    DoForward(char* name) : Container(name)
    { DoNotPropagateMask = 0; }
};



//////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    DoForward* root = new DoForward("root");
    DoNotForward* branch1 = new DoNotForward("branch1");
    DoForward* branch2 = new DoForward("branch2");
    LeefKo* leefb1 = new LeefKo("leefb1");
    LeefKo* leef1b2 = new LeefKo("leef1b2");
    LeefOk* leef2b2 = new LeefOk("leef2b2");

    root->add_control(branch1);
    root->add_control(branch2);

    branch1->add_control(leefb1);
    branch1->set_orientation(Container::useparent);

    branch2->add_control(leef1b2);
    branch2->add_control(leef2b2);
    branch2->set_orientation(Container::useparent);

    leefb1->set_size(Control::Size(10u,20u));
    leef1b2->set_size(Control::Size(10u,30u));
    leef2b2->set_size(Control::Size(10u,10u));

    root->set_orientation(Container::TopDown);
    assert( branch1->X() == (root->XOffLeft()) );
    assert( branch1->Y() == (root->Height() - root->YOffTop() - branch1->Height()) );
    assert( branch2->X() == (root->XOffLeft()) );
    assert(  branch2->Y() == (root->YOffBot()) );
    assert( leefb1->X()  == (branch1->X() + branch1->XOffLeft()) );
    assert( leefb1->Y()  == (branch1->Y() + branch1->YOffBot()) );
    assert( leef1b2->X() == (branch2->X() + branch2->XOffLeft()) );
    assert( leef1b2->Y() == (leef2b2->Height() + branch2->Y() +  branch2->YOffBot()) );
    assert( leef2b2->X() == (branch2->X() + branch2->XOffLeft()) );
    assert( leef2b2->Y() == (branch2->Y() + branch2->YOffBot()) );

    root->set_orientation(Container::BottomUp);
    assert( branch1->X() == (root->XOffLeft()) );
    assert( branch1->Y() == (root->YOffBot()) );
    assert( branch2->X() == (root->XOffLeft()) );
    assert( branch2->Y() == (root->YOffBot() + branch1->Height()) );
    assert( leefb1->X()  == (branch1->X() + branch1->XOffLeft()) );
    assert( leefb1->Y()  == (branch1->Y() + branch1->YOffBot()) );
    assert( leef1b2->X() == (branch2->X() + branch2->XOffLeft()) );
    assert( leef1b2->Y() == (branch2->Y() + branch2->YOffBot()) );
    assert( leef2b2->X() == (branch2->X() + branch2->XOffLeft()) );
    assert( leef2b2->Y() == (leef1b2->Y() + leef1b2->Height()) );

    root->set_orientation(Container::LeftToRight);
    assert( branch1->X() == (root->XOffLeft()) );
    assert( branch1->Y() == root->YOffBot() );
    assert( branch2->X() == (branch1->X() + branch1->Width()) );
    assert( branch2->Y() == (root->YOffBot()) );
    assert( leefb1->X()  == (branch1->X() + branch1->XOffLeft()) );
    assert( leefb1->Y()  == (branch1->Y() + branch1->YOffBot()) );
    assert( leef1b2->X() == (branch2->X() + branch2->XOffLeft()) );
    assert( leef1b2->Y() == (branch2->Y() + branch2->YOffBot()) );
    assert( leef2b2->X() == (leef1b2->X() + leef1b2->Width()) );
    assert( leef2b2->Y() == (branch2->Y() + branch2->YOffBot()) );

    root->set_orientation(Container::RightToLeft);
    assert( branch1->X() == (branch2->X() + branch2->Width()) );
    assert(  branch1->Y() == (root->YOffBot()) );
    assert( branch2->X() == (root->XOffLeft()) );
    assert( branch2->Y() == (root->YOffBot()) );
    assert( leefb1->X()  == (branch1->X() + branch1->XOffLeft()) );
    assert( leefb1->Y()  == (branch1->Y() + branch1->YOffBot()) );
    assert( leef1b2->X() == (leef2b2->X() + leef2b2->Width()) );
    assert( leef1b2->Y() == (branch2->Y() + branch2->YOffBot()) );
    assert( leef2b2->X() == (branch2->X() + branch2->XOffLeft()) );
    assert( leef2b2->Y() == (branch2->Y() + branch2->YOffBot()) );

    delete root; //will delete everything recursively bellow it

}
