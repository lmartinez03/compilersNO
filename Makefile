# Makefile for C-
# Run with
# make
# ./cminus gcd.cm

CC = gcc

OBJS = main.o util.o scan.o

cminus: $(OBJS)
	$(CC) $(OBJS) -o cminus
main.o: main.c globals.h util.h scan.h
	$(CC) -c main.c
util.o: util.c util.h globals.h
	$(CC) -c util.c
scan.o: scan.c scan.h util.h globals.h
	$(CC) -c scan.c
cminusrunner: cminusrunner.c
	$(CC) cminusrunner.c -o cminusrunner

all: cminus cminusrunner

clean:
	-rm cminu
	-rm cminusrunner
	-rm $(OBJS)
