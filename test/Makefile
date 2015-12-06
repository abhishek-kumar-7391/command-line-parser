CC=gcc
CFLAGS= -Wall -Werror
LDFLAGS= -lcmdparse
all:test

test: test.o
	$(CC) -o $@ $^ $(LDFLAGS)

test.o: test.c
	$(CC) $(CFLAGS) -c $^

.PHONY: clean
clean:
	@rm -rf ./*.gch
	@rm -rf ./*.o
	@rm -f ./test
