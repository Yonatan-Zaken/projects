/*******************************
    Yonatan Zaken
    Plugin Manager
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_PLUGIN_MANAGER_HPP
#define ILRD_RD8081_PLUGIN_MANAGER_HPP

#include <map> // std::map
#include <stdexcept> // std::runtime_error

#include "utility.hpp"  // noexcept
#include "framework.hpp" // Framework&
#include "plugin.hpp" // Plugin

namespace ilrd
{

class PluginManager : private Uncopyable
{
public:
    typedef boost::shared_ptr<Plugin> plugin_t;

    explicit PluginManager(const char *pluginPath, Framework& framework);
    //~PluginManager() noexcept = default;

    void Add(std::string pluginName, plugin_t plugin);
    void Remove(std::string pluginName);

private:
    typedef std::map<std::string, plugin_t> pluginList_t;
    typedef std::pair<std::string, plugin_t> pluginElement_t;

    Framework& m_framework;
    pluginList_t pluginList;
};

} // namespace ilrd

#endif // ILRD_RD8081_PLUGIN_MANAGER_HPP



