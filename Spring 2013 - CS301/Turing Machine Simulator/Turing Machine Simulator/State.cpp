//
//  Rule.cpp
//  Turing Machine Simulator
//
//  Created by Andrew Long on 5/5/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

#include "State.h"

State::State(){
    stateName = "NULL";
}

State::State(std::string name){
    stateName = name;
}

State::~State(){
    
}

void State::addTransition(std::string inputs, char output, char direction, std::string destination){
    StateTransition newTransition(inputs,output,direction,destination);
    stateTransitions.push_back(newTransition);
}


std::string State::getStateName(){
    return stateName;
}