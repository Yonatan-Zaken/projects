#include <stdio.h>    /* printf() */
#include <stdlib.h>   /* calloc() */
#include <pthread.h>  /* pthread_create() */
#include <sys/mman.h> /* mmap() */
#include <sys/stat.h> /* struct stat */
#include <fcntl.h> 	  /* open() */
#include <unistd.h>   /* close() */
#include <wchar.h>

#define NUM_OF_THREADS (10)
#define ASCII_SIZE (256)
#define DICT "/usr/share/dict/words"

typedef struct Pack
{
	void *addr[NUM_OF_THREADS];
	unsigned char *result[NUM_OF_THREADS];
	size_t length;
	size_t index;
} pack_t; 

size_t ind = 0;
size_t final_hist[ASCII_SIZE] = {0};
size_t length = 0;

enum Status
{
	SUCCESS,
	FAIL
};

/*************************************************************************/

void PrintResult(unsigned char *result, size_t length)
{
	write(STDOUT_FILENO, result, length);	
}

/*************************************************************************/

void PrintHist()
{
	size_t i = 0;
	
	for (i = 0; i < ASCII_SIZE; ++i)
	{
		printf("%c : %lu\n", i, final_hist[i]);	
	}	
}

/*************************************************************************/

void CreateFinalHist(pack_t *pack)
{
	size_t i = 0;
	size_t j = 0;
	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{	
		printf("char : %c i : %ld\n", pack->result[i][0], i);	
		for (j = 0; j < pack->length; ++j)
		{
			++final_hist[pack->result[i][j]];	
		}
	}
	/*PrintHist(final_hist);*/
	printf("length %ld\n", pack->length);
}

/*************************************************************************/

void *CountingSort(void *pack)
{
	unsigned char *runner = ((pack_t*)pack)->addr[((pack_t*)pack)->index];
	unsigned char *res = ((pack_t*)pack)->result[((pack_t*)pack)->index];
	size_t length = ((pack_t*)pack)->length;
    size_t i = 0;
    size_t histogram[ASCII_SIZE] = {0};
    
    printf("%lu\n", ((pack_t*)pack)->index);
    for (i = 0; i < length; ++i)
    {
        ++histogram[(int)runner[i]];
    }
    
    for (i = 1; i < ASCII_SIZE; ++i)
    {
        histogram[i] += histogram[i - 1];
    }       
    
    for (i = length - 1; i > 0; --i)
    {
        res[histogram[(int)runner[i]] - 1] = runner[i];
        --histogram[(int)runner[i]];
    }
    
    res[histogram[(int)runner[i]] - 1] = runner[i];
    
    return pack;
}

/*************************************************************************/

int ThreadInit(pack_t *pack)
{
	size_t i = 0;
	pthread_t threads[NUM_OF_THREADS] = {0};
	
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
    	
        if (0 != pthread_create((threads + i), NULL, CountingSort, pack))
        {
            printf("Error pthread_create\n");
            return FAIL;
        }
    }
    
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    
    return SUCCESS;	
}

/*************************************************************************/

int main(int argc, char *argv[])
{
	unsigned char *addr = NULL;
	int fd = 0;
	size_t i = 0;
	struct stat sb = {0};
	pack_t *pack = NULL;
		
	if (-1 == (fd = open(DICT, O_RDONLY)))
	{
		printf("open error\n");	
		return FAIL;
	}
	
    if (-1 == fstat(fd, &sb))        
	{
		printf("fstat error\n");	
		return FAIL;
	}           
	
	pack = malloc(sizeof(pack_t));
	if (NULL == pack)
	{
		return 1;
	}
	
	pack->length = sb.st_size;

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pack->result[i] = malloc(sizeof(char) * pack->length);
		if (NULL == pack->result[i])
		{
			return 1;
		}	
	}
	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pack->addr[i] = mmap(NULL, pack->length, PROT_READ, MAP_PRIVATE, fd, 0);
		if (MAP_FAILED == pack->addr[i])
		{
			printf("mmap error\n");
			return FAIL;
		}
	}
	
	if (FAIL == ThreadInit(pack))
	{
		return FAIL;
	}
	
	close(fd);
	
	CreateFinalHist(pack);
	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{	
		free(pack->result[i]); pack->result[i] = NULL;		
	}
	
	free(pack); pack = NULL;
	return 0;
}

