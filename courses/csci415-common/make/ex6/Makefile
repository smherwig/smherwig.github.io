CFLAGS = -Wall -Wextra -Werror

objects = a.o b.o foo.o bar.o

all: a b

a: a.o foo.o bar.o
	gcc -o  $@ $^

b: b.o foo.o bar.o
	gcc -o  $@ $^

a.o: a.c foo.h bar.h
	gcc -c -o $@ $(CFLAGS) $<

b.o: b.c foo.h bar.h
	gcc -c -o $@ $(CFLAGS) $<

foo.o: foo.c foo.h
	gcc -c -o $@ $(CFLAGS) $<

bar.o: bar.c bar.h
	gcc -c -o $@ $(CFLAGS) $<

clean:
	rm -f a b $(objects)

.PHONY: all clean
