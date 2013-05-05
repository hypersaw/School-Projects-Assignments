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
//    1.	<LINE>		->	<VAR>,<VAR>:<INPUT>-><OUTPUT><DIR>
//    2. 	<LINE>		->	%
//    3.	<INPUT>		->	<LLET><INPUT'>
//    4.	<INPUT>		->	<NUM><INPUT'>
//    5.	<INPUT>		->	#<INPUT'>
//    6.	<INPUT>		->	_<INPUT'>
//    7. 	<INPUT'>	->	,<INPUT>
//    8.	<INPUT'>	->	/e/
//    9.	<VAR>		->	<LET><VAR'>
//    10.	<VAR'>		->	<LET><VAR'>
//    11.	<VAR'>		->	<NUM><VAR'>
//    12.	<VAR'>		->	/e/
//    13.	<OUTPUT>	->	<ELEM>,
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

#include "TuringMachine.h"

TuringMachine::TuringMachine(std::string filename){
    std::ifstream newMachine;
    newMachine.open(filename);
    
    if(newMachine.fail()){
        throw "ERROR: (TuringMachine) Invalid filename.";
    }
    
    int lineIndex = 0;
    std::string newRule;
    while(!newMachine.eof()){
        getline(newMachine, newRule);
        newRule = trimWhitespace(newRule);
        
        // Ignore file comments
        if(newRule[0] != '%'){
            machineRules[lineIndex] = newRule;
            ++lineIndex;
        }
    }
    
    std::cout << "Created a new Turing Machine with " << lineIndex << " new rules." << std::endl;
    for(int i = 0; i < lineIndex; ++i){
        std::cout << machineRules[i] << std::endl;
    }
}

TuringMachine::~TuringMachine(){
    
}

void TuringMachine::consumeChar(){
    ++currentLinePosition;
}

void TuringMachine::matchChar(int item){
    if (item == nextChar()){
        consumeChar();
    }
    else{
        throw "Womp.";
    }
}

int TuringMachine::nextChar(){
    return machineRules[currentLine][currentLinePosition];
}

void TuringMachine::parseFile(){
    
}

std::string TuringMachine::trimWhitespace(std::string originalString){
    
    for(int i = 0; i < originalString.length(); ++i){
        if(originalString[i] == ' '){
            originalString.erase(i,1);
            --i;
        }
    }
    
    return originalString;
}