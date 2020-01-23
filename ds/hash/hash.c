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
#include <assert.h> /* assert */

#include "dllist.h"
#include "hash.h"

struct Hash
{
    size_t table_size;
    match_func_t is_match;
    hash_func_t hash_func;
    dll_t *table[1];
};

static hash_t *InitTable(hash_t * hash)
{
    int i = 0;
    size_t size = hash->table_size;
    
    for (i = 0; i < size; ++i)
    {
        (hash->table[i]) = DLLCreate();
        if (NULL == hash->table[i])
        {
            for (; i >= 0; --i)
            {
                free(hash->table[i]); hash->table[i] = NULL;
            }
            return NULL;
        }
    }
    return hash;
}

hash_t *HashCreate(size_t table_size, hash_func_t hash_func, match_func_t is_match)
{
    hash_t *hash = (hash_t*)malloc(offsetof(hash_t, table) + table_size 
                                                     * sizeof(dll_t*));
    if (NULL != hash)
    {
        hash->table_size = table_size;
        hash->is_match = is_match;
        hash->hash_func = hash_func;
        if (NULL == InitTable(hash))
        {
            free(hash); hash = NULL;
            return hash;
        }
    }
    return hash;
}
 
void HashDestroy(hash_t *hash_table)
{
    size_t i = 0;
    size_t size = hash_table->table_size;
    
    for (i = 0; i < size; ++i)
    {
        DLLDestroy(hash_table->table[i]);
    }
    free(hash_table); hash_table = NULL;
}

int HashInsert(hash_t *hash_table, void *data)
{
    size_t key = 0;
    
    assert(NULL != hash_table);
    
    key = hash_table->hash_func(data) % hash_table->table_size;
    
    return (DLLEnd(hash_table->table[key]) ==
            DLLPushBack(hash_table->table[key], data));
}

void HashRemove(hash_t *hash_table, const void *data)
{
    size_t key = 0;
    
    assert(NULL != hash_table);
    
    key = hash_table->hash_func(data) % hash_table->table_size;
    
    DLLRemove(DLLFind(DLLBegin(hash_table->table[key]), 
                       DLLEnd(hash_table->table[key]),
                       hash_table->is_match, (void*)data));
}

void *HashFind(const hash_t *hash_table, const void *data)
{
    size_t key = 0;
    iterator_t holder = NULL;
    
    assert(NULL != hash_table);
    
    key = hash_table->hash_func(data) % hash_table->table_size;
    
    if (DLLEnd(hash_table->table[key]) != (holder = 
                                           DLLFind(DLLBegin(hash_table->table[key]), 
                                           DLLEnd(hash_table->table[key]),
                                           hash_table->is_match, (void*)data)))
    
    {
        DLLRemove(holder);
        return DLLGetData(DLLPushFront(hash_table->table[key], (void*)data));
    }                                           
    
    return NULL;
}

int HashForeach(hash_t *hash_table, action_func_t action, void *param)
{
    size_t size = 0;
    size_t i = 0;
    int result = 0;
    
    assert(NULL != hash_table);
    
    size = hash_table->table_size;
    
    for (i = 0; i < size; ++i)
    {
        if (0 != (result = DLLForEach(DLLBegin(hash_table->table[i]), 
                           DLLEnd(hash_table->table[i]),
                           action, param)))
        {
            return result;
        }    
    }
       
    return result;   
}

size_t HashSize(const hash_t *hash_table)
{
    size_t total_size = 0;
    size_t i = 0;
    
    assert(NULL != hash_table);
    
    for (i = 0; i < hash_table->table_size ; ++i)
    {
        total_size += DLLSize(hash_table->table[i]);
    }
    
    return total_size;
}

int HashIsEmpty(const hash_t *hash_table)
{
    size_t i = 0;
    size_t size = hash_table->table_size;
    
    assert(NULL != hash_table);
    
    for (i = 0; i < size; ++i)
    {
        if (!DLLIsEmpty(hash_table->table[i++]))
        {
            return 0; 
        }            
    }
    return 1;        
}
