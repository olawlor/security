/* As before, but now your machine code can't contain any ASCII
   control characters (below decimal 32), because these stop a scanf. */
#include "support/main.h"

long foo(void) {
        int nextbyte=0;
        int count=0;
        while (1==scanf("%x",&nextbyte))
        {
                if (nextbyte<32) {
                        printf("ZERO BYTE DETECTED!  ANGRY EXIT AT byte %d\n",count);
                        exit(1);
                }
                mc[count++]=nextbyte;
        }
        
        printf("Read %d bytes of machine code\n",count);
        
        return run_mc();
}

