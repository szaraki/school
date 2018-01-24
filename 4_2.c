#include <stdio.h>
#include <math.h>
#include <stdbool.h>


int main() {
	//console input segment
	int input;
	int x;
	do {
		printf("Enter number [1, 10]: ");
		input= scanf("%d", &x);
		if( input == false) {
			printf("Error: check input\n");
			char c;
			while ((c= getchar()) != '\n' && c != EOF) { }
		}
		else {
			if( x<=0 || x>10) {
				input = false;
				printf("Error: check input\n");
				char c;
				while ((c= getchar()) != '\n' && c != EOF) { }				
			}
		}
	} while (input == false);
	
	//find segment
	int min= 1;
	int max= 10;
	int chck;
	for( int n= 0;n < 5 ;n+=1 ) {
		chck = (min+max)/2;	
		if ( x > chck) {
			min = chck;
		}
		else {
			max = chck;
		}
	}
	printf("Result: %d\n", max);
	
	return 0;
}
