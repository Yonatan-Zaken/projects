#include <stdio.h>
#include <string.h>


void InitializeArr(int arr[], int n);
int FindLastAlive(int arr[], int n, int start_indux);
int CountAlive(int arr[], int n);


int main()
{
    int arr[7] = {0};
    int last_alive = 0;
    
    InitializeArr(arr, 7);
    last_alive = FindLastAlive(arr, 7, 1);
    printf("Soldier %d survives.\n",last_alive);
    
    return 0;    
}


int FindLastAlive(int arr[], int n, int start_index)
{
    int i = start_index;
    
    while(1)                   /* If more than 1 is left */
    {
        if((n - 1) == i)
        {
            i = 0;
        }
        
        else ++i;
        
        while(0 == arr[i])        /* If current is dead */
        {
             if((n - 1) == i)
             {
                i = 0;
             }
                
             else ++i;        
        }
        
        
        arr[i] = 0;
        
        if((n - 1) == i)         /* Move to next alive */
        {
            i = 0;
        }
        
        else ++i;                      
        
        while(0 == arr[i])        /* If current is dead */
        {
             if((n - 1) == i)
             {
                i = 0;
             }
                
             else ++i;        
        }
        
        if(1 == CountAlive(arr, n))
        {
            return i;
            break;
        }
        
    }
    
    return i;    
}

void InitializeArr(int arr[], int n)
{
    int i = 0;
    
    for(; i < n ; ++i)
    {
        arr[i] = 1;
    }
}

int CountAlive(int arr[], int n)
{
    int i = 0;
    int count = 0;
    int is_one_left = 0;
    
    for(i = 0; i < n; i++)
    {
        if(1 == arr[i])
        {
            ++count;
        }     
    }
    
    if(1 == count)
    {
        is_one_left = 1;
    }
    
    return is_one_left;
}
















