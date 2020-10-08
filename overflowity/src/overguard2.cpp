/* Use the "double write trick" to first trash the access,
   then a second overflow to put the guard string's terminator back */
#include "support/main.h"

class user_record {
public:
        char userID[4]; // user's ID
        char userPIN[4]; // user's PIN 
        char GUARD[8]; // prevent buffer overflow
        char access[8]; // either "none", "some", or "ALL"

        void show(void) {
                printf("ID  %s\n",userID);
                printf("PIN     %s\n",userPIN);
                printf("GUARD       %s\n",GUARD);
                printf("access              %s\n",access);
        }
};

long foo() {
        stack_guard before;
        user_record u;
        stack_guard after;
        strcpy(u.userID,"none");
        strcpy(u.userPIN,"1234");
        strcpy(u.GUARD,"SAFENOW");
        strcpy(u.access,"none");

	std::cout<<"Enter ID:\n";
	std::cin>>u.userID;
        u.show();
	std::cout<<"Enter PIN:\n";
	std::cin>>u.userPIN;
        u.show();

        if (strcmp(u.GUARD,"SAFENOW")!=0) {
                std::cout<<"ERROR!  BUFFER OVERFLOW DETECTED!\n";
                return 1;
        }
        else {
                std::cout<<"Guard appears OK, safe to proceed\n";
        }
        std::cout<<"Your access:      "<<u.access<<"\n";
        return strcmp(u.access,"ALL");
}
