//
// Turing Machine Simulator
//
// Andrew Long
// U. of Illinois, Chicago
// CS301, Spring 2013: Final Project

#ifndef STATETRANSITION
#define STATETRANSITION

#include <iostream>
#include <string>

class StateTransition{
public:
    StateTransition(std::string inputs, char output, char direction, std::string destination);
    ~StateTransition();
    
    std::string getInputs();
    char getOutput();
    std::string getDestination();
    char getDirection();
    
protected:
    
private:
    std::string transitionInputs;
    char transitionOutput;
    std::string transitionDestination;
    char transitionDirection;
    
};

#endif