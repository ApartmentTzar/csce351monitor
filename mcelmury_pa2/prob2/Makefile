CC=gcc
CFLAGS=-I. -lpthread -g -std=c99
DEPS = monitor.h
OBJ = sleepingStylistMon.o monitor.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sleepingStylistMon: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	$(RM) *.o
	$(RM) sleepingStylistMon