CC=g++
CFLAGS=-c -Wall -std=c++0x -MMD
BIN=./bin/
SRC=./src/
FILES=main.cpp polynomial/polynomialInterpolation.cpp matrix/rational.cpp
SOURCES=$(addprefix $(SRC), $(FILES))
OBJECTS=$(addprefix $(BIN), $(FILES:.cpp=.o))
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(BIN)%.o: $(SRC)%.cpp
	$(CC) $(CFLAGS) -o $@ $<

test: all
	./main

clean:
	rm $(OBJECTS)
