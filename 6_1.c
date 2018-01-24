#include <stdio.h>
#include <time.h>

#define True 1
#define False 0



void print_ASCII() {
	for( int chr= 0; chr<256; chr+=1) {
		printf("%d is: '%c'\n", chr, chr);
	}
}




int main(){
	
	print_ASCII();
	
	
	
	return 0;
}