CC=g++
CFLAGS=-c -Wall -std=c++0x
SOURCES=./main.cpp ./polynomial/polynomialInterpolation.cpp ./matrix/rational.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

test: all
	./main
