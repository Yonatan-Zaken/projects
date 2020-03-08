#include <dlfcn.h>
#include <stddef.h>

#include "testing2.h"

int main ()
{
    printf("sum is: %d\n", Foo(111, 222)); 
    FooTwo("String Printing...");
    
	return 0;
}
