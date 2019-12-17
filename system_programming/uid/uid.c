/*********************************/
/*   			             	 */
/*   System Programming          */
/*   UID                         */
/*   Author: Yonatan Zaken       */
/*   Last Updated 15/12/19       */
/*   Reviewed by: Guy            */   
/*			                   	 */
/*********************************/

#include <stdlib.h>

#include "uid.h"

ilrd_uid_t UIDCreate()
{
    ilrd_uid_t new_uid;
    static size_t counter = 0;
    
    new_uid.time_stamp = time(NULL);
    new_uid.pid = getpid();
    new_uid.counter = ++counter;
    
    return new_uid;
}

int UIDIsBad(ilrd_uid_t uid)
{
    return (0 == uid.time_stamp);
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
    return ((uid1.time_stamp == uid1.time_stamp) &&
            (uid1.counter == uid2.counter) &&
            (uid1.pid == uid2.pid));
}
