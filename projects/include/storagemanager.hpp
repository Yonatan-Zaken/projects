/*****************************
    Storage Manager
    HPP File
    24/06/2020
    ILRD - RD8081               
****************************/
#ifndef ILRD_RD8081_STORAGEMANAGER_HPP
#define ILRD_RD8081_STORAGEMANAGER_HPP

#include <vector>
#include <map>
#include <utility>

#include "utility.hpp"
#include "configuration_base.hpp"

namespace ilrd
{

struct Raid
{
    int m_minionIndex;
    uint64_t m_minionBlockIndex;
};

struct MinionInfo
{
    const char *m_minionIp;
    const char *m_minionPort;
};

class StripingManager
{
public:
    explicit StripingManager();
    std::pair<int, int> GetNext();
private:
    int m_currentMinion;
};

class StorageManager
{
public:	
    explicit StorageManager(ConfigurationBase *config);	
    // StorageManager(const StorageManager& other) = default;	
    // StorageManager& operator=(const StorageManager& other) = default;	
    ~StorageManager() noexcept;

    std::pair<MinionInfo, MinionInfo> GetNextMinions();
    void Add();

private:
    std::vector<MinionInfo> m_minionList;
    std::map<uint64_t, std::pair<Raid, Raid> > m_raidInfo;
    StripingManager m_striper;
};

} // namespace ilrd

# endif // ILRD_RD8081_STORAGEMANAGER_HPP
