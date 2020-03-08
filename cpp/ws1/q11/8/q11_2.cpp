#include <dlfcn.h>
#include <stddef.h>

#include "testing2.h"

typedef int (*func_t)(int, int);
typedef void (*func2_t)(char *);

int main ()
{
    void *handle = NULL;
    
    printf("Opening libtesting2.so...\n");
    handle = dlopen("./libtesting2.so", RTLD_LAZY);    
    if (!handle) 
    {
        printf("Cannot open library: %s\n", dlerror());
        /*cerr << "Cannot open library: " << dlerror() << endl;*/
        return 1;
    }
    
    dlerror();
    func_t func = (func_t)dlsym(handle, "Foo");
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
    
        printf("Cannot load symbol: %s\n", dlsym_error);
        /*cerr << "Cannot load symbol: " << dlsym_error << endl;*/
        dlclose(handle);
        return 1;
    }
    
    printf("sum is %d\n", func(555, 222));
    
    func2_t func2 = (func2_t)dlsym(handle, "FooTwo");
    dlsym_error = dlerror();
    if (dlsym_error)
    {
    
        printf("Cannot load symbol: %s\n", dlsym_error);
        /*cerr << "Cannot load symbol: " << dlsym_error << endl;*/
        dlclose(handle);
        return 1;
    }
    
    func2("Printing The String...");
    
    
    printf("closing library...\n");
    /*cout << "Closing library...\n";*/
    dlclose(handle);

	return 0;
}
