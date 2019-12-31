#include <stdio.h>

int main()
{
    int x = 5;
    int y = 20;
    
    void *p;
    FILE *pfile = fopen("file.txt", "r");
    if (NULL != pfile)
    {
        fscanf(pfile, "%p", &p);
    }
    
    fclose(pfile);
    
    printf("%p\n", p);
     
    printf("%d\n", *(int*)p);    
    
    return 0;
}


