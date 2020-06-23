/*******************************
    Yonatan Zaken
    Dir Monitor
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_DIRMONITOR_HPP
#define ILRD_RD8081_DIRMONITOR_HPP

#include <string>           // std::string
#include <sys/inotify.h>    // inotify_init
#include <linux/limits.h>   // NAME_MAX

#include "reactor.hpp"
#include "dispatcher.hpp"
#include "inotify.hpp"

namespace ilrd
{

struct InotifyEvent
{
public:
    //explicit InotifyEvent(const char *buffer);
    enum IdentifedOP
    {
        CREATE,
        DELETE
    };

    std::string name;
    //char name[NAME_MAX];
    IdentifedOP operation;
};

class DirMonitor: public Dispatcher<ObserverBase<InotifyEvent>, InotifyEvent>
{
public:	
    explicit DirMonitor(Reactor& reactor, const char *pathname);
    //DirMonitor(const DirMonitor& other) = default;
    //DirMonitor& operator=(const DirMonitor& other) = default;
    ~DirMonitor() noexcept;

    void Callback();

    class DirMonitorError: std::logic_error
    {
    public:
        explicit DirMonitorError(const char *message);
    };

private:
    Reactor& m_reactor;
    Inotify m_inotify;
    InotifyEvent m_event;

    void InitEventInfo(const struct inotify_event *event);
    void ReadEvent(char *buffer);
};

} // namespace ilrd

#endif // ILRD_RD8081_DIRMONITOR_HPP

