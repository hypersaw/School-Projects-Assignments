//
// Turing Machine Simulator
//
// Andrew Long
// U. of Illinois, Chicago
// CS301, Spring 2013: Final Project

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
        tmFilenameP = trimWhitespace(tmFilenameP);
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
    TuringMachine machineP(tmFilenameP,tmInputString);
    machineP.runInput(tmInputString);
    
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
