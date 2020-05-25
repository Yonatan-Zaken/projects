/*********************
    Task
    Header File
    24/05/2020
    ILRD - RD8081               
*********************/

#include "utility.hpp"

namespace ilrd
{

class Task
{
public:
    //explicit Task() = default;
    virtual ~Task() noexcept;
    //Task(const Task&) = default;
    //Task& operator=(const Task&) = default;
    
    virtual void Run() = 0;
};


} // namespace ilrd

