CC=g++

CFLAGS=-c -Wall

SRC=$(wildcard *.cpp)
EXEC = compiler.exe
OBJ=$(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm $(EXECS)