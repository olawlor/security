/* Simple hello world program--give it any input and it's happy! */
#include "support/main.h"

long foo() {
	std::cout<<"Please enter your name!\n";
	std::string s;
	std::cin>>s;
	if (s!="") {
		std::cout<<"Hello '"<<s<<"'!\n";
		return 0; // OK
	} else {
		std::cout<<"Error, didn't read a name...\n";
		return 1; // error exit
	}
}
