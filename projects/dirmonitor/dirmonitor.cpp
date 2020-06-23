/*******************************
    Yonatan Zaken
    Dir Monitor
    CPP
    ILRD - RD8081               
*******************************/

#include <sys/inotify.h>    // inotify_init
#include <boost/bind.hpp>

#include "dirmonitor.hpp"

namespace ilrd
{

/*************************** Dir Monitor Definitions **************************/

DirMonitor::DirMonitor(Reactor& reactor, const char *pathname):
    m_reactor(reactor),
    m_inotify(pathname),
    m_event()
{
    m_reactor.InsertFD(m_inotify.GetFD(), FDListener::READ, boost::bind(&DirMonitor::Callback, this));
}

/******************************************************************************/

DirMonitor::~DirMonitor() noexcept
{
}

/******************************************************************************/

void DirMonitor::Callback()
{
    char buffer[sizeof(struct inotify_event) + NAME_MAX + 1];
    ReadEvent(buffer);
    
    const struct inotify_event *event = reinterpret_cast<const struct inotify_event*>(buffer);

    InitEventInfo(event);
    this->Broadcast(m_event);
}

/*************************** Private Definitions ******************************/

void DirMonitor::InitEventInfo(const struct inotify_event *event)
{
    //memcpy(&m_event.name, event->name, event->len + 1);
    m_event.name = event->name;
    if (IN_DELETE == event->mask)
    {
        m_event.operation = InotifyEvent::DELETE;
    }
    
    else
    {
        m_event.operation = InotifyEvent::CREATE;
    }
}

/******************************************************************************/

void DirMonitor::ReadEvent(char *buffer)
{
    if (-1 == read(m_inotify.GetFD(), buffer, sizeof(struct inotify_event) + NAME_MAX + 1))
    {
        throw DirMonitorError("fail to read inotify_event");
    }
}

/************************** Exception Definitions *****************************/

DirMonitor::DirMonitorError::DirMonitorError(const char *message):
    std::logic_error(message)
{
}

} // namespace ilrd


