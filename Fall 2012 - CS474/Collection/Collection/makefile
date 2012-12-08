collection: main.o Collection.o OrderedCollection.o Array.o
	g++ -o along main.o Collection.o OrderedCollection.o Array.o

main.o: main.cpp
	g++ -c main.cpp

Collection.o: Collection.cpp Collection.h
	g++ -c Collection.cpp

OrderedCollection.o: OrderedCollection.cpp OrderedCollection.h
	g++ -c OrderedCollection.cpp

Array.o: Array.cpp Array.h
	g++ -c Array.cpp

clean:
	rm along *.o
