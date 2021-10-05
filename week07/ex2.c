#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("N is not provided!\n");
		return 1;
	}

	int n;
	sscanf(argv[1], "%d", &n);

	int *arr = (int*) malloc(sizeof(int) * n);

	for (int i = 0; i < n; ++i) {
		arr[i] = i;
	}

	for (int i = 0; i < n; ++i) {
		printf("%d\n", arr[i]);
	}

	free(arr);
}