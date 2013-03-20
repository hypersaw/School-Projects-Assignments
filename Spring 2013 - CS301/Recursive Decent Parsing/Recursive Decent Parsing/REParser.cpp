//
//  REParser.cpp
//  Regular Expression Parser
//
//  Andrew Long
//  University of Illinois at Chicago
//  CS301, Spring 2013: HW8-PE
//

#include "REParser.h"

REParser::REParser(){

}

REParser::~REParser(){
    
}

void REParser::parse(char* input){
    userInput = input;
    index = 0;
}

char REParser::nextCharacter(){    
    return userInput[index];
}

void REParser::match(char* symbol){
    
}

void REParser::consume(){
    ++index;
}