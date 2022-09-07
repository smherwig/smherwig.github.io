CFLAGS = -Wall -Wextra -Werror -ggdb

all: ex1 stack queue

ex1: ex1.c
	$(CC) -o $@ $(CFLAGS) $^

stack: stack.c
	$(CC) -o $@ $(CFLAGS) $^

queue: queue.c
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -f ex1 stack queue

.PHONY: all clean
