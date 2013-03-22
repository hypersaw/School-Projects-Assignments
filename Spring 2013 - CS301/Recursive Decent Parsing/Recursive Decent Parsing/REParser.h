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
    bool match(char symbol);
    void consume();
    
    bool RE();
    void _RE();
    bool CONCAT();
    bool _CONCAT();
    bool KLEENE();
    bool _KLEENE();
    bool ELEMENT();
protected:
    
};

#endif