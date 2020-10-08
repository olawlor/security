/* Overwriting function pointers gives you control of the code
   that the CPU runs next. */
#include "support/main.h"

void expose_secrets(void) {
        printf("Mailing a very interesting envelope to the BBC...\n");
        exit(0);
}

typedef void (*error_fn)(const char *error);

class user_record {
public:
        long events[2];
        error_fn error;
        void show() {
                printf("events[0]: %08lx\n", events[0]);
                printf("events[1]: %08lx\n", events[1]);
                printf("error: %p\n", error);
        }
};

long foo() {
        printf("expose_secrets = %p\n", (void *)expose_secrets);

        user_record u;
        u.error=0;

        long read_val=0;
        long count=0;
        while (1==scanf("%li",&read_val)) {
                printf("Read %lx\n",read_val);
                u.events[count++] = read_val;
                u.show();
        }
        
        if (count>2) {
                printf("Overflow detected!  Running error function\n");
                u.error("Overflow!");
        }

        printf("Not there yet...");
        return 1;
}

