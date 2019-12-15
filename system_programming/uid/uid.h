#ifndef __UID_H__
#define __UID_H__

#include <time.h>
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct Uid ilrd_uid_t;

/*****************************************/
/* Returns the uid struct                */
/* complexity of O(1)                    */
/*****************************************/
ilrd_uid_t UIDCreate();

/*****************************************/
/* Returns 1 if the struct is bad        */
/* (not valid) or 0 if not               */
/* complexity of O(1)                    */
/*****************************************/
int UIDIsBad(ilrd_uid_t uid);

/*****************************************/
/* Returns 1 if the structs are same     */
/* or 0 if not                           */
/* complexity of O(1)                    */
/*****************************************/
int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);

#endif
