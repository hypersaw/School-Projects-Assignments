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
//    12.	<OUTPUT>	->	<ELEM>,
//    13.	<OUTPUT>	->	/e/
//    14.	<DIR>		->	L
//    15.	<DIR>		->	R
//    16.	<ELEM>		->	<NUM>
//    17.	<ELEM>		->	<ULET>
//    18.	<ELEM>		->	<LLET>
//    19.	<ELEM>		->	#
//    20.   <ELEM>		->	_
//    21.	<NUM>		->	{ 0 - 9 }
//    22.	<LET>		->	<LLET>
//    23.	<LET>		->	<ULET>
//    24.	<LLET>		->	{ a - z }
//    25.	<ULET>		->	{ A - Z }

#include "TuringMachine.h"

TuringMachine::TuringMachine(std::string filename){
    std::ifstream newMachine;
    newMachine.open(filename);
    
    if(newMachine.fail()){
        throw "ERROR: (TuringMachine) Invalid filename.";
    }
    
    std::string newRule;
    while(!newMachine.eof()){
        getline(newMachine, newRule);
        newRule = trimWhitespace(newRule);
        
        // Ignore file comments
        if(newRule[0] != '%'){
            machineRules[ruleCount] = newRule;
            ++ruleCount;
        }
    }
    
    std::cout << "Created a new Turing Machine with " << ruleCount << " rules." << std::endl;
    for(int i = 0; i < ruleCount; ++i){
        std::cout << machineRules[i] << std::endl;
    }
    
    parseFile();
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
        std::cout << "Item: " << (char)item << std::endl;
        throw "Match fault.";
    }
}

int TuringMachine::nextChar(){
    return machineRules[currentLine][currentLinePosition];
}

void TuringMachine::parseFile(){
    for(int currentLine = 0; currentLine < ruleCount; ++currentLine){
        parseRule(machineRules[currentLine]);
    }
}

void TuringMachine::parseRule(std::string rule){
    currentLinePosition = 0;
    
    try{
        LINE();
    }
    catch(const char* error){
        std::cout << "ERROR: " << error << std::endl;
    }
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

void TuringMachine::LINE(){
    VAR();
    matchChar(',');
    VAR();
    matchChar(':');
    INPUT();
    matchChar('-');
    matchChar('>');
    OUTPUT();
}

void TuringMachine::VAR(){    
    LET();
    VAR_();
}

void TuringMachine::VAR_(){    
    if(alphabetSet.find(nextChar()) != std::string::npos){
        LET();
        VAR_();
    }
    else if(numberSet.find(nextChar()) != std::string::npos){
        NUM();
        VAR_();
    }
    else{
        ;
    }
}

void TuringMachine::INPUT(){
    if(lowercaseSet.find(nextChar()) != std::string::npos){
        LLET();
        INPUT_();
    }
    else if(numberSet.find(nextChar()) != std::string::npos){
        NUM();
        INPUT_();
    }
    else if(nextChar() == '#'){
        matchChar('#');
        INPUT_();
    }
    else if(nextChar() == '_'){
        matchChar('_');
        INPUT_();
    }
    else{
        throw "Incorrect input format (no input defined/must start with lowercase letter, number, or pound sign).";
    }
}

void TuringMachine::INPUT_(){
    if(nextChar() == ','){
        matchChar(',');
        INPUT();
    }
    else if(nextChar() != '-'){
        throw "Incorrect input format (missing comma/size larger than one character).";
    }
    else{
        ;
    }
}

void TuringMachine::OUTPUT(){
    int prevChar = nextChar();
    
    ELEM();
    
    if(nextChar() == ','){
        matchChar(',');
        DIR();
    }
    else{
        if(prevChar != 'L' && prevChar != 'R'){
            throw "Incorrect direction format (must be L or R).";
        }
        else{
            ;
        }
    }
}

void TuringMachine::DIR(){
    if(nextChar() == 'L' || nextChar() == 'R'){
        matchChar(nextChar());
    }
    else{
        throw "Incorrect direction (must be L or R).";
    }
}

void TuringMachine::ELEM(){
    if(alphabetSet.find(nextChar()) != std::string::npos){
        matchChar(nextChar());
    }
    else if(numberSet.find(nextChar()) != std::string::npos){
        matchChar(nextChar());
    }
    else if(nextChar() == '#'){
        matchChar('#');
    }
    else if(nextChar() == '_'){
        matchChar('_');
    }
}

void TuringMachine::NUM(){
    if(numberSet.find(nextChar()) != std::string::npos){
        matchChar(nextChar());
    }
    else{
        throw "Incorrect number format (some other character used outside of 0-9).";
    }
}

void TuringMachine::LET(){
    if(alphabetSet.find(nextChar()) != std::string::npos){
        matchChar(nextChar());
    }
    else{
        throw "Incorrect letter format (some other character used outside of a-z,A-Z).";
    }
}

void TuringMachine::LLET(){
    if(lowercaseSet.find(nextChar()) != std::string::npos){
        matchChar(nextChar());
    }
    else{
        throw "Incorrect lowercase format (some other character used outside of a-z).";
    }
}

void TuringMachine::ULET(){
    if(uppercaseSet.find(nextChar()) != std::string::npos){
        matchChar(nextChar());
    }
    else{
        throw "Incorrect uppercase format (some other character used outside of A-Z).";
    }
}