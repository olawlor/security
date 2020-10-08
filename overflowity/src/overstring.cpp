/* Overwrite a C++ std::string by noticing that it only
   has space for 16 chars */
#include "support/main.h"

class user_record {
public:
        std::string userID; // user's ID
        char access[8]; // either "none", "some", or "ALL"
};

long foo() {
        user_record u;
        u.userID="none";
        strcpy(u.access,"none");

	std::cout<<"Enter ID:\n";
	std::cin>>(char *)u.userID.c_str(); // OOPS!

        std::cout<<"Your ID: "<<u.userID<<"\n";
        std::cout<<"Your access:      "<<u.access<<"\n";
        return strcmp(u.access,"ALL");
}
