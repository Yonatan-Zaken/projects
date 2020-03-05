#include <stdio.h>
#include <stdlib.h>

int main()
{

	float *f = new float(12.6);
	delete f;
	
	f = new float[15];
	delete[] f;
	
	/*
	float *f = (float *)malloc(sizeof(float));
	*f = 12.6;
	free(f);	*/
	
	
	return 0;
}
