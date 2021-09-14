#include <stdio.h>
#include <unistd.h>

int main() {
	int n = 1234;

	int pid = fork();

	if (pid != 0){
		printf("Hello from parent %d - %d\n", pid, n);
	} else {
		printf("Hello from child %d - %d\n", pid, n);
	}
}
