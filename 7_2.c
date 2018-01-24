#include <stdio.h>
#include <math.h>





void readANDpaste(char* str, int* input) {
	
	int* ptr_input = input;
	
	for (char* ptr= str; *ptr !='\n'; ptr+=1) {
		if ( ptr[0] == '%' && ptr[1] == 'd'){
			scanf("%d", ptr_input);
			ptr_input+=1;
			ptr+=1;
		}
		else {
			printf("%c", *ptr);
		}
	}
	printf("\n");
	
	
	
}






int main() {
	int n[]= {0};
	char str[]= "te%dst\n";
	readANDpaste(str, n);
	
	
	
	return 0;
}