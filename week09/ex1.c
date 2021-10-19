#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 16384
#define INF 32768
#define NUMBER_BITS 16

typedef struct page{
	int id;
	int priority;
} page_t;

int is_digit(char c){
	return c >= '0' && c <= '9';
}

int read_file_arr(const char *fname, int **arr){
	int file = open(fname, O_RDONLY);

	char content[MAX_FILE_SIZE];
	memset(content, 0, MAX_FILE_SIZE);

	size_t fsize = read(file, content, MAX_FILE_SIZE);

	int arr_size = 1;

	for (int i = 0; i < fsize; ++i){
		if (!is_digit(content[i])){
			if (i < fsize - 1 && is_digit(content[i + 1]))
				++arr_size;
			content[i] = 0;
		}
	}
	
	*arr = (int*)malloc(sizeof(int) * arr_size);

	int p = 0;
	for (int i = 0; i < fsize; ++i){
		if (i == 0 || (is_digit(content[i]) && !is_digit(content[i - 1])))
			sscanf(&content[i], "%d", &((*arr)[p++]));
	}

	return arr_size;
}

int frames = 0;

int main(int argc, char *argv[]){
	sscanf(argv[1], "%d", &frames);

	if (frames <= 0){
		printf("Incorrect number of frames!\n");
		return 1;
	}

	int *arr = NULL;
	int arr_size = read_file_arr("input.txt", &arr);

	page_t *pages = (page_t*) malloc(sizeof(page_t) * frames);

	for (int i = 0; i < frames; ++i){
		pages[i].id = -1;
		pages[i].priority = 0;
	}

	int hit = 0, miss = 0;

	for (int i = 0; i < arr_size; ++i){

		for (int k = 0; k < frames; ++k){
			printf("i = %d id = %d %d\n", k, pages[k].id, pages[k].priority);
		}

		printf("current page number %d\n\n", arr[i]);

		int hit_check = 0;
		for (int j = frames - 1; j >= 0; --j){
			pages[j].priority >>= 1;
			if (pages[j].id == arr[i]){
				hit++;
				hit_check++;
				pages[j].priority |= 1 << (NUMBER_BITS - 1);
			}
		}

		if (hit_check)
			continue;

		++miss;
		int min = 0;
		for (int j = frames - 1; j >= 0; --j){
			if (pages[min].id == -1 || pages[j].priority < pages[min].priority){
				min = j;
			}

			if (pages[min].id == -1)
				break;
			}

			pages[min].id = arr[i];
			pages[min].priority = INF;
	}

	double ratio = (float) hit / (float) (miss);
	printf("hit = %f miss = %f ratio = %f\n", (float)hit, (float)miss, ratio);

	free(pages);
	free(arr);
}