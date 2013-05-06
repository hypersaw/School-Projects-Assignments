#include "State.h"

State::State(){
    stateName = "NULL";
}

State::State(std::string name){
    stateName = name;
}

State::~State(){
    stateTransitions.clear();
}

void State::addTransition(std::string inputs, char output, char direction, std::string destination){
    StateTransition* newTransition;
    newTransition = new StateTransition(inputs,output,direction,destination);
    stateTransitions.push_back(*newTransition);
}

bool State::hasOutputOnInput(char input){
    for(int i = 0; i < stateTransitions.size(); ++i){
        if(stateTransitions.at(i).getInputs().find(input) != std::string::npos){
            if(stateTransitions.at(i).getOutput() != 0){
                return true;
            }
        }
    }
    
    return false;
}

bool State::hasTransitionOnInput(char input){
    for(int i = 0; i < stateTransitions.size(); ++i){
        if(stateTransitions.at(i).getInputs().find(input) != std::string::npos){
            return true;
        }
    }
    
    return false;
}

char State::outputOnInput(char input){
    char output;
    
    for(int i = 0; i < stateTransitions.size(); ++i){
        if(stateTransitions.at(i).getInputs().find(input) != std::string::npos){
            output = stateTransitions.at(i).getOutput();
        }
    }
    
    return output;
}

char State::directionOnInput(char input){
    char direction;
    
    for(int i = 0; i < stateTransitions.size(); ++i){
        if(stateTransitions.at(i).getInputs().find(input) != std::string::npos){
            direction = stateTransitions.at(i).getDirection();
        }
    }
    
    return direction;
}

std::string State::stateOnInput(char input){
    std::string direction;
    
    for(int i = 0; i < stateTransitions.size(); ++i){
        if(stateTransitions.at(i).getInputs().find(input) != std::string::npos){
            direction = stateTransitions.at(i).getDestination();
        }
    }
    
    return direction;    
}


std::string State::getStateName(){
    return stateName;
}