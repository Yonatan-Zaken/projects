#include <stdio.h>

int main()
{
    int a = 200;
    void *p = &a;
    FILE *pfile = fopen("file.txt", "w");
    if (NULL != pfile)
    {
        fprintf(pfile, "%p", p);
    }
    
    fclose(pfile);
    return 0;
}


