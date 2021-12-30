CXX=g++
CXXFLAGS= -std=c++17
LDFLAGS= -pthread -fopenmp

SRC=$(wildcard *.cpp)
EXEC = tester.exe
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm $(EXECS)