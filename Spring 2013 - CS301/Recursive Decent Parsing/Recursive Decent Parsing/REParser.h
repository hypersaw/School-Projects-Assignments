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


#ifndef REPARSER
#define REPARSER

#include <iostream>
#include <string>

class REParser{
public:
    REParser();
    ~REParser();
    
    void parse(std::string input);
private:
    unsigned int index;
    std::string userInput;
    
    char nextCharacter();
    void match(char symbol);
    void consume();
    
    void RE();
    void _RE();
    void CONCAT();
    void _CONCAT();
    void KLEENE();
    void _KLEENE();
    void ELEMENT();
protected:
    
};

#endif