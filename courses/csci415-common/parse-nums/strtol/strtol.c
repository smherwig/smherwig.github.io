#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define die(fmt, ...) \
    do { \
        fprintf(stderr, "[die] %s:%d " fmt "\n", \
                __func__, __LINE__,##__VA_ARGS__); \
        exit(1); \
    } while (0)

#define die_errno(errnum, fmt, ...) \
    do { \
        fprintf(stderr, "[die] %s:%d " fmt ": %s\n", \
                __func__, __LINE__,##__VA_ARGS__, strerror(errnum)); \
        exit(1); \
    } while (0)

/* atoi(3), atol(3), atoll(3), atof(3) */
int
main(int argc, char *argv[])
{
    long x;
    char *endptr = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: strtol NUM\n");
        exit(1);
    }
    
    errno = 0;
    x = strtol(argv[1], &endptr, 10);
    if (errno != 0) {
        /* EINVAL for bad base, or ERANGE for value to big or small */
        die_errno(errno, "invalid integer: \"%s\"", argv[1]);
    }

    if (endptr == argv[1]) {
        /* no digits at all -- not a number */
        die("invalid integer: \"%s\"", argv[1]);
    }

    if (*endptr != '\0') {
        /* trailing garbage */
        die("invalid integer: \"%s\"", argv[1]);
    }

    printf("x = %ld\n", x);

    return 0;
}
