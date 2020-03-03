#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* malloc() */
#include <string.h>    /* strtok() */
#include <assert.h>    /* assert() */
#include <pthread.h>   /* pthread_create() */
#include <sys/stat.h>  /* struct stat */
#include <fcntl.h> 	   /* open() */
#include <unistd.h>    /* close() */
#include <sys/mman.h>  /* mmap() */
#include <sys/types.h> /* ssize_t */

#define NUM_OF_THREADS (3)
#define NUM_OF_COPIES (3)
#define FILE_NAME "/usr/share/dict/words"

enum
{
    SUCCESS,
    FAIL
};

typedef int (*cmp_func_t)(const void *data1, const void *data2);

char **buffer = {0};
char *dict = NULL;
size_t num_of_words = 0;
pthread_t threads[NUM_OF_THREADS] = {0};
/**************************************************************************/

static int LoadDictionary(int fd, size_t size)
{
    if (MAP_FAILED == (dict = mmap(NULL, size, PROT_READ|PROT_WRITE, 
                                               MAP_PRIVATE, fd, 0)))
    {
        perror("mmap:");
        return FAIL;
    }
    
    return SUCCESS;
}

/**************************************************************************/

static size_t CountWords()
{
    FILE *fptr = NULL;
    size_t counter = 0;
    char c = 0;
    
    if (NULL == (fptr = fopen(FILE_NAME, "r")))
    {
        perror("fopen:");
        return FAIL;
    }
    
    while (EOF != (c = fgetc(fptr)))
    {
        if ('\n' == c)
        {
            ++counter;            
        }
    }
    
    fclose(fptr);
    return counter;
}

/**************************************************************************/

void Swap(char **ptr1, char **ptr2)
{
    void *temp = NULL;

    assert(NULL != ptr1);
    assert(NULL != ptr2);

    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

/**************************************************************************/

static void ShuffleBuffer(size_t size)
{
    size_t i = 0, j = 0;
    
    srand(time(NULL));
    
    for (i = 0; i < size; ++i)
    {
        j = rand() % size;
        Swap(&buffer[i], &buffer[j]);    
    }
}

/**************************************************************************/

static int BuildPoitnerBuffer(size_t num_of_words)
{
    size_t i = 0;
    
    buffer = (char **)malloc(sizeof(char *) * num_of_words * NUM_OF_COPIES);
    if (NULL == buffer)
    {
        return FAIL;
    }
    
    buffer[0] = strtok(dict, "\n");
    for (i = 1; i < num_of_words; ++i)
    {
        buffer[i] = strtok(NULL, "\n");
    }
    
    ShuffleBuffer(num_of_words);
    
    for (i = 1; i < NUM_OF_COPIES; ++i)
    {
        memcpy(buffer + (num_of_words * i), buffer, sizeof(char *) * num_of_words);
    }
    
    return SUCCESS;
}

/**************************************************************************/

int CompareFunc(const void *data1, const void *data2)
{
    assert(NULL != data1);
    assert(NULL != data2);
    
    return strcmp(*(char **)data1, *(char **)data2);
}

static void *SortBuffer(void * param)
{
    size_t index = (size_t)param;
    size_t start = index * ((num_of_words * NUM_OF_COPIES) / NUM_OF_THREADS);
    size_t end = (index + 1) * ((num_of_words * NUM_OF_COPIES) / NUM_OF_THREADS);
    
    qsort((buffer + start), (end - start), sizeof(char *), &CompareFunc); 

    return param; 
}

/**************************************************************************/

static int ThreadsQuickSort()
{
    size_t i = 0;
    
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (0 != pthread_create(&threads[i], NULL, SortBuffer, (void *)i))
        {
            perror("pthread_create:");
            return FAIL;
        }
    }    
    
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    
    return SUCCESS;
}

/**************************************************************************/

static void PrintBuffer()
{
    size_t i = 0;
    size_t num_of_elements = num_of_words * NUM_OF_COPIES;
    
    for (i = 0; i < num_of_elements; ++i)
    {
        printf("%s\n", buffer[i]);
    }
}

/**************************************************************************/

static void MergeSort(void *dest_arr, size_t left, size_t middle, size_t right)
{
    size_t i = 0, j = 0, k = 0;
    size_t size1 = middle - left;
    size_t size2 = right - middle;
    
    void **left_side = malloc(sizeof(char *) * size1);
    void **right_side = malloc(sizeof(char *) * size2);
    
    for (i = 0; i < size1; ++i)
    {
        left_side[i] = ((char **)dest_arr)[left + i];
    }
    
    for (j = 0; j < size2; ++j)
    {
        right_side[j] = ((char **)dest_arr)[middle + j];
    }
    
    i = 0; j = 0; k = left;
    
    while ((i < size1) && (j < size2))
    {
     
        if (left_side[i] <= right_side[j])
        {
            ((char **)dest_arr)[k] = left_side[i];
            ++i;
        }
        else
        {
            ((char **)dest_arr)[k] = right_side[j];
            ++j;
        }
        ++k;
    }
    
    while (i < size1)
    {
        ((char **)dest_arr)[k] = left_side[i];
        ++i;
        ++k;
    }
    
    while (j < size2)
    {
        ((char **)dest_arr)[k] = right_side[j];
        ++j;
        ++k;
    }
    
    free(left_side); left_side = NULL;
    free(right_side); right_side = NULL;
}

static void MergeBuffer()
{
	size_t i = 0;
	size_t start = 0;
	size_t end = 0;
	size_t middle = 0;

	for (i = 1; i < NUM_OF_THREADS; ++i)
	{
	    size_t start = 0;
    	size_t end = (i + 1) * ((num_of_words * NUM_OF_COPIES) / NUM_OF_THREADS);
    	size_t middle = end - num_of_words;
    	MergeSort(buffer, start, middle, end);
	}
}

/**************************************************************************/

void Destroy(int fd)
{
	free(buffer); buffer = NULL;
	close(fd);
	munmap(dict, num_of_words);
}

/**************************************************************************/

int main ()
{
    int fd = 0;
    size_t size = 0;
    struct stat stat_buf = {0};
    
	if (-1 == (fd = open(FILE_NAME, O_RDONLY)))
	{
	    perror("open:");
		return FAIL;
	}
	
    if (-1 == fstat(fd, &stat_buf))        
	{
		perror("fstat:");	
		return FAIL;
	}     
	size = stat_buf.st_size;	

	LoadDictionary(fd, size);

	num_of_words = CountWords();

	BuildPoitnerBuffer(num_of_words);

	ThreadsQuickSort();
	
	MergeBuffer();
	
	PrintBuffer();
	
	Destroy(fd);
	
	return 0;
}

