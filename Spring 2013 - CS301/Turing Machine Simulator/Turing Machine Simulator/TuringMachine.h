//    <LINE>	->	<VAR>,<VAR>:<INPUT>-><OUTPUT><DIR> | %
//    <VAR>		->	<LET><VAR'>
//    <VAR'>	->	<LET><VAR'> | <NUM><VAR'> | /E/
//    <INPUT>	->	<LLET><INPUT'> | <NUM><INPUT'> | #<INPUT'> | _<INPUT'>
//    <INPUT'>	->	,<INPUT> | /E/
//    <OUTPUT>	->	<ELEM>, | /E/
//    <DIR>		->	L | R
//    <ELEM>	->	<NUM> | <LET> | # | _
//    <NUM>		-> 	0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
//    <LET>		-> 	<LLET> | <ULET>
//    <LLET>	->	a | b | c | ... | x | y | z
//    <ULET>	->	A | B | C | ... | X | Y | Z
//
//    1.	<LINE>		->	<VAR>,<VAR>:<INPUT>-><OUTPUT>
//    2.	<INPUT>		->	<LLET><INPUT'>
//    3.	<INPUT>		->	<NUM><INPUT'>
//    4.	<INPUT>		->	#<INPUT'>
//    5.	<INPUT>		->	_<INPUT'>
//    6. 	<INPUT'>	->	,<INPUT>
//    7.	<INPUT'>	->	/e/
//    8.	<VAR>		->	<LET><VAR'>
//    9.	<VAR'>		->	<LET><VAR'>
//    10.	<VAR'>		->	<NUM><VAR'>
//    11.	<VAR'>		->	/e/
//    12.	<OUTPUT>	->	<DIR>
//    13.   <OUTPUT>    ->  <ELEM>,<DIR>
//    14.	<OUTPUT>	->	/e/
//    15.	<DIR>		->	L
//    16.	<DIR>		->	R
//    17.	<ELEM>		->	<NUM>
//    18.	<ELEM>		->	<ULET>
//    19.	<ELEM>		->	<LLET>
//    20.	<ELEM>		->	#
//    21.   <ELEM>		->	_
//    22.	<NUM>		->	{ 0 - 9 }
//    23.	<LET>		->	<LLET>
//    24.	<LET>		->	<ULET>
//    25.	<LLET>		->	{ a - z }
//    26.	<ULET>		->	{ A - Z }

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
    int ruleCount = 0;
    int currentLine = 0;
    int currentLinePosition = 0;
    std::string lowercaseSet = "abcdefghijklmnopqrstuvwxyz";
    std::string uppercaseSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string alphabetSet = lowercaseSet + uppercaseSet;
    std::string numberSet = "0123456789";
    
    std::string trimWhitespace(std::string originalString);
    
    void consumeChar();
    void matchChar(int item);
    int nextChar();
    
    void parseFile();
    void parseRule(std::string rule);
    void LINE();
    void VAR();
    void VAR_();
    void INPUT();
    void INPUT_();
    void OUTPUT();
    void DIR();
    void ELEM();
    void NUM();
    void LET();
    void LLET();
    void ULET();
};

#endif
