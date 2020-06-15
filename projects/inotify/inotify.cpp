
/*******************************
    Yonatan Zaken
    Inotify
    CPP
    ILRD - RD8081               
*******************************/

#include <unistd.h>         // close
#include <sys/inotify.h>    // inotify_init

#include "inotify.hpp"

namespace ilrd
{

Inotify::Inotify(const char *path):
    m_inotifyFD(InotifyInit())
{
    if (-1 == inotify_add_watch(m_inotifyFD, path, IN_CREATE | IN_DELETE))
    {
        throw InotifyError("inotify fail to add watch");
    }
}

/******************************************************************************/

Inotify::~Inotify() noexcept
{
    close(m_inotifyFD);
}

/******************************************************************************/

int Inotify::InotifyInit()
{
    int fd;
    if (-1 == (fd = inotify_init()))
    {
        throw InotifyError("inotify fail to init");
    }
    
    return fd;
}

/************************** Exception Definitions *****************************/

Inotify::InotifyError::InotifyError(const char *message):
    std::logic_error(message)
{
}

} // namespace ilrd
