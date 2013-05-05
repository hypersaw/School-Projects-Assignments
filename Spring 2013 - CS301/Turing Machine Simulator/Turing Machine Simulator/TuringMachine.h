//
//  TuringMachine.h
//  Turing Machine Simulator
//
//  Created by Andrew Long on 5/4/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

#ifndef TURINGMACHINE
#define TURINGMACHINE

#include <fstream>
#include <iostream>
#include <string>

class TuringMachine{
public:
    TuringMachine(std::string filename);
    ~TuringMachine();
protected:
    
private:
    std::string machineRules[1000];
    int currentLine = 0;
    int currentLinePosition = 0;
    
    std::string trimWhitespace(std::string originalString);
    
    void consumeChar();
    void matchChar(int item);
    int nextChar();
    
    void parseFile();
    
};

#endif
