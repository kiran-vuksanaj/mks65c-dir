CC = gcc
ifeq ($(DEBUG),true)
	CFLAGS = -g
endif

all: dir.o pstat.o
	$(CC) $(CFLAGS) -o elless pstat.o dir.o
dir.o: dir.c pstat.h
	$(CC) $(CFLAGS) -c dir.c
pstat.o: pstat.c pstat.h
	$(CC) $(CFLAGS) -c pstat.c
run:
	./elless
clean:
	rm *.o
	rm elless
	rm *~
