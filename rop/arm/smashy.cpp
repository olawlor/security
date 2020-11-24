/*
 This is a toy model of an application that is vulnerable to
 a stack-smashing attack.  It's actually a buffer *underflow*,
 so we don't hit the compiler's stack cookie.

 Orion Lawlor, lawlor@alaska.edu, 2020-11-23 (educational use only)
*/
#include <iostream>
#include <unistd.h>
#include "lib/inc.h" // crash report tools
#include "lib/inc.c" 
#include "lib/signals.c"

/* Fully safe function: read data into an array */
long fill_array(unsigned long *array,long len)
{
	printf("Entering fill_array, array=%p\n",array);
	long count=0;
	while (1==scanf("%lx",&array[count]))
// std::cin>>std::hex>>array[count]) 
	{
		printf("array[%ld]=%lx\n", count, array[count]);
		count++;
		if (count>len) break;
	}
	printf("Returning from fill_array, count=%d\n",(int)count);
	return count;
}

/* UNSAFE function with a bug */
int foo(void) 
{
	unsigned long storage[10];
	unsigned long *ptr=storage;
	
	ptr-=4; //<- OOOPS!  (bad pointer arithmetic)
	
	long count=fill_array(ptr,10);
	std::cout<<"No failure reading "<<count<<" entries from array\n";
	return storage[0];
}

/* Print a bunch of data useful for constructing the attack */
void recon() {
	// Copy out our memory maps
	//   Set /proc/sys/kernel/randomize_va_space to 0 to stop this moving around.
	FILE *maps=fopen("/proc/self/maps","r");
	const int N=8192;
	char buf[N];
	size_t read=fread(buf,1,N,maps);
	fwrite(buf,1,read,stdout);
	fclose(maps);
	
	std::cout<<"Address of execve: "<<(void *)execve<<std::endl;
	dump_hex(((char *)execve)-1,64);
}

/* Call the safe function in an unsafe way */
int main()
{
	int err=setuid(0); //<- for extra danger, run this with setuid!
	handle_signals();
	recon();
	foo();
	return err;
}
