CFLAGS = -Wall -Wextra -Werror

mains = a b
main_objs = a.o b.o
util_objs = foo.o bar.o
util_headers = foo.h bar.h

all: $(mains)

$(mains): %: %.o $(util_objs)
	$(CC) -o $@ $^

$(main_objs): %.o: %.c $(util_headers)
	$(CC) -c -o $@ $(CFLAGS) $<

$(util_objs): %.o: %.c %.h
	$(CC) -c -o $@ $(CFLAGS) $<

clean:
	rm -f $(mains) $(main_objs) $(util_objs)

.PHONY: all clean
