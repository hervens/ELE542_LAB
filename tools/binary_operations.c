
#include "binary_operations.h"

#define A 0xFE

void
print_binary (u02 n){ 
 
    int i;
/*    printf ("la taile de n est de %d bits soit %d bytes\n",(sizeof(n)*8),sizeof(n)); */
    printf ("la valeur binaire est: ");
    n = (double)n; 

    for(i = sizeof(n)*(8)-1; i >= 0; i--){
	if(i%4==3)
	    printf(" ");

	printf ("%d",(n >> i ) & 1); 
/*	printf("%d: %d\n",i,(n >> i ) & 1); */
    }

    printf ("\n"); 
}

void
print_with_indent(int indent, char * string){

    printf("%*s" "%s", indent, " ", string);
}

void 
repeat_char(int i){
    
    int j=0;
    while(j<i){
	printf("=");
	j++;
    }
    printf ("\n");
}

void
help_binary_operations (void){
 
    u02 a=0xFF00;
    u02 b=0x1111;
    u02 c=0x0000;
   
    repeat_char(50);
    printf("a:\t"); print_binary(a);
    a= ~a; 
    printf ("NOT a = ~a\n");
    printf("a:\t"); print_binary(a);

    repeat_char(50);
    a=0xFF00;
    printf("a:\t"); print_binary(a);
    printf("b:\t"); print_binary(b);
    c= b ^ a; 
    printf ("XOR c = b ^ a\n");
    printf("c:\t"); print_binary(c);

    repeat_char(50);
    printf("a:\t"); print_binary(a);
    printf("b:\t"); print_binary(b);
    c= b | a; 
    printf ("OR c = b | a\n");
    printf("c:\t"); print_binary(c);

    repeat_char(50);
    printf("a:\t"); print_binary(a);
    printf("b:\t"); print_binary(b);
    c= b & a; 
    printf ("AND c = b & a\n");
    printf("c:\t"); print_binary(c);

    repeat_char(50);
    printf("a:\t"); print_binary(a);
    printf("b = 2\n");
    b = 2;
    c = a >> b; 
    printf ("Decalage a droite c = a >> b\n");
    printf("c:\t"); print_binary(c);

    repeat_char(50);
    printf("a:\t"); print_binary(a);
    printf("b = 3\n");
    b = 3;
    c = a << b;
    printf ("Decalage a gauche c = a << b\n");
    printf("c:\t"); print_binary(c);

    repeat_char(50);
    printf("a:\t"); print_binary(a);
    a |= (1 << 2);
    printf ("Mise a 1 du bit 2 a |= 1 << 2\n");
    printf("a:\t"); print_binary(a);
}

void
conditional(void){
    
    printf ("s = condition ? true : false\ns = ( x < 0 ) ? -1   : x * x\n");
    
    int x;
    x=2;
    int s = ( x < 0 ) ? -1 : x * x;
    printf("x = 2:\t s = %d\n",s);
    x = -1;
    s = ( x < 0 ) ? -1 : x * x;
    printf("x = -1:\t s = %d\n",s);
}
