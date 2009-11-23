#include <GL/glui/NonCopyableClass.h>
using namespace GLUI;

class testNonCopyable : public NonCopyableClass
{
        public :
                int a;
};


int main(int argc, char** argv)
{
        testNonCopyable orig;
        //testNonCopyable cpy = orig;
        testNonCopyable cpy2;
        cpy2 = orig;
}
