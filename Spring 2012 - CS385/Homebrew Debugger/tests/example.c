#include <stdio.h>

void h(int hx){
	printf("In h\n");
}

void g(int gx){
	h(10);
}

int main(){
	g(5);
	return 0;
}
