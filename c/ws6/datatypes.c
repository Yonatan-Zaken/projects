#include <stdio.h>

int main()
{
    printf("\nC Data Types\n");
    printf("================================\n");
    
    printf("size of char:            %ld bytes\n", sizeof(char));
    printf("size of unsigned char:   %ld bytes\n", sizeof(unsigned char));
    printf("size of signed char:     %ld bytes\n", sizeof(signed char));
    printf("size of int:             %ld bytes\n", sizeof(int));
    printf("size of unsigned int:    %ld bytes\n", sizeof(unsigned int));
    printf("size of short:           %ld bytes\n", sizeof(short));
    printf("size of unsigned short:  %ld bytes\n", sizeof(unsigned short));
    printf("size of long:            %ld bytes\n", sizeof(long));
    printf("size of unsigned short:  %ld bytes\n", sizeof(unsigned short));
    printf("size of float:           %ld bytes\n", sizeof(float));
    printf("size of double:          %ld bytes\n", sizeof(double));
    printf("size of long double:    %ld bytes\n", sizeof(long double));
    printf("size of size_t:          %ld bytes\n", sizeof(size_t));
    printf("size of char*:           %ld bytes\n", sizeof(char*));
    printf("size of int*:            %ld bytes\n\n", sizeof(int*));
             
    return 0;
}
