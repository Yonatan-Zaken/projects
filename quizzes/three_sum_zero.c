#include <stdio.h>

#define ON 1
#define OFF 0

enum
{
    SUCCESS,
    FAIL
};

static void Swap(int *data1, int *data2)
{
    int temp = *data1;
    *data1 = *data2;
    *data2 = temp;
}

static void BubbleSort(int arr[], size_t size)
{
    size_t j = 0;
    size_t new_size = size - 1;
    size_t temp_size = 0;
    int flag = ON;
    
    while (ON == flag)
    {
        flag = OFF;
        for (j = 0; j < new_size; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                Swap(&arr[j], &arr[j + 1]);
                temp_size = j;
                flag = ON;
            }
        }
        new_size = temp_size;
    }
}

static int IsThreeSumZero(int arr[], size_t size)
{
    size_t i = 0;
    size_t start = 0; 
    size_t end = size - 1;
    int temp_sum = 0;
    int sum = 0;
    
    BubbleSort(arr, size);
    
    if (0 < arr[0])
    {
        return FAIL;
    }
    
    for (i = 0; i < size; ++i)
    {
        sum = -(arr[i]);
        start = i + 1;
        while (start < end)
        {
            temp_sum = arr[start] + arr[end];
            if (temp_sum == sum)
            {
                return SUCCESS;
            }
            else if (temp_sum < sum)
            {
                ++start;
            }
            else
            {
                --end;
            }
        }
    }
    return FAIL;
}

int main ()
{
	int arr[] = {-14, 12, -2, 55, -1, 5, 6, 7, -19};
	
	if (IsThreeSumZero(arr, 9))
	{
	    printf("The sum of three elements is not zero\n");
	}
	printf("The sum of three elements is zero\n");
	
	BubbleSort(arr, 5);
	return 0;
}

