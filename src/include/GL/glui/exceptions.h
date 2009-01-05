#ifndef __GLUI_EXCEPTIONS_H
#define __GLUI_EXCEPTIONS_H
namespace GLUI
{
    class exception
    {
        public :
            exception(std::string msg, int err);
            std::string errorMsg;
            int errno;
    };

    inline exception::exception(std::string msg, int err)
    {
        errno = err;
        errorMsg = msg;
    }

}

#endif __GLUI_EXCEPTIONS_H
