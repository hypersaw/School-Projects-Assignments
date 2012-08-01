#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include "debugger_interface.h"
#include "dwarf_symbol_reader.h"
#include <string.h>

#define AT_BREAKPOINT 0
#define AFTER_BREAKPOINT 1
#define FRAME_POINTER 2
#define CURRENT_EIP 3

// My Defined Functions
int breakpoint(unsigned int lineNumber);
void fixBreakpoint(unsigned int fixStep);
int findBreakpoint(int code);
void stacktrace();
unsigned long findAddress(int code);
void printVariable(char * format, char * var, int generic);
void printPassedVariable(Dwarf_Die functionDie);
void whereAmI();
void printLine(int lineNumber,char * filePath);

// My Defined Variables
unsigned long breakpoints[100][2];	// breakpoints[][0] is Addr, breakpoints[][1] is Op
					// a breakpoints[0] = 0 means not set, our index is the break number
unsigned long breakpointCount;
unsigned long mostRecentlyUsedBreak;

//identifies a compilation unit and its debugging symbols
struct dwarf_compilation_unit * compilation_unit;
//an array of line info
struct dwarf_lines * dwarf_lines;

//the child we are debugging
pid_t child;
int status;

void initialize_debugger(char * program_name){
	compilation_unit = dwarf_get_compilation_unit(program_name);
	dwarf_lines =  dwarf_get_line_info_from_cu(compilation_unit);

	int i = 0;
	for(; i < 100; ++i){
		breakpoints[i][0] = 0;
		breakpoints[i][1] = 0;
	}

	breakpointCount = 0;
}

void debugger(){
	int hasStarted = 0;
	int hasContinued = 0;
	while(1){
		//wait for a signal
		wait(&status);
		//if the program exited, just return
		if (WIFEXITED( status )){
			printf("\nthe program terminated\n");
			return;
	 	}

		// Quick overview of what's going on here:
		// **Variable 'done': Done will keep us within this while loop. If it is
		//   set to 1 that means we issued the "continue" command.
		//
		// **Variable 'hasContinued': In the event that we stop at a breakpoint
		//   and issue a command other than "continue", we will end up calling
		//   fixBreakpoint a second time. hasContinued will tell the loop
		//   to pump the breaks, we haven't moved on yet!
		int done = 0;
	 	while(!done){
	    		//get user input, what should we do?
			if((breakpointCount > 0) && hasStarted && hasContinued){
				printf("breakpoint %d hit\n",findBreakpoint(AFTER_BREAKPOINT));
				fixBreakpoint(0);	// Restore our opcode and registers
				hasContinued = 0;
			}

	    		user_command * cmd = debugger_interface_get_cmd();
	    		if (cmd){
				//now handle the input
				switch(cmd->command_type){
				case CMD_TYPE_BREAKPOINT:
					if(breakpoint(cmd->value.line_number)){
						printf("Could not set breakpoint at line %d.\n",cmd->value.line_number);
					}
					break;
				case CMD_TYPE_STACKTRACE:
					stacktrace();
					break;
				case CMD_TYPE_PRINT:
					printVariable(cmd->value.var.format,cmd->value.var.name,0);
					break;
				case CMD_TYPE_PRINT_GEN:
					printVariable(cmd->value.var.format,cmd->value.var.name,1);
					break;
				case CMD_TYPE_CONTINUE:
					if(!hasStarted){
						// If we are here, that means we are just starting to run the
						// program, so nothing special.
						hasStarted = 1;
					}
					else{
						// However, if we are here that means we were "interuptted"
						// by a break. We fixed the breakpoint and altered our registers
						// At the beginning of the parent while loop, so now we want
						// to use SINGLE_STEP and then reset the breakpoint that we just
						// fixed.
						fixBreakpoint(1);
					}
					done = 1;
					hasContinued = 1;
					break;
				case CMD_TYPE_WHERE:
					whereAmI();
					break;
				}
			}
		}
		ptrace( PTRACE_CONT, child, NULL, NULL );
	}
}

