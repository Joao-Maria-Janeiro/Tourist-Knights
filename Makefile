#compiler used
CC = gcc

CFLAGS = -Wall -std=c99 -O3

#executable name
EXECUTABLE = tuktuk

$(EXECUTABLE):
	$(CC) $(CFLAGS) *.c -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)

FORCE:
