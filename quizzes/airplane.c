/**********************************/
/* Airplane Quizz  In Two Methods */
/**********************************/

#include <stdio.h>

int FindStayedOne(int arrive[], int left[], int arrive_size, int left_size)
{
    int sum_arrive = 0;
    int sum_left = 0;
    int i = 0;
    
    for (i = 0; i < left_size; ++i)
    {
        sum_left += left[i];
    }
    
    for (i = 0; i < arrive_size; ++i)
    {
        sum_arrive += arrive[i];
    }
    
    return (sum_arrive - sum_left);
}

int FindStayedTwo(int arrive_and_left[], int size)
{
    int i = 0;
   
    for (i = 0; i < size; ++i)
    {
        arrive_and_left[i+1] ^= arrive_and_left[i];
    }
    
    return arrive_and_left[size - 1];    
}

int main()
{
    int arrive[] = {2, 51, 4, 1, 72, 44, 99};
    int left[] = {99, 72, 2, 44, 1, 4};
    int arrive_and_left[] = {2, 51, 4, 1, 72, 44, 99, 99, 72, 2, 44, 1, 4};
    
    printf("The ID of airplane that stayed is: %d\n", 
                 FindStayedOne(arrive, left, 7, 6));
                 
    printf("The ID of airplane that stayed is: %d\n", 
                 FindStayedTwo(arrive_and_left, 13));
    
    return 0;
}