void exec_debuggee(char * debuggee_name){

	char* argv[] = { NULL };
	char* envp[] = { NULL };

	if(ptrace( PTRACE_TRACEME, 0, NULL, NULL )){
		perror( "ptrace" );
		return;
	}

	execve(debuggee_name,argv,envp);
}

/*fork a child process, and lets get this started!*/
void start(char * debuggee_name){
	pid_t pid = fork();
	switch(pid){
	case -1:
		perror("error\n");
		exit(1);
    		break;
	case 0:
		//the forked process will execute the target program
		exec_debuggee(debuggee_name);
		break;
	default:
		initialize_debugger(debuggee_name);
		child=pid;
 		debugger();
	}
}

//The lone argument is the program to debug
int main(int argc, char ** argv){
	if (argc < 2)
		perror("Error: Must provide a program name\n");
	else
		start(argv[1]);
}



//////////////////////////////////
//                              //
// Start of Andrew's added code //
//                              //
//////////////////////////////////

// Sets a breakpoint at the provided line number.
// To do this we comb through our dwarf_lines struct and compare
// the line numbers associated with the assembly instructions
// until we find the one that matches up with what we want.
//
// Once we have that we will store the OpCode and address into
// our breakpoint array. After everything is safely tucked away
// we start operating on our assembly code *evil laugh*
// Replace the low order byte with 0xCC (INT 3)
// Return of 0 means breakpoint was set successfully!
// Return of 1 means that there were no instructions on that line.
int breakpoint(unsigned int lineNumber){
	int numberOfInstructions = dwarf_lines->number_of_lines;	// How many lines do we have?
	int status;
	int i = 0;
	unsigned long breakAddress = 0;
	for(; i < numberOfInstructions; ++i){
		if(lineNumber == dwarf_lines->lines[i].line_number){
			breakAddress = dwarf_lines->lines[i].addr;
			i = numberOfInstructions;
		}
	}

	if(breakAddress != 0){
		// We found our line, hooray!
		// Now we want to set our break
		int currentBreakpoint = breakpointCount;							// Keep a local variable that won't change

		unsigned int oldOpCode = ptrace(PTRACE_PEEKTEXT,child,breakAddress,NULL);			// Save our instruction at addr
		breakpoints[breakpointCount][0] = breakAddress;							// Save our address
		breakpoints[breakpointCount][1] = oldOpCode;							// Save our instruction at addr
		ptrace(PTRACE_POKETEXT,child,breakAddress,(oldOpCode  & ~0xFF) | 0xCC);				// Modify instr
		printf("breakpoint %d set at line %d\n",currentBreakpoint,lineNumber);
		++breakpointCount;										// Incr global, use currentBreak from now on
		return 0;
	}

	return 1;
}


// fixBreakpoint is going to clean up the mess we made in breakpoint().
// What we are cleaning up is determined by step:
//
// Step = 0: We will restore our OpCode and do nothing else! This will
// prove useful if we ever implement the ability to disable a breakpoint.
// This also allows us to use whereAmI() without having to guess if we
// are after INT 3 or at a valid instruction.
//
// Step = 1 we will be single stepping and then resetting the break.
void fixBreakpoint(unsigned int step){
	if(!step){
		unsigned long breakIndex = findBreakpoint(AFTER_BREAKPOINT);
		unsigned long breakAddress = breakpoints[breakIndex][0];
		unsigned long opCode = breakpoints[breakIndex][1];
		int i = 0;
		ptrace(PTRACE_POKETEXT,child,breakAddress,opCode);	// And now it is restored

		struct user_regs_struct regs;
		ptrace(PTRACE_GETREGS,child,NULL,&regs);
		--regs.eip;
		ptrace(PTRACE_SETREGS,child,NULL,&regs);
	}
	else{
		unsigned long breakIndex = findBreakpoint(AT_BREAKPOINT);
		if(ptrace(PTRACE_SINGLESTEP,child,NULL,NULL) != 0)
			printf("ptrace error\n");			// Execute this one instruction
		wait(&status);

		unsigned long opCode = (breakpoints[breakIndex][1] & ~0xFF) | 0xCC;
		unsigned long address = breakpoints[breakIndex][0];
		ptrace(PTRACE_POKETEXT,child,address,opCode);		// And now it is reset
	}
}

