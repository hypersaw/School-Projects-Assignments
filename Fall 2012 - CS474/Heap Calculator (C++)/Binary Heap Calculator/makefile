calc: main.o SetCalculator.o BinaryHeap.o BinaryNode.o
	g++ -o along main.o SetCalculator.o BinaryHeap.o BinaryNode.o

main.o: main.cpp
	g++ -c main.cpp

SetCalculator.o: SetCalculator.cpp SetCalculator.h
	g++ -c SetCalculator.cpp

BinaryHeap.o: BinaryHeap.cpp BinaryHeap.h
	g++ -c BinaryHeap.cpp

BinaryNode.o: BinaryNode.cpp BinaryNode.h
	g++ -c BinaryNode.cpp

clean:
	rm along *.o
