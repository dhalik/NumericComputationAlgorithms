all:
	g++ -std=c++0x *.cpp

test: all
	./a.out
