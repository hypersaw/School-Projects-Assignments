turingmachine: main.o TuringMachine.o State.o StateTransition.o
	g++ -o along main.o TuringMachine.o State.o StateTransition.o

main.o: main.cpp
	g++ -c main.cpp

TuringMachine.o: TuringMachine.cpp TuringMachine.h
	g++ -c TuringMachine.cpp

State.o: State.cpp State.h
	g++ -c State.cpp

StateTransition.o: StateTransition.cpp StateTransition.h
	g++ -c StateTransition.cpp

clean:
	rm along *.o
