/*******************************
    Yonatan Zaken
    File Name
    File Type
    //
    ILRD - RD8081               
*******************************/

#include "utility.hpp"

extern "C" 
{
    #include "wd.h"
}

namespace ilrd
{

class Watchdog: private Uncopyable
{

public:
    explicit Watchdog();
    //~Watchdog(); = default
	void Start();
	void Stop();
private:
    wd_t *m_wd;
    status_t m_status;
};

Watchdog::Watchdog(): 
    m_wd(NULL),
    m_status(SUCCESS)
{
}

void Watchdog::Start()
{
    m_wd = WDStart(	
        "/home/yonatan10/yonatan-zaken/cpp/scopeguard/outdebug/scopeguard", &m_status);
}

void Watchdog::Stop()
{
    WDStop(m_wd);
}

} // namespace ilrd

