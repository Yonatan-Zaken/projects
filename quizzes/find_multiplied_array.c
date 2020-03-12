#include <stdio.h>

#define SIZE_OF_ARR 6

int *FindMult(int arr[], int buff[], size_t size)
{
    int mult_holder = 1;
    int i = 0;
    
    for (i = 0; i < size; ++i)
    {
        buff[i] = mult_holder;
        mult_holder *= arr[i];
    }
    
    mult_holder = 1;
    for (i = size - 1; i >= 0; --i)
    {
        buff[i] *= mult_holder;
        mult_holder *= arr[i];
    }
    
    return buff;
}

void Print(int buff[], size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        printf("%d ", buff[i]);
    }
}

int main ()
{
	int arr[] = {2, 1, 5, 3, 2, 4};
	int buff[SIZE_OF_ARR];
	
	printf("before: ");
	Print(arr, SIZE_OF_ARR);
	
	FindMult(arr, buff, SIZE_OF_ARR);
	printf("\nafter: ");
	Print(buff, SIZE_OF_ARR);
	printf("\n");
	
	return 0;
}

