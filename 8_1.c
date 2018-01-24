#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

void print_array(int* arr, const int MAX, char* name) {
	
	printf("%s: ", name);
	for( int pos= 0; pos < MAX; pos+=1) {
		printf("%d ",arr[pos]);
	}
	printf("\n");
	
}

int sum(int* arr, const int MAX) {
	int sum= 0;
	
	for( int pos= 0; pos < MAX; pos+=1) {
		sum+= arr[pos];
	}
	return sum;
}

double mean(int* arr, const int MAX) {
	
	return (double)(sum(arr,MAX)/MAX);
}

typedef struct{
	int num;
	int quantity;
} Num;


int num_check(Num* arr, const int MAX, int num) {
	
	for( int n= 0; n < MAX; n+=1) {
		if (arr[n].num == num) {
			arr[n].quantity+=1;
			return 1;
		}
	}
	return 0;
}

int mode(int* arr_A, const int MAX_A) {	// dominanta
	
	int MAX_B =1;
	Num* arr_B= malloc(MAX_B * sizeof(Num));
	arr_B[0].num= arr_A[0];
	arr_B[0].quantity= 1;
	
	
	for( int n= 0; n < MAX_A; n+=1) {
		if (num_check(arr_B, MAX_B, arr_A[n]) == False) {
			MAX_B+=1;
			arr_B= realloc(arr_B, MAX_B * sizeof(Num));
			arr_B[MAX_B-1].num= arr_A[n];
			arr_B[MAX_B-1].quantity= 1;
		}
	}
	
	int result=0;
	for( int n= 1; n < MAX_B; n+=1) {
		if( arr_B[result].quantity < arr_B[n].quantity) {
			result = n;
		}
	}
	
	
	result= arr_B[result].num;
	free(arr_B);
	return result;

}	


void sort(int* arr, const int MAX) {
	
	for( int n= 0; n< MAX; n+=1) {
		for( int m= 0; m+1< MAX-n; m+=1) {
			if( arr[m] > arr[m+1]) {
				int temp= arr[m];
				arr[m]= arr[m+1];
				arr[m+1]= temp;
			}
		}	
	}
}

double median(int* arr, const int MAX) {
	//make table for checking median
	
	sort(arr, MAX);
	
	if( MAX%2== 0){
		return (double)(arr[(MAX/2)-1]+arr[(MAX/2)])/2;
	}
	else {
		return (arr[(MAX/2)]);
	}
	
}

int* load(const int MAX) {
	int* arr= malloc(MAX* sizeof(int));
	
	return arr;
}


int input(const int min, const int max, char* str) {
	int input;
	int x;
	do {
		printf("%s", str);
		input= scanf("%d", &x);
		if( input == False) {
			printf("Error: check input\n");
			char c;
			while ((c= getchar()) != '\n' && c != EOF) { }
		}
		else {
			if( x<min || x>=max) {
				input = False;
				printf("Error: check input\n");
				char c;
				while ((c= getchar()) != '\n' && c != EOF) { }				
			}
		}
		
	} while (input == False);
	
	return x;
}

void print_hex(int x) {
	char arr[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	
	if( x != 0) {
		print_hex(x/16);
		printf("%c", arr[x%16]);
	}
	
}

void print_oct(int x) {
	char arr[8] = {'0', '1', '2', '3', '4', '5', '6', '7'};
	
	if( x != 0) {
		print_hex(x/8);
		printf("%c", arr[x%8]);
	}
	
}


void p(double x, char* str) {
	printf("%s: %lf, ", str, x);
	print_hex(x);
	printf(", ");
	print_oct(x);
	printf("\n");
}



int main() {
	
	int MAX = input(1,10000, "Enter size of array: ");
	int* arr= load(MAX);
	for( int n= 0; n < MAX; n+=1) {
		printf("Enter %d int: ", n+1);
		arr[n]= input(-100000, 100000, "");
	}
	
	p(sum(arr, MAX), "Sum");
	p(mean(arr, MAX), "Mean");
	p(median(arr, MAX), "Median");
	p(mode(arr, MAX), "Mode");
	
	free(arr);
	return 0;
}
