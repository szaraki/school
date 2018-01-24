#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define True 1
#define False 0



void average(int* ben, int* end) {
	int base =1;
	int sum_base =0;
	for ( int* chck = ben; chck != end; chck+=1, base+=1) {
			sum_base+=base*(*chck);
	}
	sum_base+=(*end)*base;
	printf("Sum: %d\n", sum_base);
	printf("Base: %d\n", base);
	printf("Result: %d\n", sum_base/base);
}




int main(){
	int arr[] = {1,2};
	average(arr, arr+1);
	
	
	
	
	return 0;
}