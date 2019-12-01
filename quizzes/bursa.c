#include <stdio.h>
#include <assert.h>

int FindMaxProfit(int arr[], int size, int* buy, int *sell)
{
    int max_profit = 0;              
    int min_value = arr[0]; 
    int i = 0, j = 0, max_value = 0;
    
    if (1 >= size)
    {
        return max_profit;
    }
    
    *buy = 0;
    *sell = 0;  
    max_profit = arr[1] - arr[0];
    
    for (i = 0; i < size; ++i)
    {
        if (max_profit <= arr[i] - min_value)
        {
            max_profit = arr[i] - min_value;
            *sell += i - max_value;
            max_value = i;  
            *buy += j;
        }
        
        else if (min_value > arr[i])
        {
            min_value = arr[i];
            j = i;
            
        }    
    }
    
    return max_profit;
}

int main()
{
    int array[] = {6,12,3,5,1,4,9,2};
    int buy = 0;
    int sell = 0;
    /*
    int *pbuy = &buy;
    int *psell = &sell;
    */
    int result = FindMaxProfit(array, 8, &buy, &sell);
    printf("maxprofit = %d\n buy %d sell %d", result, buy, sell);
    
    return 0;
}
