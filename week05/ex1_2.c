#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

void *print_thread(void *args){
	printf("Hello from thread %d\n", (int) args);
	
	printf("Terminating of thread %d\n", (int) args);
	pthread_exit(NULL);
}

int main(){
	pthread_t threads[N];

	for (int i = 0; i < N; ++i) {
		printf("Creating thread %d\n", i);
		pthread_create(&threads[i], NULL, print_thread, (void*) i);
		pthread_join(threads[i], NULL);
		sleep(1);
	}
}