// Takes address from EIP register and checks it against our breakpoints array
// Returns index/breakpoint number
int findBreakpoint(int code){
	unsigned long currentAddress = findAddress(code);

	int i = 0;
	while(currentAddress != breakpoints[i][0]){ ++i;}
	return i;
}

unsigned long findAddress(int code){
	struct user_regs_struct regs;
	ptrace(PTRACE_GETREGS,child,NULL,&regs);

	unsigned long addr;
	if(code == AT_BREAKPOINT)
		addr = regs.eip;
	if(code == AFTER_BREAKPOINT)
		addr = regs.eip - 1;
	if(code == FRAME_POINTER)
		addr = regs.ebp;
	if(code == CURRENT_EIP)
		addr = regs.eip;

	return addr;
}

// Finds line number of first instruction in function
int findLineNumber(unsigned long addr){
	int numberOfInstructions;
	int lineNumber = 0;
	int i = 0;

	numberOfInstructions = dwarf_lines->number_of_lines;	// How many lines do we have?
	while(addr >= dwarf_lines->lines[i].addr){
		lineNumber = dwarf_lines->lines[i].line_number;
		++i;
	}
	return lineNumber;
}

void stacktrace(){
	unsigned long framePointer;
	unsigned long savedEIP;
	unsigned long lowPC;
	unsigned long highPC;
	int functionFound = 0;
	int functionCount = 0;
	char * functionName;
	char * fileName;
	Dwarf_Die functionDie;

	// Find our current Function
	functionDie = dwarf_get_next_function(compilation_unit->root_die,compilation_unit);
	savedEIP = findAddress(CURRENT_EIP);
	while(!functionFound){
		lowPC = dwarf_function_starting_address(functionDie,compilation_unit);
		highPC = dwarf_function_ending_address(functionDie,compilation_unit);
		if((savedEIP >= lowPC) && (savedEIP < highPC)){
			fileName = dwarf_get_name(compilation_unit->root_die,compilation_unit);
			functionName = dwarf_get_name(functionDie,compilation_unit);
			printf("#%d %s(",functionCount,functionName);
			printPassedVariable(functionDie);
			printf(") at %s:%d\n",fileName,findLineNumber(savedEIP));
			functionFound = 1;
			++functionCount;
		}
		else
			functionDie = dwarf_get_next_function(functionDie,compilation_unit);
	}
	functionFound = 0;

	framePointer = findAddress(FRAME_POINTER);
	while(ptrace(PTRACE_PEEKTEXT,child,framePointer,NULL) != 0){
		savedEIP = ptrace(PTRACE_PEEKTEXT,child,framePointer+4,NULL);	// Give us our old EBP
		framePointer = ptrace(PTRACE_PEEKTEXT,child,framePointer,NULL);

		// Now look for function DIE
		functionDie = dwarf_get_next_function(compilation_unit->root_die,compilation_unit);
		while(!functionFound){
			lowPC = dwarf_function_starting_address(functionDie,compilation_unit);
			highPC = dwarf_function_ending_address(functionDie,compilation_unit);
			if((savedEIP >= lowPC) && (savedEIP < highPC)){
				fileName = dwarf_get_name(compilation_unit->root_die,compilation_unit);
				functionName = dwarf_get_name(functionDie,compilation_unit);
				printf("#%d %s() at %s:%d\n",functionCount,functionName,fileName,findLineNumber(savedEIP));
				functionFound = 1;
			}
			else
				functionDie = dwarf_get_next_function(functionDie,compilation_unit);
		}
		functionFound = 0;
	}
}

