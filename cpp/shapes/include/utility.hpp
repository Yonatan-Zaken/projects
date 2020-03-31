#ifndef ILRD_RD8081_UTILITY_HPP
#define ILRD_RD8081_UTILITY_HPP

#if __cplusplus<201104
#define noexcept throw()
#endif

namespace ilrd
{

class Uncopyable
{
protected:
    Uncopyable() {}
    ~Uncopyable() {}
    
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};
} // namespace ilrd

#endif // ILRD_RD8081_UTILITY_HPP

