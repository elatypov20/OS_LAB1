#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

FILE *input;

int *read_arr(int *n){
	int *arr = malloc(BUFFER_SIZE);
	char line[BUFFER_SIZE];
	memset(line, 0, BUFFER_SIZE);

	char c = fgetc(input);
	int p = 0;
	while (c != '\n' && c != EOF){
		line[p++] = c;
		c = fgetc(input);
	}

	if (!p)
		return NULL;

	int t = 0;
	for (int i = 0; i < p; ++i){
		if (i == 0 || line[i - 1] == ' ')
			sscanf(&line[i], "%d", &arr[t++]);
	}

	if (n != NULL)
		*n = t;

	return arr;
}

int **read_mx(int *m){
	int **mx = (int**) malloc(BUFFER_SIZE);

	int p = 0;

	while ((mx[p++] = read_arr(NULL)) != NULL);

	*m = p - 1;
	return mx;
}

int main(){
	input = fopen("input.txt", "r");

	int n, m;

	int *E = read_arr(&n);
	read_arr(NULL);
	int *A = read_arr(&n);

	read_arr(NULL);
	int **C = read_mx(&m);
	int **R = read_mx(&m);

	int *deadlocked = (int*) malloc(sizeof(int) * m);
	memset(deadlocked, 0, sizeof(int) * m);

	for (int k = 0; k < m * m; ++k){
		for (int i = 0; i < m; ++i){
			int dl = 0;
			for (int j = 0; j < n; ++j){
				int need = R[i][j] - C[i][j];
				if (need > A[j] || need > E[j]){
					dl = 1;
					break;
				}
			}

			deadlocked[i] = dl;

			if (dl)
				continue;

			for (int j = 0; j < n; ++j){
				int need = R[i][j] - C[i][j];
				A[j] -= need;
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i < m; ++i){
		if (deadlocked[i]){
			++cnt;
			printf("Process %d deadlocked\n", i);
		}
	}

	if (!cnt)
		printf("No deadlock is detected\n");
}