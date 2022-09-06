#include <errno.h>
#include <limits.h>
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


/* 
 * On success, return 0 and set val to the parsed value.
 * On failure, return a negative errno value.
 */
static int
mu_str_to_long(const char *s, int base, long *val)
{
    char *endptr;

    errno = 0;
    *val = strtol(s, &endptr, base);
    if (errno != 0) {
        /* EINVAL for bad base, or ERANGE for value to big or small */
        return -errno;
    }

    if (endptr == s) {
        /* no digits at all -- not a number */
        return -EINVAL;
    }

    if (*endptr != '\0') {
        /* trailing garbage */
        return -EINVAL;
    }

    return 0;
}


/* 
 * On success, return 0 and set val to the parsed value.
 * On failure, return a negative errno value.
 */
static int
mu_str_to_int(const char *s, int base, int *val)
{
    int ret;
    long tmp;

    ret = mu_str_to_long(s, base, &tmp); 
    if (ret < 0)
        return ret;

    if (tmp < INT_MIN || tmp > INT_MAX)
        return -ERANGE;

    *val = (int)tmp;
    return 0;
}


int
main(int argc, char *argv[])
{
    int x, err;

    if (argc != 2) {
        fprintf(stderr, "Usage: strtol NUM\n");
        exit(1);
    }

    err = mu_str_to_int(argv[1], 10, &x);
    if (err != 0)
        die_errno(-err, "invalid integer: \"%s\"", argv[1]);

    printf("x = %d\n", x);

    return 0;
}
