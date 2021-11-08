CC = gcc
CFLAGS = -lpthread -g -std=c99
SOURCES = sleepingStylistSem.c
OBJ = sleepingStylistSem

sleepingStylistSem:
	$(CC) $(CFLAGS) $(SOURCES) -o $(OBJ)

run:
	./$(OBJ)

clearBin:
	rm $(OBJ)
