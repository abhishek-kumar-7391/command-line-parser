CC=gcc
CFLAGS= -fPIC -Wall -Werror 
LIBNAME=libcmdparse
LIB_SO_NAME=$(LIBNAME).so.1

all:parse lib

parse: parse_cmdline.o 

parse_cmdline.o: parse_cmdline.c parse_cmdline.h
	$(CC) -c $(CFLAGS) $^
	@rm -f ./*.gch

cmdline.o: test.c 
	$(CC) -c $(CFLAGS) $^

lib: parse_cmdline.o
	$(CC) -shared -Wl,-soname,$(LIBNAME).so -o $(LIB_SO_NAME) $^
	@rm -rf ./lib
	@mkdir ./lib
	@cp -f $(LIB_SO_NAME) ./lib/
	@rm -f ./$(LIB_SO_NAME)

install:
	@cp -f ./parse_cmdline.h /usr/local/include/
	@cp -f ./lib/$(LIB_SO_NAME) /usr/local/lib/
	@ldconfig /usr/local/lib/

.PHONY: clean distclean
distclean: clean
	@rm -f /usr/local/lib/libcmdparse.*
	@rm -f /usr/local/include/parse_cmdline.h
	@rm -rf ./lib
clean:
	@rm -rf ./*.gch
	@rm -rf ./*.o
	@rm -f ./parse_cmdline ./main

