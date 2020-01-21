/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Hash Table                  */
/*   Author: Yonatan Zaken       */
/*   Last Updated 21/1/20        */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/
#include <stdlib.h> /* malloc */

#include "dllist.h"
#include "hash.h"

struct Hash
{
    size_t table_size;
    match_func_t is_match;
    hash_func_t hash_func;
    dll_t *table[1];
};

hash_t *HashCreate(size_t table_size, hash_func_t hash_func, action_func_t is_match)
{
            

}

void HashDestroy(hash_t *hash_table)
{

}

int HashInsert(hash_t *hash_table, void *data)
{

}

void HashRemove(hash_t *hash_table, const void *data)
{

}

void *HashFind(const hash_t *hash_table, const void *data)
{

}

int HashForeach(hash_t *hash_table, action_func_t action, void *param)
{

}

size_t HashSize(const hash_t *hash_table)
{

}

int HashIsEmpty(const hash_t *hash_table)
{

}
