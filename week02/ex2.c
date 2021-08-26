#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(){
	char buffer[BUFFER_SIZE];
	memset(buffer, BUFFER_SIZE, 0);
	int p = 0;

	printf("input string: ");
	while ((buffer[p++] = getchar()) != '\n');
		
	printf("reversed string: ");

	p--; // remove '\n' from the end
	
	while (--p >= 0)
		putchar(buffer[p]);

	putchar('\n');
}