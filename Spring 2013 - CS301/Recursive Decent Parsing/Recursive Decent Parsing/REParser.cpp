//
//  REParser.h
//  Regular Expression Parser
//
//  Andrew Long
//  University of Illinois at Chicago
//  CS301, Spring 2013: HW8-PE
//
//  GRAMMAR:
//  1.  <RE> 		-> 	<CONCAT><RE’>
//  2.  <RE’>		->	U<CONCAT>
//  2.  <RE’>		->	/e/
//  3.  <CONCAT> 	->	<KLEEN><CONCAT’>
//  4.  <CONCAT’>	->	<KLEEN><CONCAT’>
//  5.  <CONCAT’>	->	/e/
//  6.  <KLEEN>     ->	<ELEMENT><KLEEN’>
//  7.  <KLEEN’>	->	*<KLEEN’>
//  8.  <KLEEN’>	->	/e/
//  9.  <ELEMENT>	->	a
//  10. <ELEMENT>	->	b
//  11. <ELEMENT>	->	c
//  12. <ELEMENT>	->	d
//  13. <ELEMENT>	->	(<RE>)

#include "REParser.h"

REParser::REParser(){

}

REParser::~REParser(){
    
}

void REParser::parse(std::string input){
    userInput = input+'$';
    index = 0;
    
    try{
        RE();
        match('$');
        
        std::cout << std::endl;
        std::cout << "** Yes, input is a valid RE!" << std::endl;
        std::cout << std::endl;
        
    }
    catch(const char* error){
        std::cout << std::endl;
        std::cout << "** Sorry, input is NOT a valid RE..." << std::endl;
        std::cout << error << std::endl;
        std::cout << std::endl;
    }
}

char REParser::nextCharacter(){    
    return userInput[index];
}

bool REParser::match(char symbol){
    if(nextCharacter() == symbol){
        std::cout << "Matched " << symbol << std::endl;
        consume();
        return true;
    }
    
    return false;
}

void REParser::consume(){
    ++index;
}

void REParser::RE(){
    std::cout << "Called RE()" << std::endl;
    CONCAT();
    _RE();
}

void REParser::_RE(){
    std::cout << "Called _RE()" << std::endl;
    if(match('|')){
        CONCAT();
    }
    else{
        // empty string
    }
}

void REParser::CONCAT(){
    std::cout << "Called CONCAT()" << std::endl;
    KLEENE();
    _CONCAT();
}

bool REParser::_CONCAT(){
    std::cout << "Called _CONCAT()" << std::endl;
    if(KLEENE()){
        _CONCAT();
    }
    else{
        return false;
    }
    
    return true;
}

bool REParser::KLEENE(){
    std::cout << "Called KLEENE()" << std::endl;
    if(ELEMENT()){
        _KLEENE();
        return true;
    }
    
    return false;
}

bool REParser::_KLEENE(){
    std::cout << "Called _KLEENE()" << std::endl;
    if(match('*')){
        _KLEENE();
    }
    else{
        return false;
    }
    
    return true;
}

bool REParser::ELEMENT(){
    std::cout << "Called ELEMENT()" << std::endl;
    if(match('a') || match('b') || match('c') || match('d')){
        // cool
    }
    else if(match('(')){
        RE();
        if(match(')')){
            // cool
        }
        else{
            // not cool
            throw "Missing Closing Parentheses.";
        }
    }
    else{
        return false;
    }
    
    return true;
}

