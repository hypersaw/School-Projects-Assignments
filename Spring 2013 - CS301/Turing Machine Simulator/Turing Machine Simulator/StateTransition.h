//
//  StateTransition.h
//  Turing Machine Simulator
//
//  Created by Andrew Long on 5/5/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

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