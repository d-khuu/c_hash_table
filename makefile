FLAGS =-ansi -pedantic -Wall -g
CC = gcc
PROGRAM= vm
myprog= hash_table.o prime.o 
SOURCES= hash_table.c prime.c
HEADERS= hash_table.h prime.h


all: $(myprog)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(myprog) 

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^

.PHONY: clean

clean:
	rm -f *.o *.h.gch $(PROGRAM)
archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) *.txt Makefile
