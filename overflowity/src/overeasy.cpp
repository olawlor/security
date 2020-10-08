/* Easy buffer overflow on the previous data field. */
#include "support/main.h"

class user_record {
public:
        char userID[8]; // user's ID
        char access[8]; // either "none", "some", or "ALL"
};

long foo() {
        user_record u;
        strcpy(u.userID,"none");
        strcpy(u.access,"none");

	std::cout<<"Enter ID:\n";
	std::cin>>u.userID;
        std::cout<<"Your ID: "<<u.userID<<"\n";
        std::cout<<"Your access:      "<<u.access<<"\n";
        return strcmp(u.access,"ALL");
}
