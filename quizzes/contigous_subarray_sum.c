#include <stdio.h>

int FindMaxSubarray(int arr[], int size)
{
    int max = 0;
    int best_max = arr[0];
    int i = 0;
    
    for (i = 0; i < size; ++i)
    {
        max += arr[i];
        if (best_max < max)
        {
            best_max = max;
        }
        
        if (0 > max)
        {
            max = 0;
        }
    }
    return best_max;
}

int main ()
{
    int arr[] = {-5, -6 , -7};	
	int size = sizeof(arr) / sizeof(int);
	printf("max subarray sum : %d\n", FindMaxSubarray(arr, size));
	
	return 0;
}

