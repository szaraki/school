#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

enum ArgumentType{ chr, chr_ptr, intt, doublee};


void print_int(int arg, unsigned width) {
	int len= log10(arg);
	int max= (width- len)/2;
	for( int n= 0; n< max; n+=1) {
			printf("-");
	}
	printf("%d", arg);
	width-= max+len+1;
	for( int n= 0; n< width; n+=1) {
			printf("-");
	}
	printf("\n");
}

void print_char(char arg, unsigned width) {
	int max= (width-1)/2;
	for( int n= 0; n< max; n+=1) {
			printf("-");
	}
	printf("%c", arg);
	width-= max+1;
	for( int n= 0; n< width; n+=1) {
			printf("-");
	}
}

void print_str(char* arg, unsigned width) {
	if( arg== NULL) {
		for( int n= 0; n< width ; n+=1) {
			printf("-");
		}
	}
	else {
		int len= strlen(arg);
		int max= (width-len)/2;
		for( int n= 0; n< max; n+=1) {
			printf("-");
		}
		width-= len + max;
		printf("%s", arg);
		
		for( int n= 0; n< width; n+=1) {
			printf("-");
		}
	}
	printf("\n");
}

void print_double(double* argg, unsigned width) {
	double arg = argg[0];
	int len;
	int prec;
	printf("%d\n", (int)(arg));
	if( arg == (int)arg) {
		len= log10((int)arg);
		prec=0;
	}
	else if( arg*10 == (int)(arg*10)) {
		len= log10((int)arg)+2;
		prec=1;
		
		
	}
	else {
		len= log10((int)arg)+3;
		prec=2;
		
	}
	int max= (width- len-1)/2;
	for( int n= 0; n< max; n+=1) {
			printf("-");
	}
	if( prec==0) {
		printf("%d", (int)arg);
	}
	else if( prec==1) {
		printf("%.1lf", arg);
	}
	else {
		printf("%.2lf", arg);
	}
	width-= max+len+1;
	for( int n= 0; n< width; n+=1) {
			printf("-");
	}
	printf("\n");
}




int printArgumentInTheMiddle(void* argument, enum ArgumentType type, unsigned width) {
	
	if (argument == NULL) {
		for( int n=0; n<width/2; n+=1) {
			printf("-");
		}
	}
	switch( type) {
		case chr:
			print_char(argument, width);
			return 1;
		case chr_ptr:
			print_str(argument, width);
			return 1;
		case intt:
			print_int(argument, width);
			return 1;
		case doublee:
			print_double(argument, width);
			return 1;
	}
	return 0;
}



int main() {
	
	double n[]= {2.};
	printArgumentInTheMiddle(n, doublee, 10);
	
	
	return 0;
}