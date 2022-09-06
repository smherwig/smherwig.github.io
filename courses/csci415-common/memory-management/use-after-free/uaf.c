#include <stdio.h>
#include <stdlib.h>


static void
foo(void)
{
    char *p;

    p = malloc(16);
    p[0] = 'A';
    free(p);

    printf("p[0] = %c\n", p[0]);
}


int
main(void)
{
    foo();
    return 0;
}
