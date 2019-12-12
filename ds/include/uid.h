#ifndef __UID_H__
#define __UID_H__

#include <time.h>
#include <stddef.h>
#include <sys/types.h>

typedef struct Uid ilrd_uid_t;

/*****************************************/
/* Returns pointer to the uid struct     */
/* complexity of malloc                  */
/*****************************************/
ilrd_uid_t UIDCreate();

/*****************************************/
/* Returns 1 if the struct is bad        */
/* (not valid) or 0 if not               */
/* complexity of strcmp                  */
/*****************************************/
int UIDIsBad(ilrd_uid_t);

/*****************************************/
/* Returns 1 if the structs are same     */
/* or 0 if not                           */
/* complexity of strcmp                  */
/*****************************************/
int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);

#endif
