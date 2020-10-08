/* Your input is hex bytes of machine code.
   Write a function that returns zero!  */
#include "support/main.h"

long foo(void) {
        int nextbyte=0;
        int count=0;
        while (1==scanf("%x",&nextbyte))
                mc[count++]=nextbyte;
        
        printf("Read %d bytes of machine code\n",count);
        
        return run_mc();
}

