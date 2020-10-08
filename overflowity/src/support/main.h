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


int main() {
	handle_signals(); // <- if program crashes, print a NetRun-style crash report
	std::cout<<"Starting program..."<<std::endl;
	long ret=foo();
	std::cout<<"Program complete.  Return "<<ret<<std::endl;
	return ret;
}
