#include <dlfcn.h>
#include <stddef.h>
#include <iostream>
#include <stdio.h>

#include "shared.hpp"

using namespace std;

typedef void (*func_t)(char, int);

int main ()
{
    float f = 5.4;
    void *handle = NULL;
    
     cout << "Opening testing.so...\n";
    handle = dlopen("./libtesting.so", RTLD_LAZY);    
    if (!handle) 
    {
        printf("Cannot open library: %s\n", dlerror());
        /*cerr << "Cannot open library: " << dlerror() << endl;*/
        return 1;
    }
    
    dlerror();
    func_t func = (func_t)dlsym(handle, "_Z3Fooci");
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
    
        printf("Cannot load symbol: %s\n", dlsym_error);
        /*cerr << "Cannot load symbol: " << dlsym_error << endl;*/
        dlclose(handle);
        return 1;
    }
    
    func('K', 222);
    printf("closing library...\n");
    /*cout << "Closing library...\n";*/
    dlclose(handle);

	return 0;
}

