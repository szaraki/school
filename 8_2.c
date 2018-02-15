#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

enum ArgumentType{ TYPE_CHAR, TYPE_CHAR_PTR, TYPE_INT, TYPE_DOUBLE};


void make_line(int size) {
	char* line = "";
	for( int n= 0; n < size; n++) {
		printf("-");
	}
}


void print_int(int* arg, unsigned width) {
	int len= log10(arg[0]);
	int max= ((double)width- len)/2;
	make_line(max);
	printf("%d", arg[0]);
	make_line(width-max-len-1);
	printf("\n");
}

void print_char(char* arg, unsigned width) {
	int max= (width-1)/2;
	make_line(max);
	printf("%c", arg[0]);
	make_line(max+1);
	printf("\n");
}

void print_str(char* arg, unsigned width) {
	if( arg== NULL) {
		make_line(width);
	}
	else {
		int len= strlen(arg);
		int max= (width-len)/2;
		make_line(max);
		printf("%s", arg);
		make_line(width-max-strlen(arg));
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
	make_line(max);
	
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
	make_line(width);
	printf("\n");
}




int printArgumentInTheMiddle(void* argument, enum ArgumentType type, unsigned width) {
	if (argument == NULL) {
		for( int n=0; n<width/2; n+=1) {
			printf("-");
		}
	}
	switch( type) {
		case TYPE_CHAR:
			print_char(argument, width);
			return 1;
		case TYPE_CHAR_PTR:
			print_str(argument, width);
			return 1;
		case TYPE_INT:
			print_int(argument, width);
			return 1;
		case TYPE_DOUBLE:
			print_double(argument, width);
			return 1;
	}
	
	return 0;
}



int main() {
	const double test_double= 2.;
	printArgumentInTheMiddle(&test_double, TYPE_DOUBLE, 10);
	const char	test_char= 'x';
	printArgumentInTheMiddle(&test_char, TYPE_CHAR, 10);
	const char* test_char_ptr= "test";
	printArgumentInTheMiddle(test_char_ptr, TYPE_CHAR_PTR, 10);
	const int 	test_int= 22;
	printArgumentInTheMiddle(&test_int, TYPE_INT, 10);
	
	return 0;
}