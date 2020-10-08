/* You can long ints (64 bits, 8 bytes) here 
   in hex with 0x1234abcd, or decimal. */
#include "support/main.h"

class user_record {
public:
        long ID; // user's ID
        long events[2];
        long access; // either 0xA11 for all, or 0xF001 for none.
        void show() {
                printf("ID: %08lx\n", ID);
                printf("events[0]: %08lx\n", events[0]);
                printf("events[1]: %08lx\n", events[1]);
                printf("access: %08lx\n", access);
        }
};

long foo() {
        user_record u;
        u.ID=0x12345;
        u.access=0xF001;

        long read_val=0;
        long count=0;
        while (1==scanf("%li",&read_val)) {
                printf("Read %lx\n",read_val);
                u.events[count++] = read_val;
                u.show();
        }

        return u.access ^ 0xA11;
}

