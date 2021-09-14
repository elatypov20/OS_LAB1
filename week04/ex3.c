#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 2048

int main(){
	printf("Welcome to shell!\n");

	char buff[BUFFER_SIZE];
	while (1){
		printf(">> ");

		// read command (line)
		memset(buff, 0, BUFFER_SIZE);
		int p = 0;
		while ((buff[p++] = getchar()) != '\n');
		buff[--p] = 0; // remove \n from the end
		
		// execute
		system(buff);
	}
}