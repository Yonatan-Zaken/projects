/*********************
    Future Task
    Header File
    27/05/2020
    ILRD - RD8081               
*********************/

#ifndef ILRD_RD8081_FUTURE_TASK_HPP
#define ILRD_RD8081_FUTURE_TASK_HPP

#include "thread_pool.hpp" // Task

namespace ilrd
{

template <class VALUE>
// VALUE must be dufault contructable, copy constructable, and copy assignable
class FutureTask: public ThreadPool::Task
{
public:
    // explicit FutureTask() = default;
    // virtual ~FutureTask() noexcept = default;

    virtual void TaskFunc() = 0;
    // TaskFunc must beimplemented with the function the task should do

    void Run(); 
    bool IsFinished() const;
    VALUE GetValue();
    VALUE Wait();

private:
    VALUE m_value;
};

} // namespace ilrd

#endif // ILRD_RD8081_FUTURE_TASK_HPP

