#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define True 1
#define False 0


int num= 0;
void num_get() {
	num = (rand()%10)+1;
}

void num_print() {
	printf("%d\n", num);
}


void print_array(int* arr, const int MAX, char* name) {
	
	printf("%s: ", name);
	for( int pos= 0; pos < MAX; pos+=1) {
		printf("%d ",arr[pos]);
	}
	printf("\n");
	
}

void mean() {
	srand(time(NULL));
	const int MAX = 10;
	int arr[MAX];
	for( int pos= 0; pos < MAX; pos+=1) {
		arr[pos] = rand()%10;
	}
	print_array(arr, MAX, "Array");
	int sum= 0;
	
	for( int pos= 0; pos < MAX; pos+=1) {
		sum+= arr[pos];
	}
	
	printf("Result: %lf\n", ((double)sum)/MAX);
}

void f_min_max() {
	srand(time(NULL));
	const int MAX = 10;
	int arr[MAX];
	for( int pos= 0; pos < MAX; pos+=1) {
		arr[pos] = rand()%10;
	}
	print_array(arr, MAX, "Array");
	
	int min = arr[0];
	int max = arr[0];
	
	//func
	for( int pos= 0; pos < MAX; pos+=1) {
		if( min > arr[pos]) {
			min = arr[pos];
		}
		if( max < arr[pos]) {
			max = arr[pos];
		}
	}
	
	
	
	
	
	printf("min: %d\n", min);
	printf("max: %d\n", max);
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

void median() {
	srand(time(NULL));
	const int MAX = 10;
	const int MAX_INT = 10;
	int arr[MAX];
	for( int pos= 0; pos < MAX; pos+=1) {
		arr[pos] = rand()%MAX_INT;
	}
	print_array(arr, MAX, "Array");
	
	int num[MAX_INT];
	for( int pos= 0; pos < MAX; pos+=1) {
		num[pos] = 0;
	}
	
	sort(arr, MAX);
	
	if( MAX%2== 0){
		printf("Result: %d\n", (arr[(MAX/2)-1]+arr[(MAX/2)])/2);
	}
	else {
		printf("Result: %d\n", (arr[(MAX/2)+1]));
	}
}









void menu() {
	//init
	const int MAX = 6;
	char func_name[6][50]= {"Losowanie tablicy 10 liczb",
							"Wyświetlanie jej",
							"Liczenie sredniej liczb",
							"Liczebnie mediany liczb",
							"Maksymalny/minimalny element tablicy",
							"Exit"};
	void (*funcs[5])()={num_get,
	/*    ^ o_O     */	num_print,
						mean,
						median,
						f_min_max};
	
	while( True) {
		//print menu
		printf("Menu: \n");
		for( int pos=0; pos < MAX; pos+=1) {
			printf("%d. %s\n", pos, func_name[pos]);
		}
		
		//get input
		int input;
		int x;
		do {
			printf("Select function by number: ");
			input= scanf("%d", &x);
			if( input == False) {
				printf("Error: check input\n");
				char c;
				while ((c= getchar()) != '\n' && c != EOF) { }
			}
			else {
				if( x<0 || x>=MAX) {
					input = False;
					printf("Error: check input\n");
					char c;
					while ((c= getchar()) != '\n' && c != EOF) { }				
				}
			}
			
		} while (input == False);
		
		//if 5 -> exit
		if(x == 5) {
			return;
		}
		
		
		//start funcion
		//funcs[x]();
		switch( x){
			case 0:
				funcs[0]();
				break;
			case 1:
				funcs[1]();
				break;
			case 2:
				funcs[2]();
				break;
			case 3:
				funcs[3]();
				break;
			case 4:
				funcs[4]();
				break;
		};
	}
	
	
}









int main(){
	menu();
	
	
	
	
	return 0;
}