#include <stdio.h>

#define ARR_SIZE(x)  (sizeof(x) / sizeof((x)[0])) 

// function prototypes
void bubble_sort(int arr[], int arr_len);
void swap(int *a, int *b);
void print_array(int arr[], int arr_size);

int main(){
	int a = 10, b = 20;
	swap(&a, &b);

	int arr[] = {3, 7, 4, 1, 2, 6, -5};
	printf("Initial array:\n");
	print_array(arr, ARR_SIZE(arr));

	bubble_sort(arr, ARR_SIZE(arr));

	printf("Array after bubble sort:\n");
	print_array(arr, ARR_SIZE(arr));
}

void bubble_sort(int arr[], int arr_len) {
	for (int i = 0; i < arr_len-1; ++i) {
		for (int j = 0; j < arr_len-i-1; ++j) {
			if (arr[j] > arr[j+1]) swap(&arr[j], &arr[j+1]);
		}
	}
}

void swap(int *a, int *b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void print_array(int arr[], int arr_size) {
	for (int i = 0; i < arr_size; ++i) {
		printf("%d\n", arr[i]);
	}
}