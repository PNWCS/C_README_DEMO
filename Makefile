CC = gcc
CFLAGS = -Wall -g

all: ipcount

ipcount: ipcount.o utils.o
	$(CC) $(CFLAGS) -o ipcount ipcount.o utils.o

ipcount.o: ipcount.c utils.h
utils.o: utils.c utils.h

clean:
	rm -f *.o ipcount
