#include <iostream>
#include <utility>

std::pair<int, int> FindOccuring(int arr[], int size)
{
    int temp = arr[0];

    for (int i = 1; i < size; i++)
    {
        temp ^= arr[i];
    }

    int mask = 1;

    while ((mask & temp) == 0)
    {
        mask <<= 1;
    }
    
    std::pair<int, int> result;
    for (int i = 0; i < size; i++)
    {
        if (mask & arr[i])
        {
            result.first ^= arr[i];
        }

        else
        {
            result.second ^= arr[i];
        }
    }
    
    return result;
}

int main()
{
    int arr[10] = {4, 3, 6, 2, 4, 2, 3, 4, 3, 3};
    std::pair<int ,int> res = FindOccuring(arr, 10);

}