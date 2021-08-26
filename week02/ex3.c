#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(){
	char buffer[BUFFER_SIZE];
	memset(buffer, BUFFER_SIZE, 0);
	int p = 0;

	printf("triange height: ");
	while ((buffer[p++] = getchar()) != '\n');
	
	int n = atoi(buffer);

	int curw = 1;

	for (int i = 0; i < n; ++i) {
		
		for (int j = 0; j < n - i - 1; ++j)
			putchar(' ');

		for (int j = 0; j < curw; ++j)
			putchar('*');

		for (int j = 0; j < n - i - 1; ++j)
			putchar(' ');		

		putchar('\n');		

		curw += 2;	
	}
}