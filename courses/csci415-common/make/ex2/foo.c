#include <stdio.h>

static void
foo(void)
{
    printf("foo\n");
}

static void
bar(void)
{
    printf("bar\n");
}

int
main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    foo();
    bar();
    return 0;
}
