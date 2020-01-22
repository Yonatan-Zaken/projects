#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h> /* size_t */

typedef struct Hash hash_t;

typedef size_t (*hash_func_t)(const void *data);
typedef int (*action_func_t)(void *data1, void *data2);
typedef int (*match_func_t)(void *data1, void *data2);

/*
*   Returns a pointer to the HASH data structure
*	Complexity of malloc     
*/
hash_t *HashCreate(size_t table_size, hash_func_t hash_func, match_func_t is_match);

/*
*	Destroys the HASH Table and frees it from the memory 
*	Complexity o(n) * free                            
*/
void HashDestroy(hash_t *hash_table);

/*
*	Gets a pointer to the Hash Table and inserts the new data into it.  
*	Return 0 for success, otherwise: 1
*	Complexity of O(1)                            
*/
int HashInsert(hash_t *hash_table, void *data);

/*
*	Gets a pointer to the Hash Table and removes the data given 
*	Complexity: O(1)
*/

void HashRemove(hash_t *hash_table, const void *data);

/*	given a pointer to the data searched and the hash table.
*	Complexity: O(1),
*/

void *HashFind(const hash_t *hash_table, const void *data);

/*
*	Gets the hash tableand a action function pointer to operate on the elements in the table
*	Returns 0 for success, otherwise: non-zero value
*	Complexity: worst-case: O(n) 
*/

int HashForeach(hash_t *hash_table, action_func_t action, void *param);

/*
*	Gets a pointer to the table
*	Returns the amount of elements
*	complexity: O(n)                  
*/
size_t HashSize(const hash_t *hash_table);

/*
*	Gets a pointer to the table
*	Returns 1 if empty, otherwise: 0
*	Complexity: O(1)
*/
int HashIsEmpty(const hash_t *hash_table);

#endif
