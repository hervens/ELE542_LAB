#include "sizeof_type.h"



void 
print_sizeof_type (void){

    printf ("%-30s %d\n","sizeof int:",sizeof(int));
    printf ("%-30s %d\n","sizeof unsigned short int:",sizeof(unsigned short int));
    printf ("%-30s %d\n","sizeof unsigned int:",sizeof(unsigned int));
    printf ("%-30s %d\n","sizeof long:",sizeof(long));
    printf ("%-30s %d\n","sizeof unsigned long:",sizeof(unsigned long));
    printf ("%-30s %d\n","sizeof long long:",sizeof(long long));
    printf ("%-30s %d\n","sizeof unsigned long long:",sizeof(unsigned long long));
    printf ("%-30s %d\n","sizeof float:",sizeof(float));
    printf ("%-30s %d\n","sizeof double:",sizeof(double));
    printf ("%-30s %d\n","sizeof long double:",sizeof(long double));
    printf ("%-30s %d\n","sizeof unsigned char:",sizeof(unsigned char));
    printf ("%-30s %d\n","sizeof char:",sizeof(char));
    printf ("%-30s %d\n","sizeof unsigned:",sizeof(unsigned));

}
