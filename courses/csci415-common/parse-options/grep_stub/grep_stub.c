#define _GNU_SOURCE

#include <errno.h>
#include <limits.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define USAGE \
    "Usage: grep_stub [-m] [-h] [-i] PATTERN FILE\n" \
    "\n" \
    "Print lines in FILE that match PATTERN.\n" \
    "\n" \
    "optional arguments\n" \
    "   -h, --help\n" \
    "       Show usage statement and exit.\n" \
    "\n" \
    "   -i, --ignore-case\n" \
    "       Perform a case-insensitve match for PATTERN.\n" \
    "\n" \
    "   -m, --max-count NUM\n" \
    "       Stop reading FILE after NUM matching lines.\n"

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

static void
usage(int status)
{
    puts(USAGE);
    exit(status);
}


int 
main(int argc,char *argv[])
{
    int opt, nargs;
    /* 
     * An option that takes a required argument is followed by a ':'.
     * The leading ':' suppresses getopt_long's normal error handling.
     */
    const char *short_opts = ":him:";
    struct option long_opts[] = {
        {"help", no_argument, NULL, 'h'},
        {"ignore-case", no_argument, NULL, 'i'},
        {"max-count", required_argument, NULL, 'm'},
        {NULL, 0, NULL, 0}
    };
    bool ignore_case = false;
    int max_count = -1;
    int ret = 0;

    while (1) {
        opt = getopt_long(argc, argv, short_opts, long_opts, NULL);
        if (opt == -1) {
            /* processed all command-line options */
            break;
        }

        switch (opt) {
        case 'h':
            usage(0);
            break;
        case 'i':
            ignore_case = true;
            break;
        case 'm':
            /* optarg */
            ret = mu_str_to_int(optarg, 10, &max_count);
            if (ret != 0)
                die_errno(-ret, "invalid value for --max-count: \"%s\"", optarg);
            break;
        case '?':
            die("unknown option '%c' (decimal: %d)", optopt, optopt);
            break;
        case ':':
            die("missing option argument for option %c", optopt);
            break;
        default:
            die("unexpected getopt_long return value: %c\n", (char)opt);
        }
    }

    /* 
     * optind is the index in argv of the first non-option (that is, the first
     * positional argument).
     */
    nargs = argc - optind;
    if (nargs != 2)
        die("expected two positional arguments, but found %d", nargs);

    printf("ignore_case: %s\n", ignore_case ? "true" : "false");
    printf("max_count: %d\n", max_count);     
    printf("PATTERN: \"%s\"\n", argv[optind]);     
    printf("FILE: \"%s\"\n", argv[optind + 1]);     

    return 0;
}