// This one is a doosey. We are given a format and a variable name, and
// our job is to find it and print it out! There's loads to this one, better
// to just go through the function and read the step-by-step comments.
void printVariable(char * format, char * var, int generic){
	Dwarf_Die functionDie;	// DIE for our function
	Dwarf_Die variableDie;	// DIE for our variable
	Dwarf_Die previousDie;	// DIE for the previous variable
	Dwarf_Loc variableLocation;	// Location of our DIE
	int variableFound;
	unsigned long lowPC;
	unsigned long highPC;
	unsigned long currentAddress;
	unsigned long variableAddr;
	int locationType;
	int variableOffset;
	int variableData;

	struct user_regs_struct regs;
	ptrace(PTRACE_GETREGS,child,NULL,&regs);

	currentAddress = findAddress(AT_BREAKPOINT);

	variableFound = 0;
	previousDie = NULL;

	// First, check our globals!
	variableDie = dwarf_get_next_variable(compilation_unit->root_die,compilation_unit);
	while((variableDie != NULL) && (variableFound == 0)){
		if(strcmp(var,dwarf_get_name(variableDie,compilation_unit)) == 0){
			variableLocation = dwarf_get_variable_location(variableDie,compilation_unit);
			variableAddr = dwarf_get_variable_loc_addr(variableLocation);
			if(variableAddr != 0)
				variableFound = 1;
			else
				variableDie = dwarf_get_next_variable(variableDie,compilation_unit);
		}
		else
			variableDie = dwarf_get_next_variable(variableDie,compilation_unit);
	}

	// If it isn't a gloabl, check variables within our functions!
	functionDie = dwarf_get_next_function(compilation_unit->root_die,compilation_unit);	// Get the first function
	// Is our instructions address within the starting and ending range?
	while(functionDie != NULL && variableFound == 0){
		lowPC = dwarf_function_starting_address(functionDie,compilation_unit);
		highPC = dwarf_function_ending_address(functionDie,compilation_unit);
		if((currentAddress >= lowPC) && (currentAddress < highPC)){
			variableDie = dwarf_get_next_variable(functionDie,compilation_unit);
			while((variableDie != NULL) && variableFound == 0){
				if(strcmp(var,dwarf_get_name(variableDie,compilation_unit)) == 0){
					// We found our variable! Now we need to print out the correct statement
					// To do that, we need to find the value for our variable, and to do THAT
					// we need to find its location. As of right now I'm not sure that we will
					// ever have a location type of 3. This is checking for scope of just the function,
					// but then again I don't know!
					variableLocation = dwarf_get_variable_location(variableDie,compilation_unit);
					locationType = dwarf_get_variable_loc_type(variableLocation);
					variableAddr;
					if((locationType == 1) || (locationType == 2)){
						variableOffset = dwarf_get_variable_loc_offset(variableLocation);
						// Location type is SP OFFSET
						if(locationType == 1)
							variableAddr = variableOffset + regs.esp;
						// Location type is BP OFFSET
						if(locationType == 2)
							variableAddr = variableOffset + regs.ebp + 0x8;
					}
					if(locationType == 3){
						variableAddr = dwarf_get_variable_loc_addr(variableLocation);
					}

					variableFound = 1;
				}
				else
					variableDie = dwarf_get_next_variable(variableDie,compilation_unit);
			}
		}
		else
			functionDie = dwarf_get_next_function(functionDie,compilation_unit);
	}
	if(variableFound && !generic){
		variableData = ptrace(PTRACE_PEEKTEXT,child,variableAddr,NULL);
		if(strcmp(format, "/c") == 0)
			printf("%c\n",(char)variableData);
		if(strcmp(format,"/d") == 0)
			printf("%d\n",variableData);
		if(strcmp(format,"/s") == 0){
			char variableChar;
			printf("\"");
			while(variableChar){
				variableChar = (char)ptrace(PTRACE_PEEKTEXT,child,variableData,NULL);
				printf("%c",variableChar);
				++variableData;
			}
			printf("\"");
			printf("\n");
		}
	}
	if(variableFound && generic){
		variableData = ptrace(PTRACE_PEEKTEXT,child,variableAddr,NULL);
		int dataType = dwarf_get_data_type(variableDie,compilation_unit);
		if(dataType == DW_ATE_signed_char)
			printf("%c\n",(char)variableData);
		if(dataType == DW_ATE_signed)
			printf("%d\n",variableData);
		if(dataType == (DW_ATE_signed_char + 100)){
			char variableChar;
			printf("\"");
			while(variableChar){
				variableChar = (char)ptrace(PTRACE_PEEKTEXT,child,variableData,NULL);
				printf("%c",variableChar);
				++variableData;
			}
			printf("\"");
			printf("\n");
		}
	}
	if(!variableFound)
		printf("Variable '%s' not within scope!\n",var);
}

