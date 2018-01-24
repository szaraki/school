#include <stdio.h>
#include <math.h>
#include <time.h>


void print_array(int* arr, const int MAX, char* name) {
	
	printf("%s: ", name);
	for( int pos= 0; pos < MAX; pos+=1) {
		printf("%d ",arr[pos]);
	}
	printf("\n");
	
}


void sort(int** arr, const int MAX) {
	
	for( int n= 0; n< MAX; n+=1) {
		for( int m= 0; m+1< MAX-n; m+=1) {
			if( *(arr[m]) > *(arr[m+1])) {
				int temp= *(arr[m]);
				*(arr[m])= *(arr[m+1]);
				*(arr[m+1])= temp;
			}
		}	
	}	
	
	
	
}



int main() {
	//init
	srand(time(NULL));
	const int MAX= 10;
	int arrA[MAX];
	int* arrB[MAX];
	
	
	
	for( int n= 0; n< MAX; n+=1) {
		arrA[n]= rand()%MAX;
		arrB[n]= arrA+n;
	}
	
	print_array(arrA, MAX, "arrA");
	sort(arrB, MAX);
	print_array(arrA, MAX, "arrA");
	
	return 0;
}