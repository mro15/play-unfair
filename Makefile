CC = g++
CFLAGS = -Wall -std=c++11 -std=gnu++11

INCL = -I ./include

DEPS = include/*

OBJ = playfair.o

EXEC = playunfair cypher

all: $(EXEC)

playunfair: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $@.o

cypher: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $@.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCL)


clean:
	rm -f $(OBJ) $(EXEC)


