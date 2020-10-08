/* Trivial "input the access you want" program */
#include "support/main.h"

class user_record {
public:
        char access[8]; // either "none", "some", or "ALL"
};

long foo() {
        user_record u;
        strcpy(u.access,"none");

	std::cout<<"Enter the access level desired\n";
	std::cin>>u.access;
        std::cout<<"Your access: "<<u.access<<"\n";
        return strcmp(u.access,"ALL");
}
