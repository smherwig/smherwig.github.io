#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* 
 * On success, return the number of lines read.
 * On failure, return a negative errno value.
 */
static ssize_t
read_lines(const char *path)
{
    FILE *fh;
    ssize_t len = 0;
    size_t n = 0;
    char *line = NULL;
    ssize_t ret = 0;

    fh = fopen(path, "r");
    if (fh == NULL) {
        ret = -errno;
        goto out;
    }

    while (1) {
        errno = 0;
        len = getline(&line, &n, fh);
        if (len == -1) {
            if (errno != 0)
                ret = -errno;
            goto out;
        }

        ret++;

        /* 
         * TODO: process line.
         * (Here, we just print the line and some info from getline's output.)
         */
        printf("%6zd (%4zd, %4zu, %p): %s", ret, len, n, line, line);
    }

out:
    free(line); 
    if (fh != NULL)
        fclose(fh);

    return ret;
}


int
main(int argc, char *argv[])
{
    ssize_t nlines;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s FILE\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    nlines = read_lines(argv[1]);
    if (nlines < 0)
        fprintf(stderr, "error: %s: %s\n", argv[1], strerror(-nlines));

    return nlines >= 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
