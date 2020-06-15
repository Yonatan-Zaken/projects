/*******************************
    Yonatan Zaken
    Inotify
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_INOTIFY_HPP
#define ILRD_RD8081_INOTIFY_HPP

#include <stdexcept>

#include "utility.hpp"  // noexcept

namespace ilrd
{

class Inotify
{
public:	
    explicit Inotify(const char *pathname);	
    //Inotify(const Inotify& other) = default;	
    //Inotify& operator=(const Inotify& other) = default;	
    ~Inotify() noexcept;

    inline int GetFD() const noexcept;

    class InotifyError: public std::logic_error
    {
    public:
        explicit InotifyError(const char *message);
    };

private:
    int m_inotifyFD;
    int InotifyInit();
};

inline int Inotify::GetFD() const noexcept
{
    return m_inotifyFD;
}

} // namespace ilrd


#endif
