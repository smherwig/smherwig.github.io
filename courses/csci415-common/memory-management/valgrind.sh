#!/bin/sh

# use --track-origins=yes to locate origin of uninitialized values;
# this option can really slow things down.

# use --undef-value-errors=no to ignore uninitialized values

valgrind --tool=memcheck --leak-check=yes --show-reachable=yes "$@"
