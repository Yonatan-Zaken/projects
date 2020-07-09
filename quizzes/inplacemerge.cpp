#include <iostream>
#include <algorithm>

void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}

	std::cout << '\n';
}

void InPlaceMerge(int arr1[], int size1, int arr2[], int size2)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int first = 0;

    for (i = 0; i < size2; i++)
    {
        for (j = 0; j < size1; j++)
        {
            if (arr1[j] > arr2[i])
            {
                std::swap(arr1[j], arr2[i]);
                first = arr2[i];
                for (k = i + 1; (k < size2) && (arr2[k] < first); ++k)
                {
                    arr2[k - 1] = arr2[k];
                }
                arr2[k - 1] = first;
            }
        }
    }
    
}

int main()
{
    int X[] = { 1, 4, 7, 8, 10 };
	int Y[] = { 2, 3, 9 };

	int m = sizeof(X) / sizeof(X[0]);
	int n = sizeof(Y) / sizeof(Y[0]);

	InPlaceMerge(X, m, Y, n);

	std::cout << "X: "; printArray(X, m);
	std::cout << "Y: "; printArray(Y, n);
}