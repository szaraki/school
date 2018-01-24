#include <stdio.h>
#include <math.h>

#define True 1
#define False 0

int main() {
	
	
	int input;
	int x;
	do {
		printf("Enter number [1, 10]: ");
		input= scanf("%d", &x);
		if( input == False) {
			printf("Error: check input\n");
			char c;
			while ((c= getchar()) != '\n' && c != EOF) { }
		}
		else {
			if( x<=0 || x>10) {
				input = False;
				printf("Error: check input\n");
				char c;
				while ((c= getchar()) != '\n' && c != EOF) { }				
			}
		}
		
	} while (input == False);
	
	
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