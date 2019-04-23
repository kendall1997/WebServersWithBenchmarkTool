# Makefile for mypthread

SRCS =   mythread_q.c mythread_create.c mythread_exit.c  mythread_exit.c mythread_join.c mythread_detach.c mymutex.c myscheduler.c 
INC = mythread.h  mythread_q.h mymutex.h myscheduler.h
OBJS = $(SRCS:.c=.o)
TEST_SRCS = mythread_test.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
DEBUG=0

CFLAGS =  -I. -g -lpthread
LDFLAGS = -L.
LIB = libmythread.a

AR = /usr/bin/ar
CC = gcc

ifeq ($(DEBUG),1)
EXTRA_CFLAGS += -DDEBUG
endif

.PHONY: all lib clean tags test a5
a5:  all

# This function compiles every .c and .h

all: lib test

lib: $(LIB)

# This make the librarie static

libmythread.a: $(OBJS) $(INC)
	$(AR) rcs $(LIB) $(OBJS)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(LIB) *~ mythread_test

tags:
	find . -name "*.[cChH]" | xargs ctags
	find . -name "*.[cChH]" | etags -

test:	$(TEST_OBJS) $(INC) lib
	$(CC) -o mythread_test $(CFLAGS) $(EXTRA_CFLAGS) $(TEST_OBJS) $(LIB)

pthread: 
	$(CC) pthread_test.c -o pthread -lpthread

pthread_clean:
	rm pthread

timer:
	$(CC) timer.c -o timer

timer_clean:
	rm timer
