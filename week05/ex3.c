#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 500

char buffer[BUFFER_SIZE];
int cons_sleep = 0, prod_sleep = 0;

int ready = 0; // how many bytes in buffer are ready

void *producer(){
	int ptr = 0;

	while (1){
		// sleep while full buffer
		while (prod_sleep);

		if (ptr % BUFFER_SIZE == 0)
			printf("%d\n", ready);

		if (ready < BUFFER_SIZE){
			/* !!!!!!!!!
			In next line of code race condition happens, because
			consumer and producer may want to access variable ready at 
			the same time and it will break synchronization
			*/
			ready++;

			cons_sleep = 0;
			buffer[ptr] = ptr;
			ptr = ++ptr % BUFFER_SIZE;
		}else{
			prod_sleep = 1;
		}
	}
}

void *consumer(){
	int ptr = 0;

	while (1){
		// sleep while empty buffer
		while (cons_sleep);
	
		if (ready > 0){
			/* !!!!!!!!
			In next line race condition may happen because consumer
			and producer may access variable ready at the same time 
			and we will lose synchronization
			*/ 
			ready--;
			
			prod_sleep = 0;
			buffer[ptr] = ptr;
			ptr = ++ptr % BUFFER_SIZE;
		}else{
			cons_sleep = 1;
		}

	}
}

int main(){
	memset(buffer, '*', BUFFER_SIZE);
	pthread_t c, p;
	pthread_create(&p, NULL, producer, NULL);
	pthread_create(&c, NULL, consumer, NULL);
	pthread_join(c, NULL);
	pthread_join(p, NULL);
}