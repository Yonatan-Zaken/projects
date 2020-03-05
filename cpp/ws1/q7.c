#include <stdio.h>
#include <stdlib.h>

int main()
{
/*
	float *f = new float(12.6);
	delete f;
	
	f = new float[15];
	delete[] f;
	*/
	
	int *ptr = (int *)malloc(1000 * sizeof(int));
	delete ptr;
	int *ptr2 = new int[1000];
	free(ptr2);
	
	
	return 0;
}
