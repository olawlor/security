// A bunch of header files, and a main for this NetRun-style function "foo".
#include <iostream>
#include <string>
#include <string.h> // for strcmp & c
#include <stdlib.h> // for exit
#include <vector>
#include <fstream>

#define CDECL extern "C" 
CDECL long foo(void);
#include "signals.c"

#include <sys/mman.h>


// Stop unintentional buffer overflows
class stack_guard {
public:
        enum {N=1000};
        unsigned char buf[N];
        stack_guard() {
                buf[0]=0xbb;
                buf[N-1]=0xbb;
        }
        ~stack_guard() {
                if (buf[0]!=0xbb || buf[N-1]!=0xbb) {
                        printf("Stack smashed, but not in a good way!");
                        printf("Got %x in buf\n",(int)buf[0]);
                        exit(1);
                }
        }
};

// One page of machine code
unsigned char mc[4096] __attribute__ ((aligned (4096)));

long run_mc() {
        // Make memory read-execute
        if (0!=mprotect(&mc[0],4096,PROT_READ|PROT_EXEC)) {
                perror("mprotect fail");
        }
        typedef long (*fn)(void);
        fn f=(fn)&mc[0];
        printf("Running machine code at %p\n",mc);
        return f(); // finally run it!
}


int main() {
	handle_signals(); // <- if program crashes, print a NetRun-style crash report
	std::cout<<"Starting program..."<<std::endl;
	long ret=foo();
	std::cout<<"Program complete.  Return "<<ret<<std::endl;
	return ret;
}
