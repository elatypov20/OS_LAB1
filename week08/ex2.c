#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>

#define ITERATIONS 10
#define SECONDS_DELAY 1
#define ALLOCATE 10 * 1024 * 1024

int main(){
	for (int i = 0; i < ITERATIONS; ++i) {
		char *mem = (char*) malloc(ALLOCATE);
		memset(mem, 0, ALLOCATE);
		sleep(SECONDS_DELAY);
	}
}