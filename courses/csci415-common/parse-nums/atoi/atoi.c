#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int x;

    if (argc != 2) {
        fprintf(stderr, "Usage: atoi NUM\n");
        exit(1);
    }
    
    x = atoi(argv[1]);

    printf("x = %d\n", x);

    return 0;
}
