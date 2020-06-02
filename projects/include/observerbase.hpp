/*********************
    Observer Base
    Header File
    01/06/2020
    ILRD - RD8081           
*********************/

#ifndef ILRD_RD8081_OBSERVERBASE_HPP
#define ILRD_RD8081_OBSERVERBASE_HPP

namespace ilrd
{

template <class PARAM>
class ObserverBase : private Uncopyable
{
public:
    //explicit Observer() = default;
    virtual ~Observer() noexcept {}
    //Observer(const Observer& other) = default;
    //Observer& operator=(const Observer& rhs) = default;

    virtual void Update(PARAM) = 0;
    virtual void UpdateDeath() = 0;
};

} // namespace ilrd

#endif // ILRD_RD8081_OBSERVERBASE_HPP