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

template <class FUNC_PTR>
FUNC_PTR SharedObject::GetFunc(const char *funcName)
{
    void *symbol;
    if (nullptr == (symbol = dlsym(m_objectHandle, funcName)))
    {
        throw OpenError("fail to dlsym");
    }

    return static_cast<FUNC_PTR>(symbol);
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

Plugin::Plugin(Framework& framework, const char *soFileName):
    m_framework(framework),
    m_sharedObject(soFileName, RTLD_LAZY),
    m_initPlugin(m_sharedObject.GetFunc("InitPlugin")),
    m_removePlugin(m_sharedObject.GetFunc("RemovePlugin"))
{
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


