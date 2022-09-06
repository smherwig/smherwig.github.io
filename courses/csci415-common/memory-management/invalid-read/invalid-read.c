#include <stdio.h>
#include <stdlib.h>


static void
foo(void)
{
    char *p;

    p = malloc(16);
    printf("p[17] = 0x%02x\n", p[17]);
    free(p);
}


int
main(void)
{
    foo();
    return 0;
}
