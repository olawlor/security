/* It's very handy to smash variables that index into arrays.
   Once you overwrite the index, you can jump anywhere relative to the 
   start of the array--even backwards! */
#include "support/main.h"

class user_record {
public:
        long ID; // user's ID
        long access; // either 0xA11 for all, or 0xF001 for none.
        long events[2];
        long count;
        void show() {
                printf("ID: %08lx\n", ID);
                printf("access: %08lx\n", access);
                printf("events[0]: %08lx\n", events[0]);
                printf("events[1]: %08lx\n", events[1]);
                printf("count: %08lx\n", count);
        }
};

long foo() {
        user_record u;
        u.ID=0x12345;
        u.access=0xF001;
        u.count=0;

        long read_val=0;
        while (1==scanf("%li",&read_val)) {
                printf("Read %lx\n",read_val);
                u.events[u.count++] = read_val;
                u.show();
        }

        return u.access ^ 0xA11;
}

