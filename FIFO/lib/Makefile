# Costa Rica Institute of Technology
# Computer Engineering
# Operating Systems
# Kendall González León
# 2015087861

WD=$(shell pwd)


CC=gcc
CFLAGS= -fpic -Wall -O2
CFLAGS_LIB= -shared

HEADER=$(WD)/../include

OUTPUT=$(WD)/../bin


main: http.so
	@echo "Building libraries"

http.so: http.o
	@$(CC) -Wall http.o -o "$(OUTPUT)/libhttp.so" $(CFLAGS_LIB)

http.o: 
	@$(CC) -Wall -c http.c -o http.o $(CFLAGS) -I"$(HEADER)"

clean:
	@rm -f *.o libhttp.so 2> /dev/null