/*******************************
    Yonatan Zaken
    File Name
    File Type
    //
    ILRD - RD8081               
*******************************/
#include "plugin_manager.hpp"

namespace ilrd
{

PluginManager::PluginManager(const char *pluginPath, Framework& framework):
    m_framework(framework)
{
}

void PluginManager::Add(std::string pluginName, plugin_t plugin)
{
    pluginList[pluginName] = plugin;
}

void PluginManager::Remove(std::string pluginName)
{
    pluginList_t::iterator it = pluginList.find(pluginName);
    if (it == pluginList.end())
    {
        throw PluginManager("invalid key for remove from map");
    }
    
    pluginList.erase(it);
}

} // namespace ilrd


