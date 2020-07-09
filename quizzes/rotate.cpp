#include <iostream>
#include <cstring>

void EfficientRotate(char arr[], size_t shift)
{
    size_t len = strlen(arr);
    size_t toShift = shift % len;
    int prev = arr[0];
    int temp = 0;
    size_t k = toShift;

    for (size_t i = 0; i < len; ++i)
    {
        temp = arr[k];
        arr[k] = prev;
        prev = temp;
        k = (k + toShift) % len;
    }
}

void Print(char arr[])
{
    while (*arr != '\0')
    {
        std::cout << *arr;
        ++arr;
    }
}

int main()
{
    char arr[] = "abcde";
    EfficientRotate(arr, 7);

    Print(arr);
}