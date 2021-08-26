#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int read_int(){
	char buffer[BUFFER_SIZE];
	memset(buffer, BUFFER_SIZE, 0);
	int p = 0;

	while ((buffer[p++] = getchar()) != '\n');

	return atoi(buffer);
}

void swap_ints(int *x, int *y){
	// swapping via xor algorithm

	*x^=*y;
	*y^=*x;
	*x^=*y;
}

int main(){
	printf("first integer: ");
	int a = read_int();
	printf("second integer: ");
	int b = read_int();

	printf("original integers: %d, %d\n", a, b);
	swap_ints(&a, &b);
	printf("integers after swapping: %d, %d\n", a, b);
}