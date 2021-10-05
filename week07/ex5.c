#include <stdlib.h>
#include <stdio.h>

int main() {
	char **s = (char**) malloc(sizeof(char*));
	char foo[] = "Hello World";
	*s = foo;

	// it is just address of array
	// doesn't mean anything useful for user
	printf("s is 0x%x\n", s);
	
	s[0] = foo;
	printf("s[0] is %s\n",s[0]);
	return (0);
}