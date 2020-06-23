/*******************************
    Yonatan Zaken
    Plugin
    CPP
    ILRD - RD8081               
*******************************/

#include <dlfcn.h>  // dlopen

#include "plugin.hpp"

namespace ilrd
{

/************************* SharedObject Definitions ***************************/

SharedObject::SharedObject(const char *fileName, int flags):
    m_objectHandle(DLOpen(fileName, flags))
{
}

SharedObject::~SharedObject() noexcept
{
    DLClose();
}

/**************************** Private Definitions *****************************/

void *SharedObject::DLOpen(const char *fileName, int flags)
{
    void *handle;
    if (nullptr == (handle = dlopen(fileName, flags)))
    {
        throw OpenError("fail to dlopen");
    }

    return handle;
}

void SharedObject::DLClose()
{
    if (nullptr == dlclose(m_objectHandle))
    {
        // logger
    }
}

/**************************** Plugin Definitions ******************************/

Plugin()
{

}

Plugin(const Plugin& other)
{

}

Plugin& operator=(const Plugin& other)
{

}

~Plugin()
{

}

} // namespace ilrd


