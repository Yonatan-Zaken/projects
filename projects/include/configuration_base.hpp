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

template <class KEY, class VALUE>
class ConfigurationBase
{
public:	
    //explicit Configuration() = default;
    //Configuration(const Configuration& other) default;
    //Configuration& operator=(const Configuration& other) = default;	
    ~ConfigurationBase() noexcept {}
    virtual VALUE Get(KEY key) = 0;
};

} // namespace ilrd

#endif // ILRD_RD8081_CONFIGURATIONBASE_HPP
