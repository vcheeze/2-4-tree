all: 24tree

24tree: main.o
	g++ main.o -o 24tree

main.o: main.cpp
	g++ -c main.cpp

Node.o: Node.cpp
	g++ -c Node.cpp

tree.o: tree.cpp
	g++ -c tree.cpp

LinkedList.o: LinkedList.cpp
	g++ -c LinkedList.cpp

MaxHeap.o: MaxHeap.cpp
	g++ -c MaxHeap.cpp

clean:
	rm *.o 24tree
