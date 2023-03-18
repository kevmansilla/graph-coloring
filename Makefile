CC = gcc
CFLAGS = -Wall -Wextra -O3 -g -std=c99 -I -fsanitize=address,undefined 
TARGET = discretaII
OBJS = $(SRCS:.c=.o)
SRCS = $(wildcard *.c)
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: clean

all: 	$(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 

.c.o:
	$(CC) $(CFLAGS)  -c $<  -o $@

clean:
	$(RM) $(OBJS) *~ $(TARGET)

valgrind:
	$(VALGRIND) ./test.sh