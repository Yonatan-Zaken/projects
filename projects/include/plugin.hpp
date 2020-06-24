/*******************************
    Yonatan Zaken
    Plugin
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_PLUGIN_HPP
#define ILRD_RD8081_PLUGIN_HPP

#include <dlfcn.h>   // dlsym
#include <stdexcept> // std::runtime_error

#include "utility.hpp"  // noexcept
#include "framework.hpp" // Framework&

namespace ilrd
{

class SharedObject : private Uncopyable
{
public:
    explicit SharedObject(const char *fileName, int flags);
    ~SharedObject() noexcept;

    template <class FUNC_PTR>
    FUNC_PTR GetFunc(const char *funcName);      

    class OpenError : public std::runtime_error
    {
    public:
        explicit OpenError(const char *error) : std::runtime_error(error) {}
    };

private:
    void *m_objectHandle;
    void *DLOpen(const char *fileName, int flags);
    void DLClose();
};

template <class FUNC_PTR>
FUNC_PTR SharedObject::GetFunc(const char *funcName)
{
    std::cout << "funcName dlsym: " << funcName << "\n";
    FUNC_PTR handle;
    if (nullptr == (*(void**)(&handle) = dlsym(m_objectHandle, funcName)))
    {
        throw OpenError("fail to dlsym");
    }

    return handle;
}

/******************************************************************************/

class Plugin : private Uncopyable
{
public:
    explicit Plugin(Framework& framework, const char *soFileName);
    ~Plugin() noexcept;

private:
    typedef void (*pluginFunc_t)(Framework&);

    Framework& m_framework;
    SharedObject m_sharedObject;
    pluginFunc_t m_initPlugin;
    pluginFunc_t m_removePlugin;

    void InitPlugin();
    void RemovePlugin();
};

} // namespace ilrd

#endif // ILRD_RD8081_PLUGIN_HPP



