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

#include <iostream>
#include <string>
#include "REParser.h"

int main(int argc, const char * argv[])
{
    REParser parser;
    std::string input;
    
    std::cout << "** please enter a regular expression: ";
    getline(std::cin,input);
    parser.parse(input.c_str());
    
    return 0;
}

