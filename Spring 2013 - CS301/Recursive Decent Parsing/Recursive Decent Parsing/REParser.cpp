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
    catch(...){
        std::cout << std::endl;
        std::cout << "** Sorry, input is NOT a valid RE..." << std::endl;
        std::cout << std::endl;
    }
}

char REParser::nextCharacter(){    
    return userInput[index];
}

void REParser::match(char symbol){
    
}

void REParser::consume(){
    ++index;
}

void REParser::RE(){
    
}

void REParser::_RE(){
    
}

void REParser::CONCAT(){
    
}

void REParser::_CONCAT(){
    
}

void REParser::KLEENE(){
    
}

void REParser::_KLEENE(){
    
}

void REParser::ELEMENT(){
    
}

