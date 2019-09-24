/**
 Simple shared library intercept:
	gcc -fPIC -shared preload.c -o preload.so
	export LD_PRELOAD=preload.so
*/
#include <stdio.h>
#include <stdlib.h>

char *setlocale(int category, const char *locale)
{
	puts("ALL YOUR BASE ARE BELONG TO US");
	return NULL; /* "the request cannot be honored" */
}
