CC=g++

CFLAGS=-c -Wall

SRC=$(wildcard *.cpp)
EXEC = compil.exe
OBJ=$(SRC:.c=.o)

all: $(EXEC)

compil.exe: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: lexic.h 

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm $(EXECS)