/*******************************
    Yonatan Zaken
    Config
    CPP
    ILRD - RD8081               
*******************************/
#include <cstdlib>  // getenv
#include <string>   // std::string

#include "config.hpp"

namespace ilrd
{

std::string Config::Get(std::string key)
{
    const char *config = getenv(key.c_str());
    if(config)
    {
        return config;
    }

    throw ConfigError("invalid key argument in env variable");
}

/******************************************************************************/

Config::ConfigError::ConfigError(const char *message):
    std::invalid_argument(message)
{
}

} // namespace ilrd


