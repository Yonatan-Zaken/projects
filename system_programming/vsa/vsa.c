/*********************************/
/*   			             	 */
/*   System Programming          */
/*   VSA                         */
/*   Author: Yonatan Zaken       */
/*   Last Updated 19/12/19       */
/*   Reviewed by:            */   
/*			                   	 */
/*********************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "vsa.h" /* vsa functions */

struct BlockHeader
{
    long block_size;
    
    #ifndef DEBUG
    long magic_num
    #endif
}

typedef vsa_t block_header_t;

vsa_t *VSAInit(void *allocated, size_t segment_size)
{
    
}

void *VSAAlloc(vsa_t *vsa, size_t block_size)
{

}

void VSAFree(void *block)
{

}

size_t VSALargestChunkSize(vsa_t *vsa)
{

}

