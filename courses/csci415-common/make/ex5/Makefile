CFLAGS = -Wall -Wextra -Werror

all: a b

a: a.c foo.c bar.c foo.h bar.h
	gcc -o $@ $^

b: a.c foo.c bar.c foo.h bar.h
	gcc -o $@ $^
clean:
	rm -f a b

.PHONY: all clean
