#include <stdio.h>    /* printf() */
#include <stdlib.h>   /* calloc() */
#include <pthread.h>  /* pthread_create() */
#include <sys/mman.h> /* mmap() */
#include <sys/stat.h> /* struct stat */
#include <fcntl.h> 	  /* open() */
#include <unistd.h>   /* close() */

#define NUM_OF_THREADS (60)
#define NUM_OF_DICT (60)
#define ASCII_SIZE (256)
#define DICT "/usr/share/dict/words"

enum Status
{
	SUCCESS,
	FAIL
};

typedef struct Pack
{
    size_t *res;
    size_t start_index;
    size_t end_index;
    size_t length;
} pack_t;

void *buffer[NUM_OF_DICT] = {0};
pack_t thread_pack[NUM_OF_THREADS] = {0};
size_t final_hist[ASCII_SIZE] = {0};
size_t dict_length = 0;

/*************************************************************************/

void *CountingSort(void *pack)
{
    size_t *res = ((pack_t *)pack)->res;
    unsigned char *dict_buffer = NULL;
	size_t start = ((pack_t *)pack)->start_index;
	size_t end = ((pack_t *)pack)->end_index;
	size_t length = dict_length;
    size_t i = 0, j = 0;

    for (i = start; i < end; ++i)
    {
        dict_buffer = buffer[i];
        for (j = 0; j < length; ++j)
        {
            ++res[dict_buffer[j]];
        }
    }
    
    return pack;
}

/*************************************************************************/

int ThreadInit()
{
	int i = 0;	
	pthread_t threads[NUM_OF_THREADS] = {0};
	
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
		thread_pack[i].res = calloc(sizeof(size_t), ASCII_SIZE);
		if (NULL == thread_pack[i].res)
		{
		    for (--i; i >= 0; --i)
		    {
		        free(thread_pack[i].res); thread_pack[i].res = NULL;
		    }
		    return FAIL;
		}
		       
        if (0 != pthread_create(&(threads[i]), NULL, CountingSort, &thread_pack[i]))
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

int InitDictBuffer()
{
	int fd = 0;
	int i = 0;
	struct stat sb = {0};
		
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
	
	dict_length = sb.st_size;
	for (i = 0; i < NUM_OF_DICT; ++i)
	{
		buffer[i] = mmap(NULL, dict_length, PROT_READ, MAP_PRIVATE, fd, 0);
		if (MAP_FAILED == buffer[i])
		{
			for (; i >= 0; --i)
			{
			    munmap(buffer[i], dict_length);
			}
			return FAIL;
		}
	}
	return fd;
}

/*************************************************************************/

void ThreadLimitInit()
{
    size_t i = 0;
  
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        thread_pack[i].start_index = i * (NUM_OF_DICT / NUM_OF_THREADS);
        if (1 == (NUM_OF_THREADS - i))
        {
        thread_pack[i].end_index = NUM_OF_DICT;
        }
        else
        {
        thread_pack[i].end_index = (i + 1) * (NUM_OF_DICT / NUM_OF_THREADS);        
        }
    }
}

/*************************************************************************/

void FinalHistogram()
{
    size_t i = 0, j = 0;    
    size_t histogram = 0;
    
    for (j = 0; j < ASCII_SIZE; ++j)
    {
        for (i = 0; i < NUM_OF_THREADS; ++i)
        {
            histogram += thread_pack[i].res[j];
        }
        
        printf("%c : %lu\n", j, histogram);
        histogram = 0;
    }
}

/*************************************************************************/

void Destroy()
{
    size_t i = 0;
    for (i = 0; i < NUM_OF_DICT; ++i)
    {
        munmap(buffer[i], dict_length);
    }
    
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        free(thread_pack[i].res); thread_pack[i].res = NULL;
    }
}

/*************************************************************************/

int main ()
{
    int fd = 0;
    
	if (FAIL == (fd = InitDictBuffer()))
	{
	    return FAIL;
	}
	
	ThreadLimitInit();
	
	if (FAIL == ThreadInit())
	{
	    return FAIL;    
	}

	FinalHistogram();
	
	close(fd);
	Destroy();
	
	return 0;
}

