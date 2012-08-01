all: hw7 simple

simple: simple.c hw7.c
	gcc -m32 --std=gnu99 -g -o simple simple.c hw7.c

hw7: main.c hw7.c
# the -m32 forces gcc to compile a 32-bit binary
	gcc -m32 --std=gnu99 -g -o hw7 main.c hw7.c 

clean:
	rm -rf *~ *.dSYM hw7 simple
