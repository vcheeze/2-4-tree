all: 24tree

24tree: main.o
	g++ main.o -o 24tree

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o 24tree
