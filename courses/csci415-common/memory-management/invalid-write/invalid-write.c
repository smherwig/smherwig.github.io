#include <stdlib.h>


static void
foo(void)
{
    char *p;

    p = malloc(16);
    p[16] = 'A';
    free(p);
}


int
main(void)
{
    foo();
    return 0;
}
