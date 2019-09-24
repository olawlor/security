/**
 Demonstrate setuid before, during, and after root switch.

 Dr. Orion Lawlor, lawlor@alaska.edu, 2017-11-01 (Public Domain)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_ids(const char *where) {
	uid_t uid=getuid();
	uid_t euid=geteuid();
	printf("         %s: uid=%d   euid=%d\n",
		where, (int)uid, (int)euid);
}

int main() {
	print_ids("Startup");
	printf("setuid(0) returns %d: becoming root\n",   setuid(0));
	print_ids("As root");
	printf("setuid(1000) returns %d: becoming user\n",   setuid(1000));
	print_ids("As user");
	printf("setuid(0) returns %d: becoming root again\n",   setuid(0));
	print_ids("Back to root");
	return 0;
}
