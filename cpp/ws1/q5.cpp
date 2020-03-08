#include <stdio.h>


void foo(int x, int y)
{
	printf("%d\n", (x+y));
}

int main()
{
	int x = 5;
	int y =10;
	char a = 'T';
	
	foo(x, y);
	
	printf("%c\n", a);

	return 0;	
}
