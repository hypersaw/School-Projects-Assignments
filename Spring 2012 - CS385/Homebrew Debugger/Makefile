SHELL := /bin/bash
SAMPLES = prog1 prog2

all: debugger $(SAMPLES)

debugger: debugger_interface.o dwarf_symbol_reader.o debugger.c
	gcc -std=gnu99 -O0 -g -o debugger debugger.c debugger_interface.o dwarf_symbol_reader.o -lreadline -lcurses -ldwarf -lelf

debugger_interface.o:
	gcc -std=gnu99 -c -g -o debugger_interface.o debugger_interface.c -lreadline -lcurses

dwarf_symbol_reader.o:
	gcc -std=gnu99 -c -g -o dwarf_symbol_reader.o dwarf_symbol_reader.c


$(SAMPLES): %: ./grading/%.c
	gcc -gdwarf-2 -std=gnu99 -O0 -o ./grading/$@ $^

clean:
	rm *.o debugger

unit: debugger
	./grading/run_grading.sh;	
