#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *custom_realloc(void *ptr, size_t new_size){
	if (ptr == NULL && new_size == 0)
		return NULL;
	
	if (ptr == NULL)
		return malloc(new_size);

	if (new_size == 0){
		free(ptr);
		return NULL;
	}

	void *new_ptr = malloc(new_size);

	memcpy(new_ptr, ptr, new_size);

	free(ptr);
	return new_ptr;
}

int main(){
	//Allows you to generate random number
	srand(time(NULL));

	// Allows user to specify the original array size, stored in variable n1.
	printf("Enter original array size:");
	int n1=0;
	scanf("%d",&n1);

	//Create a new array of n1 ints
	int* a1 = (int*) malloc(sizeof(int) * n1);
	int i;
	for(i=0; i<n1; i++){
		//Set each value in a1 to 100
		a1[i] = 100;
		
		//Print each element out (to make sure things look right)
		printf("%d ", a1[i]);
	}

	//User specifies the new array size, stored in variable n2.
	printf("\nEnter new array size: ");
	int n2=0;
	scanf("%d",&n2);

	//Dynamically change the array to size n2
	a1 = custom_realloc(a1, sizeof(int) * n2);

	//If the new array is a larger size, set all new members to 0. Reason: dont want to use uninitialized variables.

	if (n2 > n1){
		for(int j = 0; j < n2; ++j)
			a1[j] = 0;
	}
	

	for(i=0; i<n2;i++){
		//Print each element out (to make sure things look right)
		printf("%d ", a1[i]);
	}
	printf("\n");
	
	//Done with array now, done with program :D
	free(a1);

	return 0;
}