// Print out the variables with locationType 2 for this function
void printPassedVariable(Dwarf_Die functionDie){
	Dwarf_Die variableDie;	// DIE for our variable
	Dwarf_Loc variableLocation;	// Location of our DIE
	unsigned long variableAddr;
	int locationType;
	int variableOffset;
	int variableData;
	int first = 1;

	struct user_regs_struct regs;
	ptrace(PTRACE_GETREGS,child,NULL,&regs);

	// Is our instructions address within the starting and ending range?
	variableDie = dwarf_get_next_variable(functionDie,compilation_unit);
	while(variableDie != NULL){
		variableLocation = dwarf_get_variable_location(variableDie,compilation_unit);
		locationType = dwarf_get_variable_loc_type(variableLocation);
		if(locationType == 2){
			variableOffset = dwarf_get_variable_loc_offset(variableLocation);
			// Location type is BP OFFSET
			variableAddr = variableOffset + regs.ebp + 0x8;
			if(first){
				printf("%s=%ld",dwarf_get_name(variableDie,compilation_unit),ptrace(PTRACE_PEEKTEXT,child,variableAddr,NULL));
				first = 0;
			}
			else
				printf(", %s=%ld",dwarf_get_name(variableDie,compilation_unit),ptrace(PTRACE_PEEKTEXT,child,variableAddr,NULL));
		}

		variableDie = dwarf_get_next_variable(variableDie,compilation_unit);
	}
}

// Where are we in the program?
// whereAmI finds out what line we are in the program
// by accessing the EIP register. Since we always fix our breakpoints before
// allowing the user to enter a command we can safely assume that we are always
// pointing at a valid instruction. Once we have checked the address against our
// array of lines (dwarf_lines) then we will extract our name/filepath from
// the root DIE. Following that we slice and dice the filepath until
// we are left with the source file, and then we announce it to the world.
void whereAmI(){
	unsigned int currentAddress;
	unsigned int currentLine;
	int numberOfInstructions = dwarf_lines->number_of_lines;

	struct user_regs_struct regs;
	ptrace(PTRACE_GETREGS,child,NULL,&regs);
	currentAddress = regs.eip;
	// We will loop through our dwarf lines to find the
	// line number related to the current instructions address
	int i = 0;
	for(; i < numberOfInstructions; ++i){
		if(currentAddress == dwarf_lines->lines[i].addr){
			currentLine = dwarf_lines->lines[i].line_number;
			i = numberOfInstructions;
		}
	}

	// Now we need to find our file name. We are given a path
	// using dwarf_get_name, and we use strtok to parse the string
	// to the source file being used.
	char * fileName;
	fileName = dwarf_get_name(compilation_unit->root_die,compilation_unit);
	const char * delimiter = "/";
	char * token;
	char * parsedName;

	/*
	token = strtok(fileName,delimiter);
	while(token != NULL){
		parsedName = token;
		token = strtok(NULL, delimiter);
	}

	printf("Line %d in %s\n",currentLine,parsedName);
	*/
	printf("line %d in %s\n",currentLine,fileName);
	printLine(currentLine, fileName);
}

void printLine(int lineNumber, char * filePath){
	char string[200];
	FILE *file;

	file = fopen(filePath,"r");
	int i = 1;
	if(!file)
		printf("File not found\n");
	while((fgets(string,sizeof(string),file) != NULL) && i != -1){
		if(i == lineNumber){
			while(string[0] == 0x9 || string[0] == 0x20){
				int j = 0;
				for(; j < 200; ++j)
					string[j] = string[j+1];
			}
			printf("%s",string);
			i = -1;
		}
		else
			++i;
	}
	fclose(file);
}
