#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 2048

void background_run(char **args);
char **parse_args(char *args);

int main(){
	printf("Welcome to shell v2.0!\n");
	printf("It supports process background execution.\n");
	printf("To use it just put `&` at the end of the line ");
	printf("(e.g. `sleep 3&`)\n");
	printf("OR use `./ex4_example.sh&` for demonstration\n\n");

	char cwdbuff[BUFFER_SIZE]; // buffer for current path
	char buff[BUFFER_SIZE];
	
	while (1){
		// read current path
		// (cd command doesn't work, I made this feature
		// just to make change visually from 3rd task)
		getcwd(cwdbuff, BUFFER_SIZE);
		printf("%s $ ", cwdbuff);

		// read command (line)
		memset(buff, 0, BUFFER_SIZE);
		int p = 0;
		while ((buff[p++] = getchar()) != '\n');
		buff[--p] = 0; // remove \n from the end
		

		char **args;

		// printf(".%s.\n\n", args[3]);
		
		// check if background process
		if (buff[--p] == '&'){
			buff[p] = 0;
			args = parse_args(buff);
			background_run(args);
		}else{
			args = parse_args(buff);
			int pid = fork();
			if (pid != 0)
				wait(NULL);
			else{
				execvp(args[0], args);
			}
		}
		
		free(args);
	}
}


void background_run(char **args){
	int pid = fork();

	if (pid != 0){
		printf("background process [%d]\n", pid);
		return;
	}

	execvp(args[0], args);
}

char **parse_args(char *args){
	int args_size = 1;
	char **parsed = (char**) malloc(sizeof(char**) * BUFFER_SIZE);
	
	for (int i = 0; i < BUFFER_SIZE; ++i)
		parsed[i] = NULL;

	parsed[0] = &args[0];

	char cur, prev = args[0];
	int p = 1;
	while ((cur = args[p++]) != 0){
		if (cur != ' ' && prev == 0){
			parsed[args_size++] = &args[p - 1];
		} else if (cur == ' '){
			cur = 0;
			args[p - 1] = 0;
		}
		prev = cur;
	}
	
	return parsed;
}