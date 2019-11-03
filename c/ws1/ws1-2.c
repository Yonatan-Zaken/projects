#include <stdio.h>

// This function returns 10^ the number we send it. 
double PowTen(int num)
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

// This function returns a flipped number
long long int FlipNum(long long int num)
{
	int count = 0;
	long long int temp = num;
	
	do {
		temp = temp/10;
		count++;
		//printf("temp = %lf count = %d\n",temp,count);
	} while (temp >= 1);
	temp = 0;
	
	for(int i = count; i > 0; i--)
	{
		temp += (num % 10) * (long long int)(PowTen(i-1));
		num /= 10;
		//printf("swap = %lf, num = %d\n",temp,num);
	}
	
	return temp;
}

int main()
{
	long long int a = 0;
	printf("enter a number you want to flip: ");
	scanf("%lld", &a);
	getchar();
	
	long long int result = FlipNum(a);
	printf("a = %lld, result = %lld", a, result);
	return 0;
}

