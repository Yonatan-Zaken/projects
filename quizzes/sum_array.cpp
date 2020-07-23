#include <iostream>

int MaxSum(int arr[], int size)
{
    int sum1 = arr[0];
    int sum2 = arr[1];
    int max = std::max(sum1, sum2);
    int index1 = 0;
    int index2 = 1;
    int last_index = 2;

    while ((index1 < size) && (index2 < size))
    {
        if (sum1 > sum2)
        {
            sum1 += arr[index1 + 2];
            sum2 = arr[last_index];
            index2 = last_index;
            ++last_index;
        }



        max = (sum1 > max) ? sum1 : max;
        max = (sum2 > max) ? sum2 : max;
        
        
    }
    
    return max;
}

int main()
{
    int arr[6] = {-8, 3, 7, -5, 6, -4};
    std::cout << "MaxSum = " << MaxSum(arr, 6);

    return 0; 
}