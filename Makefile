
CC=gcc
CFLAGS=-I./src

DEPS = src/database.h
OBJ = src/main.o src/database.o src/operations.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

database: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o database
