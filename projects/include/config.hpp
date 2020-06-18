/*******************************
    Yonatan Zaken
    Config
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_CONFIG_HPP
#define ILRD_RD8081_CONFIG_HPP

/**
 * Config Derived Class:
 * Supports data saved in following ENV variables:
 * ILRD_NUM_OF_THREADS
 * ILRD_THREADPOOL_TIMEOUT
 * ILRD_NUM_OF_MINIONS
 * ILRD_MINION_IP
 * ILRD_MINION_PORT
 * ILRD_DIRMONITOR_PATH
 * ILRD_NUMBER_OF_4K_BLOCKS
 * ILRD_NBD_PATH
 */

#include <stdexcept>    //std::invalid_argument

#include "configuration_base.hpp"

namespace ilrd
{

class Config: public ConfigurationBase
{
public:
    //explicit Config() = default;
    //Config(const Config& other) default;
    //Config& operator=(const Config& other) = default;	
    //~Config() noexcept = default;
    std::string Get(std::string key);

    class ConfigError: public std::invalid_argument
    {
    public:
        explicit ConfigError(const char *message);
    };
};

} // namespace ilrd


#endif // ILRD_RD8081_CONFIG_HPP