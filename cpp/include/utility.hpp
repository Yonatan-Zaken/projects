#ifndef ILRD_RD8081_UTILITY_HPP
#define ILRD_RD8081_UTILITY_HPP

#if __cplusplus<201104 
#define noexcept throw()
#else
#define NULL nullptr  
#endif


#define HORIZONTAL_TAB 9
#define UNUSED(x) (void)(x)
/*
enum Status 
{
    SUCCESS,
    FAIL
};
*/
namespace ilrd
{

// Implementation of Uncopyable class to 
// disable copy/assignment constructors
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

