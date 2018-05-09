CC = g++
CFLAGS = -Wall -std=c++11 -std=gnu++11

INCL = -I ./include

DEPS = include/*

OBJ = playfair.o

EXEC = playunfair cypher

all: $(EXEC)

playunfair: $(OBJ) playunfair.o
	$(CC) $(CFLAGS) -o $@ $^

cypher: $(OBJ) cypher.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCL)


clean:
	rm -f *.o $(OBJ) $(EXEC)


