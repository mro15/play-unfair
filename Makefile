CC = g++
CFLAGS = -Wall -std=c++11 -std=gnu++11

INCL = -I ./include

DEPS = include/*

OBJ = playfair.o playunfair.o

EXEC = playunfair

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCL)

all: $(EXEC)

clean:
	rm -f $(OBJ) playunfair

