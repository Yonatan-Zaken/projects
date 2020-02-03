#ifndef __TRIE_H__
#define __TRIE_H__

#include <stddef.h> /* size_t */

typedef enum Status
{
    SUCCESS,
    FAIL
} status_t;

typedef enum Bool
{
    FALSE,
    TRUE
} bool_t;

typedef struct Trie trie_t;

/*
* TrieCreate() - 
* Returns pointer to the Trie, will return NULL if failed. 
* complexity of malloc();       
*/
trie_t *TrieCreate(size_t height);

/*
* TrieDetroy() -
* Destroys and frees Trie from memory.
* undefined behaviour for @trie NULL pointer
* complexity: free();                  
*/
void TrieDestroy(trie_t *trie);

/*
* TrieInsert() -
* Inserts a new trie element.
* undefined behaviour for @trie NULL pointer
* complexity: malloc();                  
*/
status_t TrieInsert(trie_t *trie, unsigned char *data);

/*
* TrieIsEmpty() -
* Checks if the trie is empty.
* undefined behaviour for @trie NULL pointer
* return value:
    -TRUE
    -FALSE
* complexity: O(1);                  
*/
bool_t TrieIsEmpty(const trie_t *trie);

/*
* TrieCountLeafs() -
* Counts the number of occupied leafs in the trie.
* undefined behaviour for @trie NULL pointer
* complexity: O(n);                  
*/
size_t TrieCountLeafs(const trie_t *trie);

/*
* TrieIsAvailable() -
* checks if the path referenced by data is available
* undefined behaviour for @trie NULL pointer
* complexity: O(n);                  
*/
bool_t TrieIsAvailable(const trie_t *trie, unsigned char *data);

/*
* TrieIsAvailable() -
* frees the path referenced by data
* undefined behaviour for @trie NULL pointer
* complexity: O(n);                  
*/
void TrieFreeLeaf(trie_t *trie, unsigned char *data);

/*
* TrieNextAvailable() -
* Finds the smallest next available address
* undefined behaviour for @trie NULL pointer
* complexity: O(log(n));
*/
void TrieNextAvailable(trie_t *trie, unsigned char *ip_buffer);

#endif 

