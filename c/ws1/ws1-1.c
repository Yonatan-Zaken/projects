// header
#include<stdio.h>

float Pow_Ten(int num)
{
	float result = 1.0;
	float base = 10.0;
	
	if (num < 0)
	{
		num = -num;
		base = 1.0 / base;
	}
	
	for(int i = 0; i < num; i++)
	{
		result *= base;
	}
	
	return result;
}

ssssssssssssssssssss
int main()
{
return 0;
}

