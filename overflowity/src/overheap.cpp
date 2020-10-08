/* Most modern bugs involve heap overwrites, which let
  bugs *anywhere* trash data, not just the bad module. */
#include "support/main.h"

class user_record {
public:
        std::string userID; // user's ID
        user_record() { userID="none"; }
};

class access_record {
public:
        char access[8];
        access_record() { strcpy(access,"none"); }
};

long foo() {
        user_record *u=new user_record();
        printf("Allocated user record at %p\n",u);
        access_record *a=new access_record();
        printf("Allocated access record at %p\n",a);

	std::cout<<"Enter ID:\n";
	std::cin>>(char *)u->userID.c_str(); // OOPS!

        std::cout<<"Your ID: "<<u->userID<<"\n";
        std::cout<<"Your access:      "<<a->access<<"\n";
        return strcmp(a->access,"ALL");
}
