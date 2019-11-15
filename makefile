CC = gcc
ifeq ($(DEBUG),true)
	CFLAGS = -g
endif

all: dir.o
	$(CC) $(CFLAGS) -o elless dir.o
dir.o: dir.c
	$(CC) $(CFLAGS) -c dir.c

run:
	./elless
clean:
	rm *.o
	rm elless
	rm *~
