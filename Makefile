CC = g++
CFLAGS = -Wall

INCL = -I ./include

DEPS = include/*

OBJ = playfair.o playunfair.o

EXEC = playunfair

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCL)

all: $(EXEC)

clean:
	rm -f $(OBJ) playunfair

