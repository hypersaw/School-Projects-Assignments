//
//  StateTransition.cpp
//  Turing Machine Simulator
//
//  Created by Andrew Long on 5/5/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

#include "StateTransition.h"

StateTransition::StateTransition(std::string inputs, char output, char direction, std::string destination){
    transitionInputs = inputs;
    transitionOutput = output;
    transitionDestination = destination;
    transitionDirection = direction;
}

StateTransition::~StateTransition(){
    
}

std::string StateTransition::getInputs(){
    return transitionInputs;
}

std::string StateTransition::getOutput(){
    return transitionOutput;
}

std::string StateTransition::getDestination(){
    return transitionDestination;
}

char StateTransition::getDirection(){
    return transitionDirection;
}