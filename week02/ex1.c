#include <limits.h>
#include <float.h>
#include <stdio.h>

int main(){
	int i = INT_MAX;
	float f = FLT_MAX;
	double d = DBL_MAX;

	printf("size of integer: %ld; max value: %d\n", sizeof(i), i);
	printf("size of float: %ld; max value: %f\n", sizeof(f), f);
	printf("size of double: %ld; max value: %f\n", sizeof(d), d);
}