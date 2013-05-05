//
//  main.cpp
//  Turing Machine Simulator
//
//  Created by Andrew Long on 5/4/13.
//  Copyright (c) 2013 Andrew Long. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

#include "TuringMachine.h"

std::string trimWhitespace(std::string originalString);

int main(int argc, const char * argv[]){
    
    std::string tmFilenameP;
    std::string tmInputString;
    std::ifstream tmFile;
    
    std::cout << "** Welcome to Turing Machine Simulator **\n";
    
    do{
        std::cout << ">> Please enter filename containing TM program P: ";
        getline(std::cin,tmFilenameP);
        tmFilenameP = "/Users/andrewlong/Documents/School-Projects-Assignments/Spring 2013 - CS301/Turing Machine Simulator/Turing Machine Simulator/"+trimWhitespace(tmFilenameP);
        tmFile.open(tmFilenameP.c_str());
        if(tmFile.fail()){
            std::cout << ">> Incorrect file name, please enter another.\n";
        }
    }while(tmFile.fail());
    tmFile.close();
    
    std::cout << ">> Please enter an input string W: ";
    getline(std::cin,tmInputString);
    tmInputString = trimWhitespace(tmInputString);
    
    std::cout << "** Running...\n";
    TuringMachine machineP(tmFilenameP);

    
    return 0;
}

std::string trimWhitespace(std::string originalString){
    
    for(int i = 0; i < originalString.length(); ++i){
        if(originalString[i] == ' '){
            originalString.erase(i,1);
            --i;
        }
    }
    
    return originalString;
}
