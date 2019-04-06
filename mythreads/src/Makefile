# Single Author info:
# 	jhshah 	 Jitesh H Shah
# Group info:
# 	jhshah	 Jitesh H Shah
# 	sskanitk Salil S Kanitkar
# 	ajalgao	 Aditya A Jalgaonkar
#

SRCS =   mythread_q.c mythread_create.c mythread_exit.c  mythread_exit.c mythread_join.c mythread_detach.c
INC = mythread.h  mythread_q.h
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
all: lib test

lib: $(LIB)

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
