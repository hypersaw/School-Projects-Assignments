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
        if(RE()){
            match('$');    
        }
        else{
            throw "Empty string or invalid symbols";
        }
        
        std::cout << std::endl;
        std::cout << "Input is a valid RE" << std::endl;
        std::cout << std::endl;
        
    }
    catch(const char* error){
        std::cout << std::endl;
        std::cout << "Input is not a valid RE (" << error << ")" << std::endl;
        std::cout << std::endl;
    }
}

char REParser::nextCharacter(){    
    return userInput[index];
}

bool REParser::match(char symbol){
    if(nextCharacter() == symbol){
        consume();
        return true;
    }
    
    return false;
}

void REParser::consume(){
    ++index;
}

bool REParser::RE(){
    if(CONCAT()){
        _RE();
        return true;
    }
    
    return false;
}

void REParser::_RE(){
    if(match('|')){
        CONCAT();
    }
    else{
        // empty string
    }
}

bool REParser::CONCAT(){
    if(KLEENE()){
        _CONCAT();
        return true;
    }
    
    return false;
}

bool REParser::_CONCAT(){
    if(KLEENE()){
        _CONCAT();
        return true;
    }
    
    return false;
}

bool REParser::KLEENE(){
    if(ELEMENT()){
        _KLEENE();
        return true;
    }
    
    return false;
}

bool REParser::_KLEENE(){
    if(match('*')){
        _KLEENE();
    }
    else{
        return false;
    }
    
    return true;
}

bool REParser::ELEMENT(){
    if(match('a') || match('b') || match('c') || match('d')){
        return true;
    }
    else if(match('(')){
        RE();
        if(match(')')){
            return true;
        }
        else{
            throw "Missing closing parentheses";
        }
    }
    
    return false;
}

