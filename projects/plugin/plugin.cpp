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
    std::cout << "filename dlopen: " << fileName << "\n";
    if (nullptr == (handle = dlopen(fileName, flags)))
    {
        throw OpenError("fail to dlopen");
    }

    return handle;
}

void SharedObject::DLClose()
{
    if (0 != dlclose(m_objectHandle))
    {
        // logger
    }
}

/**************************** Plugin Definitions ******************************/

Plugin::Plugin(Framework& framework, const char *soFileName):
    m_framework(framework),
    m_sharedObject(soFileName, RTLD_NOW),
    m_initPlugin(m_sharedObject.GetFunc<void(*)(Framework&)>("InitPlugin")),
    m_removePlugin(m_sharedObject.GetFunc<void(*)(Framework&)>("RemovePlugin"))
{
    InitPlugin();
}

Plugin::~Plugin() noexcept
{
}

void Plugin::InitPlugin()
{
    m_initPlugin(m_framework);
}

void Plugin::RemovePlugin()
{
    m_removePlugin(m_framework);
}

} // namespace ilrd


