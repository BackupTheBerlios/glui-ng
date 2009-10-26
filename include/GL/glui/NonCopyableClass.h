namespace GLUI
{
        class NonCopyableClass
        {
                public :
                        NonCopyableClass() {}
                private :
                        NonCopyableClass(NonCopyableClass const& copy) {};
                        virtual NonCopyableClass& operator= (const NonCopyableClass& n) throw() {return *this;};
        };
}
