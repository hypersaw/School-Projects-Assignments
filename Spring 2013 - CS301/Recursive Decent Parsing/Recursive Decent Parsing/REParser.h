//
//  REParser.h
//  Regular Expression Parser
//
//  Andrew Long
//  University of Illinois at Chicago
//  CS301, Spring 2013: HW8-PE
//

#ifndef REPARSER
#define REPARSER

#include <iostream>

class REParser{
public:
    REParser();
    ~REParser();
    
    void parse(char* input);
private:
    unsigned int index;
    char* userInput;
    
    char nextCharacter();
    void match(char* symbol);
    void consume();
protected:
    
};

#endif