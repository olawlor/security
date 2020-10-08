/* Overwrite two fields with one buffer overflow */
#include "support/main.h"

class user_record {
public:
        char userID[8]; // user's ID
        char GUARD[8]; // prevent buffer overflow
        char access[8]; // either "none", "some", or "ALL"
};

long foo() {
        user_record u;
        strcpy(u.userID,"none");
        strncpy(u.GUARD,"NOACCESS",8);
        strcpy(u.access,"none");

	std::cout<<"Enter ID:\n";
	std::cin>>u.userID;

        std::cout<<"Your ID: "<<u.userID<<"\n";
        if (strncmp(u.GUARD,"NOACCESS",8)!=0) {
                std::cout<<"ERROR!  BUFFER OVERFLOW DETECTED!\n";
                return 1;
        }
        else {
                std::cout<<"Guard appears OK, safe to proceed\n";
        }
        std::cout<<"Your access:      "<<u.access<<"\n";
        return strcmp(u.access,"ALL");
}
