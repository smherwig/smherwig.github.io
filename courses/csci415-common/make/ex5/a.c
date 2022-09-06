#include <stdio.h>

#include "foo.h"
#include "bar.h"

int
main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    
    printf("I'm 'a'\n");
    foo();
    bar();
    return 0;
}
