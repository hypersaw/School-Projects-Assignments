#include "TuringMachine.h"

TuringMachine::TuringMachine(std::string filename, std::string input){
    ruleCount = 0;
    currentLine = 0;
    currentLinePosition = 0;
    lowercaseSet = "abcdefghijklmnopqrstuvwxyz";
    uppercaseSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    alphabetSet = lowercaseSet + uppercaseSet;
    numberSet = "0123456789";
    
    std::ifstream newMachine;
    newMachine.open(filename.c_str());
    
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
    
    buildMachine();
    
    // Add the accept and reject states
    State acceptState("accept"), rejectState("reject");
    machineStates.push_back(acceptState);
    machineStates.push_back(rejectState);
}

TuringMachine::~TuringMachine(){
    machineStates.clear();
}

void TuringMachine::buildMachine(){
    validateMachine();
    for(int currentLine = 0; currentLine < ruleCount; ++currentLine){
        buildRule(machineRules[currentLine]);
    }
}

void TuringMachine::buildRule(std::string newRule){
    std::string ruleSource, ruleDestination, ruleInputs;
    char ruleOutput, ruleDirection;
    
    int linePos = 0;
    // Get Rule Name
    while(newRule[linePos] != ','){
        ruleSource += newRule[linePos];
        ++linePos;
    }
    newRule = newRule.substr(linePos+1);
    
    // Get Rule Destination
    linePos = 0;
    while(newRule[linePos] != ':'){
        ruleDestination += newRule[linePos];
        ++linePos;
    }
    newRule = newRule.substr(linePos+1);

    // Get Rule Inputs
    linePos = 0;
    while(newRule[linePos] != '-'){
        if(newRule[linePos] != ','){
            ruleInputs += newRule[linePos];            
        }
        ++linePos;
    }
    newRule = newRule.substr(linePos+2);

    // Get Rule Output and Direction
    if(newRule.length() > 1){
        ruleOutput = newRule[0];
        ruleDirection = newRule[2];
    }
    // Or Get Rule Direction
    else{
        ruleOutput = 0;
        ruleDirection = newRule[0];
    }
    
    // Create state and add transition rule
    if(!stateExists(ruleSource)){
        State* newState;
        newState = new State(ruleSource);
        machineStates.push_back(*newState);
    }
    
    getState(ruleSource).addTransition(ruleInputs, ruleOutput, ruleDirection, ruleDestination);
    
    // Set this as our current state if we haven't yet
    if(currentState.getStateName() == "NULL"){
        currentState = getState(ruleSource);
    }
}

State& TuringMachine::getState(std::string stateName){
    State* requestedState;
    
    for(int i = 0; i < machineStates.size(); ++i){
        if(machineStates.at(i).getStateName() == stateName){
            requestedState = &machineStates.at(i);
        }
    }
    
    return *requestedState;
}

void TuringMachine::runInput(std::string machineInput){
    
    int headPosition = 0;
    
    // Continue while we are not in an accept or reject state
    while(currentState.getStateName() != "reject" && currentState.getStateName() != "accept"){
        // Display the tape
        if(machineInput[0] == '_'){
            machineInput = machineInput.substr(1);
            --headPosition;
        }
        if(headPosition == -1){
            machineInput = "_"+machineInput;
            headPosition = 0;
        }
        for(int i = 0; i < machineInput.length();){
            if(headPosition == i){
                std::cout << "(" << currentState.getStateName() << ") ";
            }
            
            std::cout << machineInput[i] << " ";
            ++i;
        }
        if(headPosition == machineInput.length()){
            std::cout << "(" << currentState.getStateName() << ")";
        }
        if(headPosition == (machineInput.length() + 1)){
            std::cout << "_ (" << currentState.getStateName() << ")";
        }
        std::cout << "\n";
        
        // Analyze at tape head
        char headPositionCharacter;
        if(headPosition == -1 || headPosition == machineInput.length()){
            headPositionCharacter = '_';
        }
        else{
             headPositionCharacter = machineInput[headPosition];
        }
        
        if(currentState.hasTransitionOnInput(headPositionCharacter)){
            // Write output if available
            if(currentState.hasOutputOnInput(headPositionCharacter)){
                machineInput[headPosition] = currentState.outputOnInput(headPositionCharacter);
            }
            
            // Move head
            char moveHead = currentState.directionOnInput(headPositionCharacter);
            if(moveHead == 'L'){
                --headPosition;
            }
            else{
                ++headPosition;
            }
            
            // Set new state
            currentState = getState(currentState.stateOnInput(headPositionCharacter));
        }
        else{
            currentState = getState("reject");
        }
    }
    
    
    if(currentState.getStateName() == "accept" || currentState.getStateName() == "reject"){
        for(int i = 0; i < machineInput.length();){
            if(headPosition == i){
                std::cout << "(" << currentState.getStateName() << ") ";
            }
            
            std::cout << machineInput[i] << " ";
            ++i;
        }
        if(headPosition == machineInput.length()){
            std::cout << "(" << currentState.getStateName() << ")";
        }
        if(headPosition == (machineInput.length() + 1)){
            std::cout << "_ (" << currentState.getStateName() << ")";
        }
        std::cout << "\n";
        
        if(currentState.getStateName() == "accept"){
            std::cout << "** Accepted\n";
        }
        else{
            std::cout << "** Rejected\n";
        }
    }
}

bool TuringMachine::stateExists(std::string stateName){
    bool exists = false;
    for(int i = 0; i < machineStates.size(); ++i){
        if(machineStates.at(i).getStateName() == stateName){
            exists = true;
        }
    }
    
    return exists;
}

void TuringMachine::validateMachine(){
    std::cout << "** Validating TM file...\n";
    for(int currentLine = 0; currentLine < ruleCount; ++currentLine){
        validateRule(machineRules[currentLine]);
    }
    std::cout << "** TM file validated...\n";
}

void TuringMachine::validateRule(std::string rule){
    currentLinePosition = 0;
    
    try{
        LINE();
    }
    catch(const char* error){
        std::cout << "ERROR (" << currentLine << "," << currentLinePosition << "): " << error << std::endl;
        std::cout << "** Exiting...\n";
        exit(0);
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

void TuringMachine::consumeChar(){
    ++currentLinePosition;
}

void TuringMachine::matchChar(int item){
    if (item == nextChar()){
        consumeChar();
    }
    else{
        throw "Match fault.";
    }
}

int TuringMachine::nextChar(){
    return machineRules[currentLine][currentLinePosition];
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