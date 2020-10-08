/* Non-interesting crash, to see how crash report looks. */
#include "support/main.h"

long foo() {
	long *ptr=(long *)0xDEADDEAD;
	std::cout<<"Reading memory at address "<<ptr<<std::endl;
	long yeah=*ptr;
	std::cout<<"How can we still be alive?!\n";
	return yeah;
}
