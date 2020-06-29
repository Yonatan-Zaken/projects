/*****************************
    Storage Manager
    CPP File
    24/06/2020
    ILRD - RD8081               
****************************/
#include "storagemanager.hpp"

namespace ilrd
{


StorageManager::StorageManager(ConfigurationBase *config)
{

    config->Get("ILRD_MINION_IP"), config->Get("ILRD_MINION_PORT");

}

StorageManager::~StorageManager() noexcept
{

}



} // namespace ilrd

