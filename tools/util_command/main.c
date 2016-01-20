#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "sizeof_type.h"
#include "binary_operations.h"


static void
print_help (void)
{
    printf ("\n"
	    "Usage: util [options]\n\n"
	    "  -b,  --binary\t\tPrint help for binary opeartion\n"
	    "  -s,  --sizeof-type\tPrint sizeof-type\n"
	    "  -h,  --help\t\tPrint this help\n"
	   );
}

int
main (int argc, char *argv[]){

    struct option long_options[] = {
		/* Options without arguments */
	{"help",        no_argument,       NULL, 'h'},
	{"sizeof-type",     no_argument,       NULL, 's'},
	{"binary",        no_argument,       NULL, 'b'}
    };
    int val;
    while ((val = getopt_long (argc, argv, "hsb", long_options, NULL)) != -1) {
	    switch (val) {

	    case 'h':
		print_help();
		break;
	    case 's':
		print_sizeof_type();
		break;
	    case 'b':
		conditional();
		help_binary_operations();
		break;
	    default:
		print_help();
		break;
	    }
    }
		return 0;

}
