/*******************************
    Yonatan Zaken
    Configuration Base
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_CONFIGURATIONBASE_HPP
#define ILRD_RD8081_CONFIGURATIONBASE_HPP

#include <string>   // std::string

#include "utility.hpp"  // noexcept

namespace ilrd
{

class ConfigurationBase
{
public:	
    //explicit Configuration() = default;
    //Configuration(const Configuration& other) default;
    //Configuration& operator=(const Configuration& other) = default;	
    ~ConfigurationBase() noexcept {}
    virtual std::string Get(std::string key) = 0;
};

} // namespace ilrd

#endif // ILRD_RD8081_CONFIGURATIONBASE_HPP
